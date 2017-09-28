//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		主program
//		曜氷
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "UI.h"
#include "Background.h"
#include "Quantitative.h"
//#include "Stage.h"

#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")//multimedia library
//=========================================
//		
//=========================================
#define	CLASS_NAME		TEXT("BadBooty")				//		WindowのClass名
#define	WINDOW_NAME	TEXT("BadBooty")	//		WindowのCaption名



//=========================================
//		Prototype宣言
//=========================================
LRESULT	CALLBACK	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT	Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void	Uninit(void);
void	Update(int);
void	Draw(int);
void	GameInit();


extern PlayerClass *Player;
ImageSystem imageSystem;
UIDrawClass GameUI;
//StageHandle stageHandle;
extern DisplayClass Display;
extern ImaginaryBackground Background;
extern StairClass *Stair;
extern EnemyClass *Enemy;
byte Status;
bool LoopWaiting;
int LoopFPS = 0;
int GameLoop = 0;
//=========================================
//		Global変数
//=========================================
LPDIRECT3D9					g_pD3D = NULL;				//		Direct3D Object
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//		Device Object（描画に必要）

//=========================================
//		Main関数
//=========================================
int	APIENTRY		WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX	wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		(HICON)LoadImage(NULL,WINDOWICO,IMAGE_ICON,0,0,LR_LOADFROMFILE),
		//NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND	hWnd;
	MSG	msg;
	
	//		Window Classの登錄
	RegisterClassEx(&wcex);

	//		Windowの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IMAGE_ICON));

	//		初期化处理（Window作成してから行う）
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//DirectX9初期化
	GameInit(); //Game初期化

	//		Window表示（初期化处理の後に行う）
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	InitKeyboard(hInstance, hWnd);
	DWORD StartTime = timeGetTime();
	DWORD NowTime;
	int fcnt = 0;
	msg.message = NULL;
	//		Message Loop
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)		//Messageを取得しなかった場合「０」を返す
		{	//		Windowsの処理
			if (msg.message == WM_QUIT)
			{//		PostQuitMessage()がよばれて、WM_QUITMessageが来たらLoop終了
				break;
			}
			else
			{
				//		Messageの編訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//		DirectXの处理
			NowTime=timeGetTime();
			
			DWORD deltaTime = NowTime - StartTime;

			if (deltaTime > (float)1000 / 60) {
				fcnt += 1;
				if (fcnt > 60) { fcnt = 0; }
				deltaTime = 0;
				StartTime = timeGetTime();



				//		更新处理
				Update(fcnt);

				//		描画处理
				Draw(fcnt);
			}
		}
	}

	//		Window Class
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//		终了处理
	UninitInput();
	Uninit();
	//tex 解放
	return (int)msg.wParam;
}

//=========================================
//		Window Procedure
//=========================================
LRESULT	CALLBACK	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case	VK_ESCAPE:
			nID = MessageBox(hWnd, TEXT("終了しますか？"), TEXT("終了"), MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, TEXT("終了しますか？"), TEXT("終了"), MB_YESNO);
		if (nID == IDYES)
		{
			delete Player;
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================
//		初期化処理
//=========================================
void	GameInit() {
	switch (Status)
	{
	default:
		Status = TITLE;
		imageSystem.Init();
		break;
	case GAME_START:
		LoopWaiting = false;
		Background.height = 1500;
		Background.width = 2000;
		Display.Init(Background);
		//stageHandle.init(stageHandle.stageNumber);
		imageSystem.Init();

		if (Player != NULL)
		{
			delete Player;
			Player = NULL;
		}
		Player = new PlayerClass;
		Player->Init(); 
		Enemy->AllInit();
		GameUI.Init();
		Status = GAME_PLAY;
		break;
	case GAME_WIN:
		imageSystem.Init();
		break;
	}
	
	
//	Stair->Init();
				 

}

//=========================================
//		更新処理
//=========================================
void Update(int fcnt)
{
	UpdateInput();

	switch (Status)
	{
	case TITLE:
		imageSystem.Update();
		if (GetKeyboardTrigger(DIK_RETURN)) {
			Status = GAME_START;
			GameInit();
		}
		break;
	case GAME_PLAY:
		if (Player->StopTime == 0) {
			Display.Update(Background);
			imageSystem.Update();
			Player->Update(); //Player Move
			Enemy->AllUpdate();
		}else{
			Player->StopTime -= 1;
		}
		
		if (Player->Hp <= 0) { GameLoop = 0; Enemy->deleteAll(); Status = TITLE; }
		if (!Enemy->AllHaveHp()) { LoopWaiting = true; }
		if(LoopFPS >=90){
			GameLoop += 1;
			Enemy->AllInit();
			LoopWaiting = false;
			LoopFPS = 0;
		}
		if (LoopWaiting) { LoopFPS += 1; }
		if (GameLoop > 5) {
			GameLoop = 0;
			Status = GAME_WIN; 
			GameInit();
		}

		//stageHandle.update();
		break;
	case GAME_OVER:
		if (GetKeyboardPress(DIK_RETURN)) { Status = TITLE; }
		break;
	case GAME_WIN:
		imageSystem.Update();
		Player->Update(); //Player Move
		if (GetKeyboardPress(DIK_RETURN)) { Status = TITLE; }
		break;
	default:
		break;
	}
	




	
}

//=========================================
//		描画処理
//=========================================
void	Draw(int fcnt)
{
	//		BackBuffer＆ZBufferのClear
	//		Count	：	pRects配列にある矩形の数
	//		pRects	：	Clearする矩形の配列（NULL指定でView Port矩形全体をClear）
	//		Flags		：	ClearするSurfaceを示すFlag（少なくとも1つを使用しなければならない）
	//						：	「D3DCLEAR_TARGET	ー	Rendering TargetをClearしてColor Parameterの値にする」
	//						：	「D3DCLEAR_ZBUFFER	ー	深度（Z）BufferをClearしてZ Parameterの値にする」
	//						：	「D3DCLEAR_STENCIL	ー	Stencil BufferをClearしてStencil Parameterの値にする」
	//		Color		：	SurfaceをClearする色
	//		Z				：	デプスBufferに保存する値
	//		Stencil	：	Stencil Bufferに保存する値（整数）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//		Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (Status)
		{
		case TITLE:
			imageSystem.TitleDraw();
			//Player->Init(); //player初期化
			break;
		case GAME_PLAY:
			imageSystem.BackDraw();
			//Stair->Draw();
			Enemy->AllDraw();
			Player->Draw();
			imageSystem.UpDraw();
			GameUI.Draw(Player->Hp);
			break;
		case GAME_OVER:
			break;
		case GAME_WIN:
			imageSystem.BackDraw();
			Player->Draw();
			break;
		default:
			break;
		}


		

		

		
		//		Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}
	
	//		Back BufferとFront Bufferの入れ替え
	//		pSourceRect						：	転送元矩形
	//		pDestRect							：	転送先矩形
	//		hDestWindowOverride	：	転送先WindowへのPointer
	//		pDirtyRegion						：	通常はNULLで
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//α blend可能
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//α値＝0.5
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//背景のα値　＝　1-α =0.5

}





//9.12 50MB
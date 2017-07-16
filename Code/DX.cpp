//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		DX API����
//		�j�X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "main.h"
//=========================================
//		Global�ϐ�
//=========================================
extern LPDIRECT3D9					g_pD3D;				//		Direct3D Object
extern LPDIRECT3DDEVICE9	g_pD3DDevice;	//		Device Object�i�`��ɕK�v�j


//=========================================
//		����������
//		hInstance	�F	Instance��Handle
//		hWnd			�F	Window��Handle
//		bWindow	�F	Window Mode�ɂ��邩�ǂ���
//=========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE	d3ddm;

	//		Direct3D Object�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//		
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//		Device��Presentation Parameter�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//		Work��0 Clear
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//		Game���Size�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;					//		Game���Size�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;						//		Color Mode�̎w��
	d3dpp.BackBufferCount = 1;													//		Back Buffer�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			//		�f���M���ɓ�������Clip����
	d3dpp.Windowed = bWindow;												//		Window Mode
	d3dpp.EnableAutoDepthStencil;											//		�f�v�XBuffer�iZBuffer�j��Stencil Buffer�쐬
	d3dpp.AutoDepthStencilFormat;											//		�f�v�XBuffer�Ƃ���16bit���g��

	if (bWindow)
	{//		Window Mode
		d3dpp.FullScreen_RefreshRateInHz = 0;																//		Refresh Late�i�w��ł��Ȃ��̂łO�Œ�j
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;		//		Interval�iVSync��҂����ɕ`��j
	}
	else
	{//		Full Screen Mode
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//		Refresh Late�i���݂̑��x�ɍ��킹��j
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//		Interval�iVSync��҂����ɕ`��j
	}

	//		Device Object�̐���
	//		�uDevice�쐬����v���`�恄�Ɓ����_��������Hardware�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,		//		Display Adapter
		D3DDEVTYPE_HAL,																				//		Device Type
		hWnd,																										//		Focus����Window�ւ�Handle
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						//		Device�쐬����̑g�ݍ��킹
		&d3dpp,																									//		Device��Presentation Parameter
		&g_pD3DDevice)))																				//		Device Interface�ւ�Pointer
	{
		//		��L�̐ݒ肪���s������
		//		�uDevice�쐬����v���`�恄��Hardware�ōs���A�����_��������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,		//		
			D3DDEVTYPE_HAL,																				//		
			hWnd,																										//		
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,						//		
			&d3dpp,																									//		
			&g_pD3DDevice)))
		{
			//		��L�̐ݒ肪���s������
			//		�uDevice�쐬����v���`�恄�Ɓ����_��������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,		//		
				D3DDEVTYPE_REF,																				//		
				hWnd,																										//		
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,						//		
				&d3dpp,																									//		
				&g_pD3DDevice)))
			{
				//		���������s
				return	E_FAIL;
			}
		}
	}

	return S_OK;
}


//=========================================
//		�I������
//=========================================
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{//		Device�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//		Direct3D Object�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
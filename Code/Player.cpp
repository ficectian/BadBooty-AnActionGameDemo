#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
//==========================================================================================================
//		関数定義
//==========================================================================================================

//int	HitSwitch = HITOFF;
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////		上移動関数定義
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//float	UpMove(float X1, float Y1, float W1, float H1) {
//	//各頂点の移動
//	if (Y1 - H1 / 2 > 0)
//	{
//		Y1 -= PLAYERSPEED;
//	}
//	return Y1;
//}
//
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////		左移動関数定義
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//float	LeftMove(float X1, float Y1, float W1, float H1) {
//	//各頂点の移動
//	if (X1 - W1 / 2 > 0)
//	{
//		X1 -= PLAYERSPEED;
//	}
//	return X1;
//}
//
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////		右移動関数定義
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//float	RightMove(float X1, float Y1, float W1, float H1) {
//	//各頂点の移動
//	if (X1 + W1 / 2 < SCREEN_WIDTH)
//	{
//		X1 += PLAYERSPEED;
//	}
//	return X1;
//}
//
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////		下移動関数定義
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//float	DownMove(float X1, float Y1, float W1, float H1) {
//	//各頂点の移動
//	if (Y1 + H1 / 2 <SCREEN_HEIGHT)
//	{
//		Y1 += PLAYERSPEED;
//	}
//	return Y1;
//
//}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		当たり判定処理関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool			HitTest(float X1, float Y1, float W1, float H1, float X2, float Y2, float W2, float H2)
{
	float XX1 = X1 - W1 / 2;
	float	XX2 = X2 - W2 / 2;
	float YY1 = Y1 - H1 / 2;
	float YY2 = Y2 - H2 / 2;

	if (((YY1 + H1 >= YY2) && (YY1 - H2 <= YY2)) && ((XX1 + W1 >= XX2) && (XX1 - W2 <= XX2)))
	{
		return true;
	}
	else
	{
		return	false;
	}

}



//==========================================================================================================
//		定義
//==========================================================================================================


PLAYER Player;

void PLAYER::Init() {
	bool bret = DXLoadTexture(PLAYERTEX, &Tex);
	//bret = DXLoadTexture(BOOWTEX, &DeadTex);
	//bret = DXLoadTexture(INVINCIBLETEX, &InvincibleTex);
	X = 100;
	Y = SCREEN_HEIGHT -120;
	Width = 128;
	Height =128;
	nHp = 6;
	Ustart = 0.0f;
	Uwidth = (float)1 / 8;
	Vstart = 0.0f;
	Vheight = (float)1 / 8;
	FacedRight = true;
	//Anime_style = StationAnime;
	StatusStyle = StationStatus;
	cnt = 0;
	JumpCnt = 0;
	InDoubleJumpStatus = false;
}

void PLAYER::Update() {

	if (nHp > 0) {
		//if (GetKeyboardPress(DIK_W) | GetKeyboardPress(DIK_UP)) {
		//	Y = UpMove(X, Y, Width, Height);					//上移動
		//	if (Anime_style != 1) { Anime_style = 1;  }
		//}
		//
		//if (GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_DOWN)) {
		//	Y = DownMove(X, Y, Width, Height);					//移動
		//	if (Anime_style != 1) {Anime_style = 1; }
		//}
		if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT)) {
			if (FacedRight) {
				if (X - Width / 2 > 0) { X -= PLAYERSPEED / 2; }
				if(StatusStyle != JumpStatus ){ StatusStyle = DefenseStatus; }
			}else{
				if (X - Width / 2 > 0) { X -= PLAYERSPEED; }
				if (StatusStyle != JumpStatus ) {
					if (StatusStyle != RunStatus) {
						cnt = 0;
						StatusStyle = RunStatus;}
				}
			}
		}

		if (GetKeyboardPress(DIK_D)| GetKeyboardPress(DIK_RIGHT))
		{
			if (FacedRight) {
				if (X + Width / 2 < SCREEN_WIDTH){X += PLAYERSPEED;}
				if (StatusStyle != JumpStatus ) {
					if (StatusStyle != RunStatus) {
						cnt = 0; 
						StatusStyle = RunStatus;}
				}
			}else {
				if (X + Width / 2 < SCREEN_WIDTH) { X += PLAYERSPEED/2; }
				if (StatusStyle != JumpStatus ) { StatusStyle = DefenseStatus; }
			}	
		}
		if (GetKeyboardTrigger(DIK_LSHIFT)) {
			FacedRight = !FacedRight;
			if (StatusStyle == RunStatus) { StatusStyle = DefenseStatus;}
			
		}
		

		if (GetKeyboardTrigger(DIK_SPACE)) {
			if (StatusStyle != JumpStatus && !InDoubleJumpStatus) {
				JumpStartY = Y; 
				
				cnt = 0; 
				StatusStyle = JumpStatus;
			}else if (!InDoubleJumpStatus) {
				JumpCnt = 0;
				cnt = 0;
				InDoubleJumpStatus = true;
			}
		}
		 if(GetKeyboardRelease(DIK_A) || GetKeyboardRelease(DIK_LEFT)||GetKeyboardRelease(DIK_D) || GetKeyboardRelease(DIK_RIGHT))
		{
			 if (StatusStyle != JumpStatus) {
				 if (StatusStyle != StationStatus) {  cnt = 0; StatusStyle = StationStatus; }
			 }
			
			 
		 }

	}
	if (StatusStyle == JumpStatus) {
		JumpCnt += 1;
		//float vg = 10 - 0.98f*fcnt;
		Y -= 14 - 0.98f*JumpCnt;;
		if (Y > JumpStartY) {
			Y = JumpStartY;
			JumpCnt = 0;
			StatusStyle = StationStatus;
			JumpStartY = 0.0f;
			InDoubleJumpStatus = false;
		}
	}
	
}

void PLAYER::Draw() {
	const byte *ptAnime = Anime_data[StatusStyle];
	if (*(ptAnime + cnt) == 0xff) { cnt = 0; }
	Ustart = ((*(ptAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((*(ptAnime + cnt)) / (int)(1 / Vheight))*Vheight;
	cnt += 1;
	if (*(ptAnime + cnt) == 0xff) { cnt = 0; }

	if (FacedRight) {
		DXDrawAnimePolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}else {
		DXDrawPlayerRevPolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}
	
}


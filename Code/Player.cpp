#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"

//==========================================================================================================
//		関数定義
//==========================================================================================================

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
		return 	false;
	}

}




//==========================================================================================================
//		定義
//==========================================================================================================
extern DisplayClass Display;
extern ImaginaryBackground Background;
PlayerClass Player;
extern ImageClass Footing[256];
extern byte FootingNum;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player初期化関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Init() {
	bool bret = DXLoadTexture(PLAYERTEX, &Tex);
	//bret = DXLoadTexture(BOOWTEX, &DeadTex);
	//bret = DXLoadTexture(INVINCIBLETEX, &InvincibleTex);
	Initial.x = (float)Display.width / 2;
	Initial.y = (float)(Display.height - 50 - 64);
	X = Initial.x;
	Y = Initial.y;
	DisplayX = X;
	DisplayY = Y;
	MaxHp = 28;
	Hp = MaxHp;
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player落下判定関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			PlayerClass::FallHitTest(float X1, float Y1, float W, float H)
{
	float XX1 = X - 24/ 2;
	if (FacedRight) { 
		XX1 -= 5; 
	}else { 
		XX1 += 5; 
	}//修正
	float	XX2 = X1 - W / 2;
	float YY1 = Y + Height / 2-10;
	float YY2 = Y1 - H / 2;

	if (((YY1 + 10 >= YY2) && (YY1 - H <= YY2)) && ((XX1 + 24 >= XX2) && (XX1 - W <= XX2)))
	{
		return true;
	}
	else
	{
		return 	false;
	}

}

bool PlayerClass::HitStair() {
	extern StairClass StairL[128];
	extern byte StairNum;
	float X1;
	float	X2;
	float Y1;
	float Y2;
	for (int i = 0; i < StairNum; i++) {
		X1 = X - Width / 2;
		X2 = StairL[i].DisplayX - StairL[i].Width / 2;
		Y1 = Y - Height / 2;
		Y2 = StairL[i].DisplayY - StairL[i].Height / 2;
		if (((Y1 + Height >= Y2) && (Y - StairL[i].Height <= Y2)) && ((X1 + Width >= X2) && (X1 - StairL[i].Width <= StairL[i].DisplayX)))
		{
			OnStairNum = i;
			return true;
			break;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Game LoopにPlayer更新関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Update() {
	/*DisplayX = X - Display.MoveDistance.x;
	DisplayY = Y;*/
	if (Hp > 0) {
		if (StatusStyle != AttackStatus) {
			Operation();
			Jump();
		}else {
			Attack();
		}	
		AllHitTest();
	}


	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player描画関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Draw() {
	Animetion();

	if (FacedRight) {
		DXDrawAnimePolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}else {
		DXDrawPlayerRevPolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player操作関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	PlayerClass::Operation() {
	extern StairClass StairL[128];

	//**********************************************************************
	//	Player 移動
	//**********************************************************************
	if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT)) {
		if (FacedRight) {
			if (X - Width / 2 < Display.width / 4 && Display.Fix.x + Display.MoveDistance.x > 10) {
				Display.MoveDistance.x -= PLAYERSPEED / 2;
			}
			else if (X - Width / 2 > 0) { X -= PLAYERSPEED / 2; }
			/*if (X - Width / 2 > 10) {
				X -= PLAYERSPEED / 2;
			}*/
			

			if (StatusStyle != JumpStatus) {
				if (StatusStyle != DefenseStatus) { cnt = 0;  StatusStyle = DefenseStatus; }
			}
		}
		else {
			if (X - Width / 2 < Display.width / 4 && Display.Fix.x + Display.MoveDistance.x > 10) {
				Display.MoveDistance.x -= PLAYERSPEED;
			}
			else if (X - Width / 2 > 0) {
				X -= PLAYERSPEED;
			}

		/*	if (X - Width / 2 < Background.width - 10) {
				X -= PLAYERSPEED;
			}
			*/
			if (StatusStyle != JumpStatus) {
				if (StatusStyle != RunStatus) {
					cnt = 0;
					StatusStyle = RunStatus;
				}
			}
		}
				
			
	}
	
	if (GetKeyboardPress(DIK_D) | GetKeyboardPress(DIK_RIGHT)) {
		if (FacedRight) {
			if (X + Width / 2 > Display.width * 3 / 4 && Display.MoveDistance.x + Display.width <= Background.width - 10) {
				Display.MoveDistance.x += PLAYERSPEED;
			}
			else if (X + Width / 2 < Display.width) { 
				X += PLAYERSPEED;  
				//if (HitStair()) { Y -= PLAYERSPEED*StairL[OnStairNum].Height / StairL[OnStairNum].Width; }
			}
			/*X += PLAYERSPEED;*/
			if (StatusStyle != JumpStatus) {
				if (StatusStyle != RunStatus) {
					cnt = 0;
					StatusStyle = RunStatus;
				}
			}
		}
		else {
			if (X + Width / 2 > Display.width * 3 / 4 && (Display.MoveDistance.x + Display.width) <= Background.width - 10) {
				Display.MoveDistance.x += PLAYERSPEED / 2;
			}
			else if (X + Width / 2 < Display.width) { X += PLAYERSPEED / 2; }
			/*X += PLAYERSPEED / 2;*/
			if (StatusStyle != JumpStatus) { if (StatusStyle != DefenseStatus) { cnt = 0;  StatusStyle = DefenseStatus; } }
		}
	}

	//**********************************************************************
	//	Player 攻撃
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_H)) {
		if (StatusStyle != JumpStatus) {
			cnt = 0;
			StatusStyle = AttackStatus;
			Display.ShockOn = true;
		}
	}

	//**********************************************************************
	//	Player 転身
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_LSHIFT)) {
		FacedRight = !FacedRight;
		if (StatusStyle == RunStatus) { StatusStyle = DefenseStatus; }
	}

	//**********************************************************************
	//	Player 　jump
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_SPACE)) {
		if (StatusStyle != JumpStatus && !InDoubleJumpStatus) {
			JumpStartY = Initial.y;
			JumpCnt = 0;
			cnt = 0;
			StatusStyle = JumpStatus;
		}
		else if (!InDoubleJumpStatus) {
			JumpCnt = 0;
			cnt = 0;
			InDoubleJumpStatus = true;
		}
	}

	//**********************************************************************
	//	停止
	//**********************************************************************
	if (GetKeyboardRelease(DIK_A) || GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_D) || GetKeyboardRelease(DIK_RIGHT))
	{
		if (StatusStyle != JumpStatus) {
			if (StatusStyle != StationStatus) { cnt = 0; StatusStyle = StationStatus; }
		}
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player jumpと落下処理関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Jump() {
	if (StatusStyle == JumpStatus) {
		JumpCnt += 1;
		//float vg = 10 - 0.98f*fcnt;
		Y -= 14 - 0.98f*JumpCnt;;
		const byte *ptAnime = Anime_data[StatusStyle];

		if (Y > JumpStartY) {
			Y = JumpStartY;
			JumpCnt = 0;
			cnt = 0;
			JumpStartY = 0.0f;
			InDoubleJumpStatus = false;
			StatusStyle = StationStatus;
			//Display.ShockOn = true;
		}
		if (*(ptAnime + cnt) == 18) {
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)/*HitTest(, Y, 20, Height, Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)*/) {
					Y = Footing[i].DisplayY - Footing[i].Height / 2 - Height / 2 + 10;

					JumpCnt = 0;
					cnt = 0;
					JumpStartY = 0.0f;
					InDoubleJumpStatus = false;
					StatusStyle = StationStatus;
				}
			}
		}
	}
	else {
		//落下
		if (Y != Initial.y /*&& !HitStair()*/) {
			InFall = true;
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)) {
					InFall = false;
					break;
				}
			}
			if (InFall) {
				JumpStartY = Initial.y;
				JumpCnt = 16;
				cnt = 16;
				StatusStyle = JumpStatus;
			}

		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player 攻撃処理関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Attack() {
	const byte *ptAnime = Anime_data[StatusStyle];
	cnt += 1;
	if (*(ptAnime + cnt) == 0xff) {
		cnt = 0;
		StatusStyle = StationStatus;
	}
	else { cnt -= 1; }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player Animetion処理関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Animetion() {
	const byte *ptAnime = Anime_data[StatusStyle];
	if (*(ptAnime + cnt) == 0xff) {

		if (StatusStyle == JumpStatus) {
			cnt = 16;
		}
		else {
			cnt = 0;
		}
	}
	Ustart = ((*(ptAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((*(ptAnime + cnt)) / (int)(1 / Vheight))*Vheight;
	cnt += 1;
}
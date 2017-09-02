//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		Player èàóùä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"
#include "Quantitative.h"
//==========================================================================================================
//		ä÷êîíËã`
//==========================================================================================================
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////		ìñÇΩÇËîªíËèàóùä÷êîíËã`
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//bool			HitTest(float X1, float Y1, float W1, float H1, float X2, float Y2, float W2, float H2)
//{
//	float XX1 = X1 - W1 / 2;
//	float	XX2 = X2 - W2 / 2;
//	float YY1 = Y1 - H1 / 2;
//	float YY2 = Y2 - H2 / 2;
//
//	if (((YY1 + H1 >= YY2) && (YY1 - H2 <= YY2)) && ((XX1 + W1 >= XX2) && (XX1 - W2 <= XX2)))
//	{
//		return true;
//	}
//	else
//	{
//		return 	false;
//	}
//
//}

//==========================================================================================================
//		íËã`
//==========================================================================================================
PlayerClass Player;
extern DisplayClass Display;
extern ImaginaryBackground Background;
extern ImageClass Footing[256];
extern byte FootingNum;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Playerèâä˙âªä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Init() {
	bool bret = DXLoadTexture(PLAYERTEX, &Tex);
	//bret = DXLoadTexture(BOOWTEX, &DeadTex);
	//bret = DXLoadTexture(INVINCIBLETEX, &InvincibleTex);
	Initial.x = 100+(float)Display.width / 2;
	Initial.y = (float)(Background.height - InitialPlayerHeight - 64- BleedSize);
	X = Initial.x;
	Y = Initial.y;
	DisplayX = X;
	DisplayY = Y;
	MaxHp = 28;
	Hp = MaxHp;
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Game LoopÇ…PlayerçXêVä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Update() {
	//**********************************************************************
	//	ï`âÊç¿ïWÇÃçXêV
	//**********************************************************************
	DisplayX = X - Display.MoveDistance.x;
	DisplayY = Y - Display.MoveDistance.y;

	if (InvincibleTime != 0) { InvincibleTime -= 1; }  //	ñ≥ìGéûä‘ÇÃèàóù
	if (Hp > 0) {
		Climb();
		if (StatusStyle != ClimbStatus) {
			if (StatusStyle == AttackStatus) {
				Attack();

			}
			else if (StatusStyle == HitStatus) {
				Hit();
			}
			else {
				Operation();
				Jump();
			}
		}
		
		AllHitTest();
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Playerï`âÊä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Draw() {
	Animetion();

	if (FacedRight) {
		DXDrawAnimePolygon(DisplayX, DisplayY, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}else {
		DXDrawPlayerRevPolygon(DisplayX, DisplayY, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	PlayerëÄçÏä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	PlayerClass::Operation() {
	extern StairClass StairL[128];



	
		//**********************************************************************
		//	Player ñhå‰
		//**********************************************************************
		if (GetKeyboardPress(DIK_LSHIFT)) {
			if (StatusStyle != JumpStatus) {
				if (StatusStyle != DefenseStatus) {
					cnt = 0;
					StatusStyle = DefenseStatus;
				}
			}
			//**********************************************************************
			//	Player ñhå‰à⁄ìÆ
			//**********************************************************************
			if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT)) {
				/*if (!FacedRight) {
				FacedRight = !FacedRight;
				X += 64;
				}*/
				X -= PLAYERSPEED / 2;
				MoveHit();
			}
			else if (GetKeyboardPress(DIK_D) | GetKeyboardPress(DIK_RIGHT)) {
				/*if (FacedRight) {
				FacedRight = !FacedRight;
				X -= 64;
				}*/
				X += PLAYERSPEED / 2;
				MoveHit();
			}
			else {
				cnt = 0;
			}
		}
		else
		{
			//**********************************************************************
			//	Player à⁄ìÆ
			//**********************************************************************
			if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT)) {
				if (FacedRight) {
					FacedRight = !FacedRight;
					X -= 28;
				}
				X -= PLAYERSPEED;
				MoveHit();
				if (StatusStyle != JumpStatus) {
					if (StatusStyle != RunStatus) {
						cnt = 0;
						StatusStyle = RunStatus;
					}
				}

			}

			if (GetKeyboardPress(DIK_D) | GetKeyboardPress(DIK_RIGHT)) {
				if (!FacedRight) {
					FacedRight = !FacedRight;
					X += 28;
				}
				X += PLAYERSPEED;
				MoveHit();
				if (StatusStyle != JumpStatus) {
					if (StatusStyle != RunStatus) {
						cnt = 0;
						StatusStyle = RunStatus;
					}
				}
			}
		}



		//**********************************************************************
		//	Player çUåÇ
		//**********************************************************************
		if (GetKeyboardTrigger(DIK_H)) {
			if (StatusStyle != JumpStatus) {
				cnt = 0;
				StatusStyle = AttackStatus;
			}
		}

		//**********************************************************************
		//	Player Å@jump
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
		//	í‚é~
		//**********************************************************************
		if (GetKeyboardRelease(DIK_LSHIFT) || GetKeyboardRelease(DIK_A) || GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_D) || GetKeyboardRelease(DIK_RIGHT))
		{
			if (StatusStyle != JumpStatus) {
				if (StatusStyle != StationStatus) { cnt = 0; StatusStyle = StationStatus; }
			}
		}
	
	

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player jumpÇ∆óéâ∫èàóùä÷êîíËã`
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
		}
		if (*(ptAnime + cnt) == 18) {
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].X, Footing[i].Y, Footing[i].Width, Footing[i].Height)) {
					Y = Footing[i].Y - Footing[i].Height / 2 - Height / 2 + 10;

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
		//óéâ∫
		if (Y != Initial.y /*&& !HitStair()*/) {
			InFall = true;
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].X, Footing[i].Y, Footing[i].Width, Footing[i].Height)) {
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
//	Player çUåÇèàóùä÷êîíËã`
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
//	Player Animetionèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Animetion() {
	const byte *ptAnime = Anime_data[StatusStyle];
	if (*(ptAnime + cnt) == 0xff) {
		//cnt = 0;
		if (StatusStyle != JumpStatus) {
			cnt = 0;
		}
		else {
			cnt = 16;
		}
	}
	Ustart = ((*(ptAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((*(ptAnime + cnt)) / (int)(1 / Vheight))*Vheight;
	if (StatusStyle != ClimbStatus) { cnt += 1; }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player damageéÛÇØÇÈäJénä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	PlayerClass::HitOn() {
	if (Display.ShockOn == 0) {
		Display.ShockOn = 2;
	}
		
		HitCnt = 0;
		cnt = 0;
		StatusStyle = HitStatus;
		InvincibleTime = 30;
		JumpStartY = Initial.y;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player damageéÛÇØÇÈèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Hit() {
	HitCnt += 1;

	if (EnemyInPlayerRight) {
		X -= PLAYERSPEED;
		BoundaryHitTest();
	}
	else
	{
		X += PLAYERSPEED;
		BoundaryHitTest();
	}
	Y -= 10 - 0.98f*HitCnt;
	if (Y > JumpStartY) {
		Y = JumpStartY;
		HitCnt = 0;
		cnt = 0;
		Hp -= 3;
		StatusStyle = StationStatus;
		InDoubleJumpStatus = false;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player èàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Climb() {
	const byte *ptAnime = Anime_data[StatusStyle];
	//**********************************************************************
	//	Player ìoÇÈ
	//**********************************************************************
	if (StatusStyle != ClimbStatus) {
		if (GetKeyboardPress(DIK_W) | GetKeyboardPress(DIK_UP)) {
			cnt = 0; 
			StatusStyle = ClimbStatus; 
			Y -= 20;
		}
		if (GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_DOWN)) {
			cnt = 0; 
			StatusStyle = ClimbStatus; 
			Y += 20;
		}
	}else{
		if (GetKeyboardPress(DIK_W) | GetKeyboardPress(DIK_UP)) {
			cnt += 1;
			if ((*(ptAnime + cnt) != *(ptAnime + cnt - 1)) && ((*(ptAnime + cnt) == 40) || (*(ptAnime + cnt) == 42) || (*(ptAnime + cnt) == 0xff))) {
				Y -= 20;
			}
		}
		if (GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_DOWN)) {
			cnt += 1;
			if ((*(ptAnime + cnt) != *(ptAnime + cnt - 1)) && ((*(ptAnime + cnt) == 40) || (*(ptAnime + cnt) == 42) || (*(ptAnime + cnt) == 0xff))) {
				Y += 20;
			}
		}

		//óéâ∫
		if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT) | GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_RIGHT) | GetKeyboardPress(DIK_SPACE)) {
			if (Y != Initial.y /*&& !HitStair()*/) {
				InFall = true;
				for (int i = 0; i < FootingNum; i++) {
					if (Player.FallHitTest(Footing[i].X, Footing[i].Y, Footing[i].Width, Footing[i].Height)) {
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
	
}

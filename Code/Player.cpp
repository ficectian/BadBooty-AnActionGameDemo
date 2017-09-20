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
//		íËã`
//==========================================================================================================
PlayerClass *Player;

extern DisplayClass Display;
extern ImaginaryBackground Background;
//extern ImageClass Footing[256];
//extern byte FootingNum;
extern ImageSystem imageSystem;

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
	attackMod = defaultMod;
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
			else if (StatusStyle == EvilHitStatus) {
				EvilHit();
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
	if (AnimeCnt() == 57|| AnimeCnt() == 59)
	{
		if (FacedRight) {
			DXDrawAnimePolygon(DisplayX+ Width, DisplayY, 0, Width, Height, Ustart+ Uwidth, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
		}
		else {
			DXDrawPlayerRevPolygon(DisplayX- Width, DisplayY, 0, Width, Height, Ustart + Uwidth, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
		}
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
		if (GetKeyboardPress(DIK_LSHIFT) | GetKeyboardPress(DIK_K)) {
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
		if (GetKeyboardTrigger(DIK_H) | GetKeyboardTrigger(DIK_Z)) {
			if (StatusStyle != JumpStatus) {
				cnt = 0;
				StatusStyle = AttackStatus;
			}
		}
		//**********************************************************************
		//	Player çUåÇ
		//**********************************************************************
		if (GetKeyboardTrigger(DIK_J) | GetKeyboardTrigger(DIK_X)) {
			if (StatusStyle != JumpStatus) {
				cnt = 0;
				StatusStyle = EvilHitStatus;
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
		if (GetKeyboardRelease(DIK_K) || GetKeyboardRelease(DIK_LSHIFT) || GetKeyboardRelease(DIK_A) || GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_D) || GetKeyboardRelease(DIK_RIGHT))
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
		if (*(ptAnime + cnt) == 19 || *(ptAnime + cnt) == 20) {
			for (int i = 0; i < imageSystem.FootingNum; i++) {
				if (Player->FallHitTest(imageSystem.Footing[i].X, imageSystem.Footing[i].Y, imageSystem.Footing[i].Width, imageSystem.Footing[i].Height)) {
					Y = imageSystem.Footing[i].Y - imageSystem.Footing[i].Height / 2 - Height / 2 + 10;

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
			for (int i = 0; i < imageSystem.FootingNum; i++) {
				if (Player->FallHitTest(imageSystem.Footing[i].X, imageSystem.Footing[i].Y, imageSystem.Footing[i].Width, imageSystem.Footing[i].Height)) {
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
	//const byte *ptAnime = Anime_data[StatusStyle];
	//cnt += 1;
	//if (*(ptAnime + cnt) == 0xff) {
	//	cnt = 0;
	//	StatusStyle = StationStatus;
	//}
	//else { cnt -= 1; }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player EvilHitèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::EvilHit() {
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

	if (StatusStyle != ClimbStatus) { cnt += 1; }

	if (AnimeCnt() == 0xff) {
		//c
		if (StatusStyle == AttackStatus)
		{
			StatusStyle = StationStatus;
			cnt = 0;
		}
		if (StatusStyle != JumpStatus) {
			cnt = 0;
		}
		else {
			cnt = 16;
		}
	}
	Ustart = ((AnimeCnt()) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((AnimeCnt()) / (int)(1 / Vheight))*Vheight;
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
//	Player ìoÇÈèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Climb() {
	const byte *ptAnime = Anime_data[StatusStyle];
	extern StairClass StairL[128];
	extern byte StairNum;
	bool ladderHit = false;
	//**********************************************************************
	//	Player ìoÇÈ
	//**********************************************************************
	if (StatusStyle != ClimbStatus) {
		for (int i = 0; i < StairNum; i++) {
				if (HitTest(X,Y,Width,Height,StairL[i].X,StairL[i].Y,StairL[i].Width,StairL[i].Height)){
					ladderHit = true;
				}
		}
		if (ladderHit) {
			if (GetKeyboardPress(DIK_W) | GetKeyboardPress(DIK_UP)&& ((Y - Height / 2) > StairL[0].Y)) {
				cnt = 0;
				StatusStyle = ClimbStatus;
				Y -= 20;
				X = StairL[0].X;
			}
			if (GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_DOWN)&& ((Y + Height / 2) < StairL[StairNum - 1].Y)) {
				cnt = 0;
				StatusStyle = ClimbStatus;
				Y += 20;
				X = StairL[0].X;
			}
		}
		
	}else{
		if (GetKeyboardPress(DIK_W) | GetKeyboardPress(DIK_UP)) {
			cnt += 1;
			if ((*(ptAnime + cnt) != *(ptAnime + cnt - 1)) && ((*(ptAnime + cnt) == 40) || (*(ptAnime + cnt) == 42) || (*(ptAnime + cnt) == 0xff))) {
				if ((Y - Height / 2) > StairL[0].Y) {
					Y -= 25;
				}
			}
		}
		if (GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_DOWN)) {
			cnt += 1;
			if ((*(ptAnime + cnt) != *(ptAnime + cnt - 1)) && ((*(ptAnime + cnt) == 40) || (*(ptAnime + cnt) == 42) || (*(ptAnime + cnt) == 0xff))) {
				if ((Y + Height / 2) < StairL[StairNum-1].Y) {
					Y += 25;
				}else {
					ladderHit = false;
					if (Y != Initial.y /*&& !HitStair()*/) {
						InFall = true;
						for (int i = 0; i < imageSystem.FootingNum; i++) {
							if (Player->FallHitTest(imageSystem.Footing[i].X, imageSystem.Footing[i].Y, imageSystem.Footing[i].Width, imageSystem.Footing[i].Height)) {
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

		if (GetKeyboardPress(DIK_SPACE)) {
			ladderHit = false;
			Y += 30;
			JumpStartY = Initial.y;
			JumpCnt = 0;
			cnt = 0;
			InDoubleJumpStatus = false;
			StatusStyle = JumpStatus;
		}/*else if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT) | GetKeyboardPress(DIK_S) | GetKeyboardPress(DIK_RIGHT)) {
			ladderHit = false;
			if (Y != Initial.y ) {
				InFall = true;
				for (int i = 0; i < imageSystem.FootingNum; i++) {
					if (Player->FallHitTest(imageSystem.Footing[i].X, imageSystem.Footing[i].Y, imageSystem.Footing[i].Width, imageSystem.Footing[i].Height)) {
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
		}*/
	}
	
}

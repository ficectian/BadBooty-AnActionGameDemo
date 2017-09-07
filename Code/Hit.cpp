//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		“–‚½‚è”»’èŠÖ”
//		—j•X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
//#include "Hit.h"
#include "Quantitative.h"

//==========================================================================================================
//		‘S‚Ä‚ÌPlayer‚ÉŠÖ‚·‚é“–‚½‚è”»’èˆ—’è‹`
//==========================================================================================================
void PlayerClass::AllHitTest() {
	extern DisplayClass Display;  //  ‰¼‘zcamera‘ã“ü
	extern EnemyClass SwordEnemy[64];	// Œ•“G‘ã“ü
	extern byte SwordEnemyNum;	// Œ•“G”‘ã“ü

	const byte *ptAnime = Anime_data[StatusStyle];	// ŒvZ—pPlayer Animation Cnt

	//**********************************************************************
	//	“G‚ÉUŒ‚‚Ì“–‚½‚è”»’è
	//**********************************************************************
	if (*(ptAnime + cnt) == 33 || *(ptAnime + cnt) == 34) {
		// 	Œ•“G‚ÉUŒ‚‚Ì“–‚½‚è”»’è
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0) {
				if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 5;
						SwordEnemy[i].HitOn();
					}  // –³“GŠÔ“à‚Å‚Í‚È‚¢
				}  // “G‚É“–‚½‚é
			}  // “G‚ª¶‚«‚Ä‚¢‚é
		}
	}
	//**********************************************************************
	//	“G‚ÉEvilHit‚Ì“–‚½‚è”»’è
	//**********************************************************************
	if (*(ptAnime + cnt) == 50 || *(ptAnime + cnt) == 51) {
		// 	Œ•“G‚ÉUŒ‚‚Ì“–‚½‚è”»’è
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0 && SwordEnemy[i].Hp <= SwordEnemy[i].MaxHp*2/5) {
				if (EvilHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 10;
						SwordEnemy[i].EvilOn();
						Hp += SwordEnemy[i].Hp * 4;
						if (Hp > MaxHp) { Hp = MaxHp; }
					}  // –³“GŠÔ“à‚Å‚Í‚È‚¢
				}  // “G‚É“–‚½‚é
			}  // “G‚ª¶‚«‚Ä‚¢‚é
		}
	}
	//**********************************************************************
	//	“G‚Édamageó‚¯‚Ì“–‚½‚è”»’è
	//**********************************************************************
	// 	Œ•“G‚Édamageó‚¯‚Ì“–‚½‚è”»’è
	for (int i = 0; i < SwordEnemyNum; i++)
	{
		if (SwordEnemy[i].Hp > 0) {
			if (SwordEnemy[i].AnimeCnt() == 5 || SwordEnemy[i].AnimeCnt() == 6) {
				if (HitHit(SwordEnemy[i].AttBox_X(), SwordEnemy[i].AttBox_Y(), SwordEnemy[i].AttBox_Wdith, SwordEnemy[i].AttBox_Height)) {
					if (InvincibleTime == 0) {
						if (StatusStyle != HitStatus) {
							if ((StatusStyle == DefenseStatus) &&( (X < SwordEnemy[i].X && FacedRight) || (X > SwordEnemy[i].X && !FacedRight))) {
								// –hŒä‚·‚ê‚Î
								if (Display.ShockOn == 0) {Display.ShockOn = 1;}
								InvincibleTime = 30;
								Hp -= 1;
							}else {
								// –hŒä‚µ‚Ä‚¢‚È‚¢
								if (X < SwordEnemy[i].X) {EnemyInPlayerRight = true;}else {
									EnemyInPlayerRight = false;} // “G•ûˆÊ”»’è
								HitOn();
							}
						}
					}  // –³“GŠÔ“à‚Å‚Í‚È‚¢
				}  // Player‚É“–‚½‚é
			}  // “GUŒ‚Cnt‚Ì
		}  // “G‚ª¶‚«‚Ä‚¢‚é
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	PlayerˆÚ“®“–‚½‚è”»’èŠÖ”’è‹`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::MoveHit() {
	extern EnemyClass SwordEnemy[64];  // Œ•“G‘ã“ü
	extern byte SwordEnemyNum;	// Œ•“G”‘ã“ü
	
	// 	Œ•“G‚É“–‚½‚è”»’è
	for (int i = 0; i < SwordEnemyNum; i++){
		if (SwordEnemy[i].Hp > 0) {
			if (SwordEnemy[i].PlayerHit()) {
				if (HitBox_X() < SwordEnemy[i].HitBox_X()) { 
					X -= PLAYERSPEED; 
				}else {
					X += PLAYERSPEED;
				}
				return true;
			}
		}  // “G‚ª¶‚«‚Ä‚¢‚é
	}
	if(BoundaryHitTest()){ return true; }
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Map“–‚½‚è”»’èŠÖ”’è‹`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::BoundaryHitTest() {
	extern ImaginaryBackground Background;
	if (X - Width / 2 < BleedSize) {
		X += PLAYERSPEED;
		return true;
	}else if (X + Width / 2 > Background.width - BleedSize)	{
		X -= PLAYERSPEED;
		return true;
	}
	return false;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player—‰º”»’èŠÖ”’è‹`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			PlayerClass::FallHitTest(float X1, float Y1, float W, float H)
{
	float XX1 = X - 24 / 2;
	if (FacedRight) {
		XX1 -= 5;
	}
	else {
		XX1 += 5;
	}//C³
	float	XX2 = X1 - W / 2;
	float YY1 = Y;
	float YY2 = Y1 - H / 2;

	if (((YY1 + 64 >= YY2) && (YY1 - H <= YY2)) && ((XX1 + 24 >= XX2) && (XX1 - W <= XX2)))
	{
		return true;
	}
	else
	{
		return 	false;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	PlayerŠK’i”»’èŠÖ”’è‹`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::HitStair() {
	extern StairClass StairL[64];
	extern byte StairNum;
	float X1;
	float	X2;
	float Y1;
	float Y2;
	for (int i = 0; i < StairNum; i++) {
		X1 = X - Width / 2;
		X2 = StairL[i].X - StairL[i].Width / 2;
		Y1 = Y - Height / 2;
		Y2 = StairL[i].Y - StairL[i].Height / 2;
		if (((Y1 + Height >= Y2) && (Y - StairL[i].Height <= Y2)) && ((X1 + Width >= X2) && (X1 - StairL[i].Width <= StairL[i].X)))
		{
			OnStairNum = i;
			return true;
			break;
		}
	}
	return false;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		当たり判定関数
//		曜氷
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
//#include "Hit.h"
#include "Quantitative.h"

//==========================================================================================================
//		全てのPlayerに関する当たり判定処理定義
//==========================================================================================================
void PlayerClass::AllHitTest() {
	extern DisplayClass Display;  //  仮想camera代入
	extern EnemyClass SwordEnemy[64];	// 剣敵代入
	extern byte SwordEnemyNum;	// 剣敵数代入

	const byte *ptAnime = Anime_data[StatusStyle];	// 計算用Player Animation Cnt

	//**********************************************************************
	//	敵に攻撃の当たり判定
	//**********************************************************************
	if (*(ptAnime + cnt) == 33 || *(ptAnime + cnt) == 34) {
		// 	剣敵に攻撃の当たり判定
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0) {
				if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 5;
						SwordEnemy[i].HitOn();
					}  // 無敵時間内ではない
				}  // 敵に当たる
			}  // 敵が生きている
		}
	}
	//**********************************************************************
	//	敵に攻撃の当たり判定
	//**********************************************************************
	if (*(ptAnime + cnt) == 57 || *(ptAnime + cnt) == 59) {
		// 	剣敵に攻撃の当たり判定
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0) {
				if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 5;
						SwordEnemy[i].HitOn();
					}  // 無敵時間内ではない
				}  // 敵に当たる
			}  // 敵が生きている
		}
	}
	//**********************************************************************
	//	敵にEvilHitの当たり判定
	//**********************************************************************
	if (*(ptAnime + cnt) == 50 || *(ptAnime + cnt) == 51) {
		// 	剣敵に攻撃の当たり判定
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0 && SwordEnemy[i].Hp <= SwordEnemy[i].MaxHp*2/5) {
				if (EvilHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 10;
						SwordEnemy[i].EvilOn();
						attackMod = swordMod;
						Hp += SwordEnemy[i].Hp * 2;
						if (Hp > MaxHp) { Hp = MaxHp; }
					}  // 無敵時間内ではない
				}  // 敵に当たる
			}  // 敵が生きている
		}
	}
	//**********************************************************************
	//	敵にdamage受けの当たり判定
	//**********************************************************************
	// 	剣敵にdamage受けの当たり判定
	for (int i = 0; i < SwordEnemyNum; i++)
	{
		if (SwordEnemy[i].Hp > 0) {
			if (SwordEnemy[i].AnimeCnt() == 5 || SwordEnemy[i].AnimeCnt() == 6) {
				if (HitHit(SwordEnemy[i].AttBox_X(), SwordEnemy[i].AttBox_Y(), SwordEnemy[i].AttBox_Wdith, SwordEnemy[i].AttBox_Height)) {
					if (InvincibleTime == 0) {
						if (StatusStyle != HitStatus) {
							if ((StatusStyle == DefenseStatus) &&( (X < SwordEnemy[i].X && FacedRight) || (X > SwordEnemy[i].X && !FacedRight))) {
								// 防御すれば
								if (Display.ShockOn == 0) {Display.ShockOn = 1;}
								InvincibleTime = 30;
								Hp -= 1;
							}else {
								// 防御していない
								if (X < SwordEnemy[i].X) {EnemyInPlayerRight = true;}else {
									EnemyInPlayerRight = false;} // 敵方位判定
								HitOn();
							}
						}
					}  // 無敵時間内ではない
				}  // Playerに当たる
			}  // 敵攻撃Cntの時
		}  // 敵が生きている
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player移動当たり判定関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::MoveHit() {
	extern EnemyClass SwordEnemy[64];  // 剣敵代入
	extern byte SwordEnemyNum;	// 剣敵数代入
	
	// 	剣敵に当たり判定
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
		}  // 敵が生きている
	}
	if(BoundaryHitTest()){ return true; }
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Map当たり判定関数定義
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
//	Player落下判定関数定義
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			PlayerClass::FallHitTest(float X1, float Y1, float W, float H)
{
	float XX1 = X - 24 / 2;
	if (FacedRight) {
		XX1 -= 5;
	}
	else {
		XX1 += 5;
	}//修正
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
//	Player階段判定関数定義
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


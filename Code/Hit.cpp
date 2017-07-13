#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
//#include "Hit.h"

void PlayerClass::AllHitTest() {
	extern DisplayClass Display;

	extern EnemyClass SwordEnemy[64];
	extern byte SwordEnemyNum;
	const byte *ptAnime = Anime_data[StatusStyle];

	//att
	if (*(ptAnime + cnt) == 33 || *(ptAnime + cnt) == 34) {
		for (int i = 0; i < SwordEnemyNum; i++)
		{

			if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
				if (SwordEnemy[i].InvincibleTime == 0) {
					StopTime = 5;
					SwordEnemy[i].HitOn();
				}
			}
		}
	}


	//hit
	for (int i = 0; i < SwordEnemyNum; i++)
	{
		if (SwordEnemy[i].AnimeCnt() == 5 || SwordEnemy[i].AnimeCnt() == 6) {
			if (HitHit(SwordEnemy[i].AttBox_X(), SwordEnemy[i].AttBox_Y(), SwordEnemy[i].AttBox_Wdith, SwordEnemy[i].AttBox_Height)) {
				if (SwordEnemy[i].InvincibleTime == 0) {
					if (StatusStyle != HitStatus && StatusStyle != DefenseStatus) {
						
						HitOn();
					}
					
				}
			}
		}
		
	}
}

bool PlayerClass::MoveHit() {
	extern EnemyClass SwordEnemy[64];
	extern byte SwordEnemyNum;
	for (int i = 0; i < SwordEnemyNum; i++){
		if (SwordEnemy[i].PlayerHit()) { 
			if (HitBox_X() < SwordEnemy[i].HitBox_X()) { X -= PLAYERSPEED; }else {
					X += PLAYERSPEED;
			}
			return true; }
	}

	return false;
}
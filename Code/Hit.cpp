#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
//#include "Hit.h"

void PlayerClass::AllHitTest() {
	extern EnemyClass SwordEnemy[64];
	extern byte SwordEnemyNum;
	extern PlayerClass Player;
	const byte *ptAnime = Anime_data[StatusStyle];
	float x2;
	float y2;
	
	if (*(ptAnime + cnt) == 33 || *(ptAnime + cnt) == 34) {
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			
				if (SwordEnemy[i].FacedLeft) {
					x2 = SwordEnemy[i].DisplayX - 3;
				}
				else {
					x2 = SwordEnemy[i].DisplayX - 35;
				}
				y2 = SwordEnemy[i].DisplayY - 39;

				if (AttHit(x2, y2, SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 5;
						SwordEnemy[i].HitOn();
					}
				}
			/*if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
				SwordEnemy[i].Hp -= 1;
				SwordEnemy[i].HitOn();
			}*/
		}
	}

}
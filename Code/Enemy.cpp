#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
//#include "input.h"
#include "Background.h"


EnemyClass *Enemy;
EnemyClass SwordEnemy[64];
byte SwordEnemyNum;
extern DisplayClass Display;
extern ImaginaryBackground Background;

void	EnemyClass::AllInit() {
	bool bret = DXLoadTexture(ENEMYTEX, &SwordEnemy[0].Tex);
	SwordEnemyNum = 1;
	SwordEnemy[0].Width = 128;
	SwordEnemy[0].Height = 128;
	SwordEnemy[0].InitialX = 1200;
	SwordEnemy[0].InitialY=(float)(Display.height - 50 - SwordEnemy[0].Height/2);
	SwordEnemy[0].X = SwordEnemy[0].InitialX;
	SwordEnemy[0].Y = SwordEnemy[0].InitialY;
	SwordEnemy[0].DisplayX = SwordEnemy[0].X;
	SwordEnemy[0].DisplayY = SwordEnemy[0].Y;
	
	SwordEnemy[0].Hp = 5;
	SwordEnemy[0].Ustart = 0.0f;
	SwordEnemy[0].Uwidth = (float)1 / 4;
	SwordEnemy[0].Vstart = 0.0f;
	SwordEnemy[0].Vheight = (float)1 / 4;
	SwordEnemy[0].FacedLeft = true;
	SwordEnemy[0].StatusStyle = EnemyRunAnime;
	SwordEnemy[0].cnt = 0;
	SwordEnemy[0].ActionMod = PatrolMod;
}
void EnemyClass::AllUpdate() {
	Display.Update(Background);

	for (int i = 0; i < SwordEnemyNum; i++) {
		//SwordEnemy[i].Sync(Display);
		SwordEnemy[i].DisplayX = SwordEnemy[i].X - Display.MoveDistance.x;
		SwordEnemy[i].DisplayY = SwordEnemy[i].Y;
		SwordEnemy[i].Update();
	}
}
void	EnemyClass::AllDraw() {
	for (int i = 0; i < SwordEnemyNum; i++) {
		if (SwordEnemy[i].Hp > 0) {
			SwordEnemy[i].Draw();
		}
	}
}
void EnemyClass::Animetion() {
	const byte *ptAnime = Anime_data[StatusStyle];
	if (*(ptAnime + cnt) == 0xff) {cnt = 0;}
	Ustart = ((*(ptAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((*(ptAnime + cnt)) / (int)(1 / Vheight))*Vheight;
	cnt += 1;
}

void EnemyClass::Draw() {
	Animetion();

	if (FacedLeft) {
		DXDrawAnimePolygon(DisplayX,DisplayY, 0, Width, Height,Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
	}
	else {
		DXDrawPlayerRevPolygon(DisplayX, DisplayY, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex); 
	}
}

void EnemyClass::Patrol() {
	if (FacedLeft) {
		X -= SWORDENEMYSPEED;
		if (X < InitialX - 150 || X <= 0) {
			X += SWORDENEMYSPEED*2;
			FacedLeft = !FacedLeft;
		}
	}else{
		X += SWORDENEMYSPEED;
		if (X > InitialX + 150 || X >= Background.width) {
			X -= SWORDENEMYSPEED*2;
			FacedLeft = !FacedLeft;
		}
	}

	
}

void	EnemyClass::Update() {
	if (InvincibleTime != 0) { InvincibleTime -= 1; }
	switch (ActionMod)
	{
	case PatrolMod:
		Patrol();
		break;
	case HitMod:
		Hit();
		break;
	default:
		break;
	}
}

void	EnemyClass::HitOn() {
		Hp -= 1;

		HitCnt = 0;
		cnt = 0;
		StatusStyle = EnemyHitAnime;
		ActionMod = HitMod;
		InvincibleTime = 30;

}

void EnemyClass::Hit() {
	extern PlayerClass Player;
	HitCnt += 1;
	if (Player.X <= X) {
		X += 4;
	}
	else
	{
		X -= 4;
	}
	Y -= 10 -0.98f*HitCnt;
	if (Y > InitialY) {
		Y = InitialY;
		HitCnt = 0;
		cnt = 0;
		StatusStyle = EnemyRunAnime;
		ActionMod = PatrolMod;
	}
	
}
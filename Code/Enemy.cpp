#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
//#include "input.h"
#include "Background.h"


EnemyClass *Enemy;
EnemyClass SwordEnemy[10];
byte SwordEnemyNum;
extern DisplayClass Display;
extern ImaginaryBackground Background;

void	EnemyClass::AllInit() {
	bool bret = DXLoadTexture(ENEMYTEX, &SwordEnemy[0].Tex);
	SwordEnemyNum = 1;
	/*SwordEnemy[0].Width = 128;
	SwordEnemy[0].Height = 128;*/
	SwordEnemy[0].InitialX = 1200;
	SwordEnemy[0].InitialY=(float)(Display.height - 50 - SwordEnemy[0].Height/2);
	SwordEnemy[0].X = SwordEnemy[0].InitialX;
	SwordEnemy[0].Y = SwordEnemy[0].InitialY;
	SwordEnemy[0].DisplayX = SwordEnemy[0].X;
	SwordEnemy[0].DisplayY = SwordEnemy[0].Y;
	
	/*SwordEnemy[0].Hp = 5;
	SwordEnemy[0].Ustart = 0.0f;
	SwordEnemy[0].Uwidth = (float)1 / 4;
	SwordEnemy[0].Vstart = 0.0f;
	SwordEnemy[0].Vheight = (float)1 / 4;
	SwordEnemy[0].FacedLeft = true;
	SwordEnemy[0].StatusStyle = EnemyRunAnime;
	SwordEnemy[0].cnt = 0;
	SwordEnemy[0].ActionMod = PatrolMod;*/
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
	if (*(ptAnime + cnt) == 0xff) {
		cnt = 0;
	}
	if (*(ptAnime + cnt) == 0xfe) {
		StatusStyle = EnemyRunAnime;
		cnt = 0;
	}
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
	case TrackMod:
		Track();
		break;
	case ReturnMod:
		Return();
		break;
	default:
		break;
	}
}

void	EnemyClass::HitOn() {
		HitCnt = 0;
		cnt = 0;
		StatusStyle = EnemyHitAnime;
		ActionMod = HitMod;
		InvincibleTime = 30;

}

void EnemyClass::Hit() {
	extern PlayerClass Player;
	HitCnt += 1;
	if (Player.X <= DisplayX) {
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
		Hp -= 1;
		StatusStyle = EnemyRunAnime;
		ActionMod = PatrolMod;
	}
	
}

void EnemyClass::Track() {
	extern PlayerClass Player;
	if (StatusStyle != EnemyAttAnime) {
		if (Player.X >= DisplayX) {
			if (FacedLeft) { FacedLeft = false; }
			if (!PlayerHit()) { X += SWORDENEMYSPEED; }
		}
		else {
			if (!FacedLeft) { FacedLeft = true; }
			if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
		}
		if (DisplayX - Player.X > 600 || DisplayX - Player.X < -600) {
			ActionMod = ReturnMod;
		}
		if ((DisplayX - Player.X > 0 && DisplayX - Player.X < 64) || (DisplayX - Player.X<0 && DisplayX - Player.X >-64)) {
			StatusStyle = EnemyAttAnime;
			cnt = 0;
		}
	}
}

void EnemyClass::Patrol() {
	extern PlayerClass Player;

	if (FacedLeft) {
		if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
		if (X < InitialX - 150 || X <= 0) {
			if (!PlayerHit()) { X += SWORDENEMYSPEED * 2; }
			FacedLeft = !FacedLeft;
		}
	}
	else {
		if (!PlayerHit()) { X += SWORDENEMYSPEED; }
		if (X > InitialX + 150 || X >= Background.width) {
			if (!PlayerHit()) { X -= SWORDENEMYSPEED * 2; }
			FacedLeft = !FacedLeft;
		}
	}

	if ((DisplayX - Player.X>0 &&DisplayX - Player.X < 300) || (DisplayX - Player.X<0 &&DisplayX - Player.X >-300)) {
		ActionMod = TrackMod;
	}


}

void EnemyClass::Return() {
	extern PlayerClass Player;
	if (InitialX >= X) {
		if (FacedLeft) { FacedLeft = false; }
		if (!PlayerHit()) { X += SWORDENEMYSPEED; }
	}
	else {
		if (!FacedLeft) { FacedLeft = true; }
		if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
	}

	if ((X - InitialX>0 && DisplayX - X < 30) || (X - InitialX<0 && X - InitialX >-30)) {
		ActionMod = PatrolMod;
	}
	if ((DisplayX - Player.X>0 && DisplayX - Player.X < 300) || (DisplayX - Player.X<0 && DisplayX - Player.X >-300)) {
		ActionMod = TrackMod;
	}
}

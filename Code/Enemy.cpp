//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		ìGAIä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include <stdlib.h> 
#include <time.h>  
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
#include "Quantitative.h"

//==========================================================================================================
//		íËã`
//==========================================================================================================
extern DisplayClass Display;
extern ImaginaryBackground Background;
EnemyClass *Enemy;
EnemyClass SwordEnemy[10];
byte SwordEnemyNum;

//==========================================================================================================
//		ëSëÃìGçsà◊èàóùíËã`
//==========================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	ëSëÃìGèâä˙âªä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	EnemyClass::AllInit() {
	//	åïìGÇÃèâä˙âª
	extern int GameLoop;
	bool bret;
	/*
	bool bret = DXLoadTexture(ENEMYTEX, &SwordEnemy[0].Tex);
	bret = DXLoadTexture(ENEMYPTTEX, &SwordEnemy[0].ptTex);
	//bret = DXLoadTexture(LIGHTBALLTEX, &SwordEnemy[0].ballTex);
	*/
	SwordEnemyNum = 5;
	if (GameLoop == 0) {
		bret = DXLoadTexture(ENEMYTEX, &SwordEnemy[0].Tex);
		SwordEnemy[0].Init();
		SwordEnemy[0].MaxHp = 5;
		SwordEnemy[0].InitialX = 1200;
		SwordEnemy[0].X = SwordEnemy[0].InitialX;
	}
	else
	{
		SwordEnemy[GameLoop].Init();
	}
	

	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	ëSëÃìGçXêVä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::AllUpdate() {
	//	åïìGÇÃçXêV
	for (int i = 0; i < SwordEnemyNum; i++) {
		SwordEnemy[i].Update();
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	ëSëÃìGHPîªíËä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool	EnemyClass::AllHaveHp() {
	for (int i = 0; i < SwordEnemyNum; i++) {
		if (SwordEnemy[i].broned != 0 && SwordEnemy[i].deaded != 2) { return true; }
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	ëSëÃìGï`âÊä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	EnemyClass::AllDraw() {
	//	åïìGÇÃï`âÊ
	for (int i = 0; i < SwordEnemyNum; i++) {
		SwordEnemy[i].Draw();
	}
}


//==========================================================================================================
//		å¬ëÃìGçsà◊èàóùíËã`ÅiåïìGÅj
//==========================================================================================================
void EnemyClass::Init() {
	bool bret = DXLoadTexture(LIGHTBALLTEX, &ball->Tex);
	bret = DXLoadTexture(ENEMYPTTEX, &ptTex);
	int x;
	//x
	srand((unsigned)time(NULL));
	x = (int)(rand() % 3);
	InitialX = (float)(rand() % Background.width);
	InitialY = (float)(Background.height - InitialPlayerHeight - Height / 2 - BleedSize);
	X = InitialX;
	Y = InitialY;
	DisplayX = X;
	DisplayY = Y;
	if (x == 1) {
		bret = DXLoadTexture(ENEMYSPTEX, &Tex);
		MaxHp = 10;
	}else{
		bret = DXLoadTexture(ENEMYTEX, &Tex);
		MaxHp = 5;
	}
	
	broned = 1;
	deaded = 0;
	losed = 0;
	//SwordEnemy[0].Hp = SwordEnemy[0].MaxHp;
	StatusStyle = EnemyRunAnime;
	ActionMod = PatrolMod;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGçXêVä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	EnemyClass::Update() {
	//**********************************************************************
	//	ï`âÊç¿ïWÇÃçXêV
	//**********************************************************************
	DisplayX = X - Display.MoveDistance.x;
	DisplayY = Y - Display.MoveDistance.y;
	if (broned==2 && deaded == 0) {
		

		if (InvincibleTime != 0) { InvincibleTime -= 1; }  //	ñ≥ìGéûä‘ÇÃèàóù
		switch (ActionMod)
		{
		case PatrolMod:
			Patrol();
			break;  //	èÑâÒ
		case HitMod:
			Hit();
			break;  //	damageéÛÇØÇÈ
		case TrackMod:
			Track();
			break;  //	ìGíTÇ∑
		case ReturnMod:
			Return();
			break;  //ñﬂÇÈ
		case EvilMod:
			Evil();
			break;
		default:
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGçXêVä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Draw() {
	if (broned == 2 && deaded == 0) {
		Animetion();
		if (FacedLeft) {
			DXDrawAnimePolygon(DisplayX, DisplayY, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
		}
		else {
			DXDrawPlayerRevPolygon(DisplayX, DisplayY, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
		}
	}

	//Ball
	if (broned == 1 || deaded == 1) {
		Animetion();
		ball->Draw(DisplayX, DisplayY);
	}
	if (losed == 1) {
		Animetion();
		ball->Draw2(DisplayX, DisplayY);
	}
	
	//HP
	if (broned != 0 && deaded != 2) {
		if (DisplayX>Display.width)
		{
			DXDrawAnimePolygon(Display.width - EnemyPtSize, DisplayY, 0, EnemyPtSize, EnemyPtSize, 0.5, 0.5, 0, 1, D3DCOLOR_RGBA(255, 255, 255, 255), ptTex);
		}
		else if (DisplayX<0)
		{
			DXDrawAnimePolygon(EnemyPtSize, DisplayY, 0, EnemyPtSize, EnemyPtSize, 0, 0.5, 0, 1, D3DCOLOR_RGBA(255, 255, 255, 255), ptTex);
		}
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGAnimetionä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Animetion() {
	if (broned == 2 && deaded == 0) {
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
	

	if (broned == 1) {
		if (ball->runBronAnime()) {
			broned = 2;
			Hp = MaxHp;
		}	
	}
	if (losed == 1) {
		if (ball->runLoseAnime()) {
			losed = 2;
		//	deaded=1;
		}
	}

	if (deaded == 1) {
		if (ball->runDeadAnime()) {
			deaded = 2;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGdamageéÛÇØÇÈäJénä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	EnemyClass::HitOn() {

		HitCnt = 0;
		cnt = 0;
		StatusStyle = EnemyHitAnime;
		ActionMod = HitMod;
		
		InvincibleTime = 30;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGdamageéÛÇØÇÈäJénä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	EnemyClass::EvilOn() {
	extern PlayerClass *Player;
	HitCnt = 0;
	cnt = 0;
	StatusStyle = EnemyHitAnime;
	ActionMod = EvilMod;
	InvincibleTime = 30;
	if (Player->FacedRight) {
		X = Player->X + 49 - 16;
	}else{
		X = Player->X - 49 + 16;
	}
	losed = 1;
	Y = Player->Y -16;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGdamageéÛÇØÇÈèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Hit() {
	extern PlayerClass *Player;
	HitCnt += 1;
	if (Player->X <= X) {
		X += 4;
	}else{
		X -= 4;
	}
	Y -= 10 -0.98f*HitCnt;
	if (Y > InitialY) {
		Y = InitialY;
		HitCnt = 0;
		cnt = 0;
		Hp -= 1;
		if (Hp <= 0) {
			Hp = 0;
			deaded = 1;
		}
		StatusStyle = EnemyRunAnime;
		ActionMod = PatrolMod;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGEvilHitéÛÇØÇÈèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Evil() {
	extern PlayerClass *Player;
	HitCnt += 1;
	if (HitCnt > 15) {
		HitCnt = 0;
		Hp = 0;
		deaded = 1;
		ActionMod = PatrolMod;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGìGíTÇ∑ä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Track() {
	extern PlayerClass *Player;
	if (StatusStyle != EnemyAttAnime) {
		if (Player->X >= X) {
			if (FacedLeft) { 
				FacedLeft = false; 
				X += 32;
			}
			if (!PlayerHit()) { X += SWORDENEMYSPEED; }
		}
		else {
			if (!FacedLeft) { 
				FacedLeft = true; 
				X -= 32;
			}
			if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
		}
		if (X - Player->X > 600 || X - Player->X < -600) {
			ActionMod = ReturnMod;
		}  //	Player Ç™ó£ÇπÇŒñﬂÇÈ
		/*
		if (Y - Player->Y > 100 || Y - Player->Y < -100) {
			ActionMod = ReturnMod;
		}*/
		if ((X - Player->X > 0 && X - Player->X < 64) || (X - Player->X<0 && X - Player->X >-64)) {
			StatusStyle = EnemyAttAnime;
			cnt = 0;
		}  
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGèÑâÒä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Patrol() {
	extern PlayerClass *Player;

	if (FacedLeft) {
		if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
		if (X < InitialX - 150 || X <= 0) {
			if (!PlayerHit()) { X += SWORDENEMYSPEED * 2; }
			FacedLeft = !FacedLeft;
			X += 32;
		}
	}
	else {
		if (!PlayerHit()) { X += SWORDENEMYSPEED; }
		if (X > InitialX + 150 || X >= Background.width) {
			if (!PlayerHit()) { X -= SWORDENEMYSPEED * 2; }
			FacedLeft = !FacedLeft;
			X -= 32;
		}
	}

	if ((X - Player->X>0 &&X - Player->X < 300) || (X - Player->X<0 &&X - Player->X >-300)) {
		ActionMod = TrackMod;
	}//	Player Ç™ê⁄ãﬂÇ∑ÇÈÇ∆ÅuìGíTÇ∑ÅvÇèàóù


}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	åïìGñﬂÇÈä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EnemyClass::Return() {
	extern PlayerClass *Player;
	if (InitialX >= X) {
		if (FacedLeft) { FacedLeft = false; }
		if (!PlayerHit()) { X += SWORDENEMYSPEED; }
	}
	else {
		if (!FacedLeft) { FacedLeft = true; }
		if (!PlayerHit()) { X -= SWORDENEMYSPEED; }
	}

	if ((X - InitialX>0 && X - X < 30) || (X - InitialX<0 && X - InitialX >-30)) {
		ActionMod = PatrolMod;
	}
	if ((X - Player->X>0 && X - Player->X < 300) || (X - Player->X<0 && X - Player->X >-300)) {
		ActionMod = TrackMod;
	}
}


void EnemyClass::Ball::Draw(float x, float y) {
	DXDrawAnimePolygon(x, y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
}

void EnemyClass::Ball::Draw2(float x, float y) {
	extern PlayerClass *Player;
	float X;
	if (Player->FacedRight) {
		X = x - cnt2;
	}else {
		X = x + cnt2;
	}
	DXDrawAnimePolygon(X, y, 0, Width, Height, Ustart2, Uwidth, Vstart2, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
}

void EnemyClass::deleteAll() {
	for (int i = 0; i < SwordEnemyNum; i++) {
		SwordEnemy[i].Hp = 0;
		SwordEnemy[i].broned = 0;
		SwordEnemy[i].deaded = 0;
		SwordEnemy[i].losed = 0;
		SwordEnemy[i].StatusStyle = EnemyRunAnime;
		SwordEnemy[i].ActionMod = PatrolMod;
	}
}
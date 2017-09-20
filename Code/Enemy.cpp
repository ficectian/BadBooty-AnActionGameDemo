//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		ìGAIä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
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
	bool bret = DXLoadTexture(ENEMYTEX, &SwordEnemy[0].Tex);
	bret = DXLoadTexture(ENEMYPTTEX, &SwordEnemy[0].ptTex);
	bret = DXLoadTexture(LIGHTBALLTEX, &SwordEnemy[0].ballTex);

	SwordEnemyNum = 3;
	switch (GameLoop)
	{
	case 0:
		SwordEnemy[0].InitialX = 1200;
		SwordEnemy[0].InitialY = (float)(Background.height - InitialPlayerHeight - SwordEnemy[0].Height / 2 - BleedSize);
		SwordEnemy[0].X = SwordEnemy[0].InitialX;
		SwordEnemy[0].Y = SwordEnemy[0].InitialY;
		SwordEnemy[0].DisplayX = SwordEnemy[0].X;
		SwordEnemy[0].DisplayY = SwordEnemy[0].Y;
		SwordEnemy[0].MaxHp = 3;
		SwordEnemy[0].broned = 1;
		SwordEnemy[0].deaded = 0;
		//SwordEnemy[0].Hp = SwordEnemy[0].MaxHp;
		SwordEnemy[0].StatusStyle = EnemyRunAnime;
		SwordEnemy[0].ActionMod = PatrolMod;
		break;
	case 1:
		SwordEnemy[1].Tex = SwordEnemy[0].Tex;
		SwordEnemy[1].ptTex = SwordEnemy[0].ptTex;
		SwordEnemy[1].ballTex = SwordEnemy[0].ballTex;
		SwordEnemy[1].InitialX = 500;
		SwordEnemy[1].InitialY = (float)(Background.height - InitialPlayerHeight - SwordEnemy[0].Height / 2 - BleedSize);
		SwordEnemy[1].X = SwordEnemy[1].InitialX;
		SwordEnemy[1].Y = SwordEnemy[1].InitialY;
		SwordEnemy[1].DisplayX = SwordEnemy[1].X;
		SwordEnemy[1].DisplayY = SwordEnemy[1].Y;
		SwordEnemy[1].broned = 1;
		SwordEnemy[1].deaded = 0;
		//SwordEnemy[1].Hp = SwordEnemy[1].MaxHp;
		SwordEnemy[1].ActionMod = PatrolMod;
		SwordEnemy[1].StatusStyle = EnemyRunAnime;
		break;
	case 3:
		bret = DXLoadTexture(ENEMYSPTEX, &SwordEnemy[2].Tex);
		SwordEnemy[2].ptTex = SwordEnemy[0].ptTex;
		SwordEnemy[2].ballTex = SwordEnemy[0].ballTex;
		SwordEnemy[2].InitialX = 1000;
		SwordEnemy[2].InitialY = (float)(Background.height - InitialPlayerHeight - SwordEnemy[0].Height / 2 - BleedSize);
		SwordEnemy[2].X = SwordEnemy[2].InitialX;
		SwordEnemy[2].Y = SwordEnemy[2].InitialY;
		SwordEnemy[2].DisplayX = SwordEnemy[2].X;
		SwordEnemy[2].DisplayY = SwordEnemy[2].Y;
		SwordEnemy[2].MaxHp = 10;
		SwordEnemy[2].broned = 1;
		SwordEnemy[2].deaded = 0;
		//SwordEnemy[2].Hp = SwordEnemy[2].MaxHp;
		SwordEnemy[2].ActionMod = PatrolMod;
		SwordEnemy[2].StatusStyle = EnemyRunAnime;
		
	default:
		break;
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
	if (broned == 1) {
		Animetion();
		DXDrawAnimePolygon(DisplayX, DisplayY, 0, 64, 64, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), ballTex);
	}
	if (deaded == 1) {
		Animetion();
		DXDrawAnimePolygon(DisplayX, DisplayY, 0, 64, 64, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), ballTex);
	}
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
		const byte *ptBallAnime = ballAnime_data[0];
		cnt += 1;
		if (*(ptBallAnime + cnt) == 0xff) {
			cnt = 0;
			broned = 2;
			Hp = MaxHp;
		}
		Ustart = ((*(ptBallAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
		Vstart = ((*(ptBallAnime + cnt)) / (int)(1 / Vheight))*Vheight;
		
	}

	if (deaded == 1) {
		const byte *ptBallAnime = ballAnime_data[1];
		cnt += 1;
		if (*(ptBallAnime + cnt) == 0xff) {
			cnt = 0;
			deaded = 2;
		}
		Ustart = ((*(ptBallAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
		Vstart = ((*(ptBallAnime + cnt)) / (int)(1 / Vheight))*Vheight;

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

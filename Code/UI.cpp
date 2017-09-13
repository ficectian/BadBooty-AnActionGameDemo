//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		UIˆ—ŠÖ”
//		—j•X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "UI.h"
#include "Quantitative.h"


void UIClass::Init(){

	
}

void UIClass::Draw() {
	DXDrawPolygon(X, Y, 0, Width, Height, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
}
void UIClass::Draw(float x, float y) {
	DXDrawPolygon(x, y, 0, Width, Height, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
}
void UIClass::Draw(float x, float y, float uStart, float uWidth, float vStart, float vHeight) {
	DXDrawAnimePolygon(x,y , 0, Width, Height, uStart, uWidth, vStart,vHeight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);
}



void UIDrawClass::Init() {
	EnemyHP = new UIClass;
	EnemyHPBackground = new UIClass;
	bool
		bret = DXLoadTexture(HeadBackgroundTex, &PlayerHeadBackground->Tex);
	bret = DXLoadTexture(HeadTex, &PlayerHead->Tex);
	bret = DXLoadTexture(PlayerHPTEX, &PlayerHP->Tex);
	bret = DXLoadTexture(ENEMYHPBGTEX, &EnemyHPBackground->Tex);
	bret = DXLoadTexture(ENEMYHPTEX, &EnemyHP->Tex);

	PlayerHeadBackground->Width = 270;
	PlayerHeadBackground->Height = 77;
	PlayerHeadBackground->X = 10 + PlayerHeadBackground->Width / 2;
	PlayerHeadBackground->Y = 10 + PlayerHeadBackground->Height / 2;

	PlayerHead->Width = 68;
	PlayerHead->Height = 68;
	PlayerHead->X = 10 + 5 + PlayerHead->Width / 2;
	PlayerHead->Y = 10 + 5 + PlayerHead->Height / 2;
	EnemyHPBackground->Width = 82;
	EnemyHPBackground->Height = 6;
	EnemyHP->Width = 80 / 10;
	EnemyHP->Height = 4;
	PlayerHP->Width = 10;
	PlayerHP->Height = 22;
	PlayerHP->X = 10 + 68 + PlayerHP->Width / 2;
	PlayerHP->Y = 10 + 44 + PlayerHP->Height / 2;
	PlayerHP->Uwidth = (float)1 / 2;
}

void UIDrawClass::Draw(int HP) {
	extern EnemyClass SwordEnemy[10];
	extern byte SwordEnemyNum;
	byte EnemyHPUI;
	for (int i = 0; i < SwordEnemyNum; i++) {
		if (SwordEnemy[i].Hp > 0) {
			EnemyHPUI = SwordEnemy[i].Hp * 10 / SwordEnemy[i].MaxHp;
			EnemyHPBackground->Draw(SwordEnemy[i].DisplayX, SwordEnemy[i].DisplayY - 70);
			for (int n = 0; n < EnemyHPUI; n++) {
				EnemyHP->Draw((SwordEnemy[i].DisplayX - 40 + EnemyHP[0].Width / 2) + n*EnemyHP[0].Width, SwordEnemy[i].DisplayY - 70);
			}
		}
		
	}
	if (HP >=20) {
		for (int i = 0; i < 20; i++) {
			PlayerHP->Draw(PlayerHP->X + i*PlayerHP->Width, PlayerHP->Y, PlayerHP->Ustart, PlayerHP->Uwidth, PlayerHP->Vstart, PlayerHP->Vheight);
		}
		for (int i = 0; i < HP - 20; i++) {
			PlayerHP->Draw(PlayerHP->X + i*PlayerHP->Width, PlayerHP->Y, PlayerHP->Ustart + PlayerHP->Uwidth, PlayerHP->Uwidth, PlayerHP->Vstart, PlayerHP->Vheight);		}
	}
	else
	{
		for (int i = 0; i < HP; i++) {
			PlayerHP->Draw(PlayerHP->X + i*PlayerHP->Width, PlayerHP->Y, PlayerHP->Ustart, PlayerHP->Uwidth, PlayerHP->Vstart, PlayerHP->Vheight);
		}
	}
	PlayerHeadBackground->Draw();
	PlayerHead->Draw();
}
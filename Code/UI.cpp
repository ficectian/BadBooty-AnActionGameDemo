//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		UIèàóùä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"
#include "Quantitative.h"
UIClass *GameUI;
UIClass	PlayerHeadBackground;
UIClass	PlayerHead;
UIClass	PlayerHP;
UIClass	EnemyHP;
UIClass	EnemyHPBackground;
void UIClass::Init(){
	bool
		bret = DXLoadTexture(HeadBackgroundTex, &PlayerHeadBackground.Tex);
	bret = DXLoadTexture(HeadTex, &PlayerHead.Tex);
	bret = DXLoadTexture(PlayerHPTEX, &PlayerHP.Tex);
	bret = DXLoadTexture(ENEMYHPBGTEX, &EnemyHPBackground.Tex);
	bret = DXLoadTexture(ENEMYHPTEX, &EnemyHP.Tex);

	PlayerHeadBackground.Width = 270;
	PlayerHeadBackground.Height = 77;
	PlayerHeadBackground.X = 10 + PlayerHeadBackground.Width / 2;
	PlayerHeadBackground.Y = 10 + PlayerHeadBackground.Height / 2;

	PlayerHead.Width = 68;
	PlayerHead.Height = 68;
	PlayerHead.X = 10+5 + PlayerHead.Width/2;
	PlayerHead.Y = 10+5 + PlayerHead.Height / 2;
	EnemyHPBackground.Width = 82;
	EnemyHPBackground.Height = 6;
	EnemyHP.Width = 80/10;
	EnemyHP.Height = 4;
	PlayerHP.Width = 10;
	PlayerHP.Height = 22;
	PlayerHP.X = 10 + 68 + PlayerHP.Width/ 2;
	PlayerHP.Y = 10+44+ PlayerHP.Height/2;
	PlayerHP.Uwidth = (float)1 / 2;
}

void UIClass::Draw(int HP) {
	extern EnemyClass SwordEnemy[10];
	extern byte SwordEnemyNum;
	byte EnemyHPUI;
	for (int i = 0; i < SwordEnemyNum; i++) {
		if (SwordEnemy[i].Hp > 0) {
			EnemyHPUI = SwordEnemy[i].Hp * 10 / 5;
			DXDrawAnimePolygon(SwordEnemy[i].DisplayX, SwordEnemy[i].DisplayY - 70, 0, EnemyHPBackground.Width, EnemyHPBackground.Height, EnemyHPBackground.Ustart, EnemyHPBackground.Uwidth, EnemyHPBackground.Vstart, EnemyHPBackground.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), EnemyHPBackground.Tex);
			for (int n = 0; n < EnemyHPUI; n++) {
				DXDrawAnimePolygon((SwordEnemy[i].DisplayX - 40 + EnemyHP.Width / 2) + n*EnemyHP.Width, SwordEnemy[i].DisplayY - 70, 0, EnemyHP.Width, EnemyHP.Height, EnemyHP.Ustart, EnemyHP.Uwidth, EnemyHP.Vstart, EnemyHP.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), EnemyHP.Tex);
			}
		}
		
	}
	if (HP >=20) {
		for (int i = 0; i < 20; i++) {
			DXDrawAnimePolygon(PlayerHP.X + i*PlayerHP.Width, PlayerHP.Y, 0, PlayerHP.Width, PlayerHP.Height, PlayerHP.Ustart, PlayerHP.Uwidth, PlayerHP.Vstart, PlayerHP.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), PlayerHP.Tex);
		}
		for (int i = 0; i < HP - 20; i++) {
			DXDrawAnimePolygon(PlayerHP.X + i*PlayerHP.Width, PlayerHP.Y, 0, PlayerHP.Width, PlayerHP.Height, PlayerHP.Ustart + PlayerHP.Uwidth, PlayerHP.Uwidth, PlayerHP.Vstart, PlayerHP.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), PlayerHP.Tex);
		}
	}
	else
	{
		for (int i = 0; i < HP; i++) {
			DXDrawAnimePolygon(PlayerHP.X + i*PlayerHP.Width, PlayerHP.Y, 0, PlayerHP.Width, PlayerHP.Height, PlayerHP.Ustart, PlayerHP.Uwidth, PlayerHP.Vstart, PlayerHP.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), PlayerHP.Tex);
		}
	}
	
	DXDrawPolygon(PlayerHeadBackground.X, PlayerHeadBackground.Y, 0, PlayerHeadBackground.Width, PlayerHeadBackground.Height, D3DCOLOR_RGBA(255, 255, 255, 255), PlayerHeadBackground.Tex);
	DXDrawPolygon(PlayerHead.X, PlayerHead.Y, 0, PlayerHead.Width, PlayerHead.Height, D3DCOLOR_RGBA(255, 255, 255, 255), PlayerHead.Tex);
	

}
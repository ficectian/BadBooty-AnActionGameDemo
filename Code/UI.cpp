//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		UIˆ—ŠÖ”
//		—j•X
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

void UIClass::Init(){
	bool
		bret = DXLoadTexture(HeadBackgroundTex, &PlayerHeadBackground.Tex);
	bret = DXLoadTexture(HeadTex, &PlayerHead.Tex);
	bret = DXLoadTexture(PlayerHPTEX, &PlayerHP.Tex);
	PlayerHeadBackground.Width = 270;
	PlayerHeadBackground.Height = 77;
	PlayerHeadBackground.X = 10 + PlayerHeadBackground.Width / 2;
	PlayerHeadBackground.Y = 10 + PlayerHeadBackground.Height / 2;

	PlayerHead.Width = 68;
	PlayerHead.Height = 68;
	PlayerHead.X = 10+5 + PlayerHead.Width/2;
	PlayerHead.Y = 10+5 + PlayerHead.Height / 2;

	PlayerHP.Width = 10;
	PlayerHP.Height = 22;
	PlayerHP.X = 10 + 68 + PlayerHP.Width/ 2;
	PlayerHP.Y = 10+44+ PlayerHP.Height/2;
	PlayerHP.Uwidth = (float)1 / 2;
}

void UIClass::Draw(int HP) {
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		ŠK’iˆ—ŠÖ”
//		—j•X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"
#include "Quantitative.h"
StairClass *Stair;
StairClass StairL[128];
byte StairNum;
extern DisplayClass Display;
extern ImaginaryBackground Background;

void StairClass::Init() {
	bool
		bret = DXLoadTexture(STAIRTEX, &StairL[0].Tex);
	
	
	StairNum = (int)((Background.height - 760 - StairL[0].Height/2) - InitialPlayerHeight)/ StairL[0].Height;
	for (int i = 0; i < StairNum; i++) {
		StairL[i].X = 1400;
		StairL[i].Y = (float)((Background.height - 760 - StairL[0].Height / 2) + i*StairL[i].Height);
		StairL[i].DisplayX = StairL[i].X;
		StairL[i].DisplayY = StairL[i].Y;
	}

}

void StairClass::Update() {
	for (int i = 0; i < StairNum; i++) {
		StairL[i].Sync(Display);
	}
}

void StairClass::Draw() {
	for (int i = 0; i < StairNum; i++) {
		DXDrawPolygon(StairL[i].DisplayX, StairL[i].DisplayY, 0, StairL[i].Width, StairL[i].Height, D3DCOLOR_RGBA(255, 255, 255, 255), StairL[0].Tex);

	}

}
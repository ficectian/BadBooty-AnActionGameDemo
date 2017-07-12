#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"

StairClass *Stair;
StairClass StairL[128];
byte StairNum;
extern DisplayClass Display;
extern ImaginaryBackground Background;

void StairClass::Init() {
	bool
		bret = DXLoadTexture(STAIRTEX, &StairL[0].Tex);
	StairNum = 1;
	StairL[0].Height = 50*4;
	StairL[0].Width = 100*4;
	StairL[0].X = Background.width - StairL[0].Width / 2;
	StairL[0].Y = (float)(Display.height - 50  -StairL[0].Height/2);

	StairL[0].DisplayX = StairL[0].X;
	StairL[0].DisplayY = StairL[0].Y;
}

void StairClass::Update() {
	Display.Update(Background);
	StairL[0].Sync(Display);
}

void StairClass::Draw() {
	DXDrawPolygon(StairL[0].DisplayX, StairL[0].DisplayY, 0, StairL[0].Width, StairL[0].Height, D3DCOLOR_RGBA(255, 255, 255, 255), StairL[0].Tex);

}
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"

ImageClass *Image;
ImageClass Scren;
//ImageClass Land;
ImageClass Pt1;
ImageClass LandPixel[LANDPIXELMAX];
byte LandNum;
ImaginaryBackground Background;
DisplayClass Display;

void ImageClass::Init() {
	bool 
	bret = DXLoadTexture(SCRENTEX, &Scren.Tex);
	//bret = DXLoadTexture(LANDTEX, &Land.Tex);
	bret = DXLoadTexture(LANDPIXELTEX, &LandPixel[0].Tex);
	LandPixel[0].Width = 50;
	LandNum = Background.width / LandPixel[0].Width + 1;
	LandNum = 41;
	for (int i = 0; i < LandNum; i++) {
		LandPixel[i].Height = 50;
		LandPixel[i].Width = 50;
		LandPixel[i].Ustart = 0.0f;
		LandPixel[i].Uwidth = 1.0f;
		LandPixel[i].Vstart = 0.0f;
		LandPixel[i].Vheight = 1.0f;
		LandPixel[i].Y = SCREEN_HEIGHT - 25;
		LandPixel[i].DisplayY = LandPixel[i].Y;
		LandPixel[i].X = LandPixel[i].Width / 2 + i*LandPixel[i].Width;
		LandPixel[i].DisplayX = LandPixel[i].X;
	}

	//Land.Width = 1024;
	//Land.Height = 512;
	//Land.X = Land.Width / 2;
	//Land.Y = SCREEN_HEIGHT - Land.Height / 2;
	//Land.Ustart = 0.0f;
	//Land.Uwidth = 1.0f;
	//Land.Vstart = 0.0f;
	//Land.Vheight = 1.0f;
	Scren.Width = SCREEN_WIDTH;
	Scren.Height = SCREEN_HEIGHT;
	Scren.X = Scren.Width / 2;
	Scren.Y = Scren.Height / 2;

}

void ImageClass::Update(){
	
	Display.Update(Background);
	//Land.Ustart += 0.0003f;
	for (int i = 0; i < LandNum; i++) {
		LandPixel[i].Sync(Display);
	}
}
void ImageClass::TitleDraw(int fcnt) {
	
}
void ImageClass::BackDraw() {
	DXDrawPolygon(Scren.X, Scren.Y, 0, Scren.Width, Scren.Height, D3DCOLOR_RGBA(255, 255, 255, 255), Scren.Tex);
	//DXDrawAnimePolygon(Land.X, Land.Y, 0, Land.Width, Land.Height, Land.Ustart, Land.Uwidth, Land.Vstart, Land.Vheight,D3DCOLOR_RGBA(255, 255, 255, 255), Land.Tex);
	for (int i = 0; i < LandNum; i++) {
		DXDrawAnimePolygon(LandPixel[i].DisplayX, LandPixel[i].DisplayY, 0, LandPixel[i].Width, LandPixel[i].Height, LandPixel[i].Ustart, LandPixel[i].Uwidth, LandPixel[i].Vstart, LandPixel[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), LandPixel[0].Tex);

	}
}

void ImageClass::UpDraw(int HP) {

}





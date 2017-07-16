//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		îwåièàóùä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"
#include "Quantitative.h"

ImageClass *Image;
ImageClass Scren;
//ImageClass Land;
ImageClass Grass[128];
ImageClass LandPixel[LANDPIXELMAX];
ImageClass Footing[256];
byte LandNum;
byte FootingNum;
byte GrassNum;
ImaginaryBackground Background;
DisplayClass Display;

void ImageClass::Init() {
	bool 
	bret = DXLoadTexture(SCRENTEX, &Scren.Tex);
	//bret = DXLoadTexture(LANDTEX, &Land.Tex);
	bret = DXLoadTexture(LANDPIXELTEX, &LandPixel[0].Tex);
	bret = DXLoadTexture(GRASSTEX, &Grass[0].Tex);
	bret = DXLoadTexture(LANDTEX, &Footing[0].Tex);


	LandPixel[0].Width = 60;
	
	LandNum = Background.width / LandPixel[0].Width + 1;

	for (int i = 0; i < LandNum; i++) {
		LandPixel[i].Height = 160;
		LandPixel[i].Width = 60;
		LandPixel[i].Ustart = 0.0f;
		LandPixel[i].Uwidth = 1.0f;
		LandPixel[i].Vstart = 0.0f;
		LandPixel[i].Vheight = 1.0f;
		LandPixel[i].Y = SCREEN_HEIGHT - LandPixel[i].Height/2;
		LandPixel[i].DisplayY = LandPixel[i].Y;
		LandPixel[i].X = LandPixel[i].Width / 2 + i*LandPixel[i].Width;
		LandPixel[i].DisplayX = LandPixel[i].X;
	}
	Grass[0].Width = 60;
	GrassNum = Background.width / Grass[0].Width + 1;
	for (int i = 0; i < GrassNum; i++) {
		Grass[i].Height = 120;
		Grass[i].Width = 60;
		Grass[i].Ustart = 0.0f;
		Grass[i].Uwidth = 1.0f;
		Grass[i].Vstart = 0.0f;
		Grass[i].Vheight = 1.0f;
		Grass[i].Y = SCREEN_HEIGHT - Grass[i].Height / 2;
		Grass[i].DisplayY = Grass[i].Y;
		Grass[i].X = Grass[i].Width / 2 + i*Grass[i].Width;
		Grass[i].DisplayX = Grass[i].X;
	}
	Scren.Width = SCREEN_WIDTH;
	Scren.Height = SCREEN_HEIGHT;
	Scren.X = Scren.Width / 2;
	Scren.Y = Scren.Height / 2;
	FootingNum = 2;
	Footing[0].X = 1024;
	Footing[0].Y = SCREEN_HEIGHT - 220;
	Footing[1].X = 1224;
	Footing[1].Y = SCREEN_HEIGHT - 270;
	for (int i = 0; i < FootingNum; i++) {
		Footing[i].Height = 20;
		Footing[i].Width = 100;
		Footing[i].Ustart = 0.0f;
		Footing[i].Uwidth = 1.0f;
		Footing[i].Vstart = 0.0f;
		Footing[i].Vheight = 1.0f;
		Footing[i].DisplayY = Footing[i].Y;
		Footing[i].DisplayX = Footing[i].X;
	}

}

void ImageClass::Update(){
	
	Display.Update(Background);
	//Land.Ustart += 0.0003f;
	for (int i = 0; i < LandNum; i++) {
		LandPixel[i].Sync(Display);
	}
	for (int i = 0; i < FootingNum; i++) {
		Footing[i].Sync(Display);
	}
	for (int i = 0; i < GrassNum; i++) {
		Grass[i].Sync(Display);
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

	for (int i = 0; i < FootingNum; i++) {
		DXDrawAnimePolygon(Footing[i].DisplayX, Footing[i].DisplayY, 0, Footing[i].Width, Footing[i].Height, Footing[i].Ustart, Footing[i].Uwidth, Footing[i].Vstart, Footing[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Footing[0].Tex);

	}
}

void ImageClass::UpDraw(int HP) {
	for (int i = 0; i < GrassNum; i++) {
		DXDrawAnimePolygon(Grass[i].DisplayX, Grass[i].DisplayY, 0, Grass[i].Width, Grass[i].Height, Grass[i].Ustart, Grass[i].Uwidth, Grass[i].Vstart, Grass[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Grass[0].Tex);

	}
}





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
ImageClass TitleBackground;
ImageClass TitleLogo;
ImageClass TitleInit;
ImageClass Scren;
ImageClass Grass[128];
ImageClass LandPixel[LANDPIXELMAX];
ImageClass Footing[256];
ImageClass XYZ;
byte LandNum;
byte FootingNum;
byte GrassNum;
float xyz;
bool Bingging;
float LOGOBigging;
ImaginaryBackground Background;
DisplayClass Display;
extern byte Status;
void ImageClass::Init() {
	bool bret;
	switch (Status)
	{
	case TITLE:
		bret = DXLoadTexture(TITLEBGTEX, &TitleBackground.Tex);
		bret = DXLoadTexture(TITLELOGOTEX, &TitleLogo.Tex);
		bret = DXLoadTexture(TITLEINITTEX, &TitleInit.Tex);
		TitleBackground.Height = Display.height;
		TitleBackground.Width = Display.width;
		TitleBackground.Y = Display.height / 2;
		TitleBackground.DisplayY = TitleBackground.Y;
		TitleBackground.X = Display.width/2;
		TitleBackground.DisplayX = TitleBackground.X;
		TitleLogo.Width = 671;
		TitleLogo.Height = 160;
		TitleLogo.X = 59 + TitleLogo.Width / 2;
		TitleLogo.DisplayX = TitleLogo.X;
		TitleLogo.Y = 77 + TitleLogo.Height / 2;
		TitleLogo.DisplayY = TitleLogo.Y;
		TitleInit.Width = 402;
		TitleInit.Height = 59;
		TitleInit.X = Display.width - 126 - TitleInit.Width / 2;
		TitleInit.Y = Display.height - 143 - TitleInit.Height / 2;
		LOGOBigging = 1.0f;
		Bingging = true;
		break;
	case GAME_START:
		bret = DXLoadTexture(SCRENTEX, &Scren.Tex);
		//bret = DXLoadTexture(LANDTEX, &Land.Tex);
		bret = DXLoadTexture(LANDPIXELTEX, &LandPixel[0].Tex);
		bret = DXLoadTexture(GRASSTEX, &Grass[0].Tex);
		bret = DXLoadTexture(LANDTEX, &Footing[0].Tex);
		bret = DXLoadTexture(XYZTEX, &XYZ.Tex);

		xyz = 0.0f;
		XYZ.Height = XYZ.Width = 128;
		XYZ.X = 512;
		XYZ.Y = SCREEN_HEIGHT - 512;
		XYZ.DisplayX = XYZ.X;
		XYZ.DisplayY = XYZ.Y;

		LandNum = Background.width / LandPixel[0].Width + 1;

		for (int i = 0; i < LandNum; i++) {
			LandPixel[i].Height = 160;
			LandPixel[i].Width = 60;
			LandPixel[i].Y = SCREEN_HEIGHT - LandPixel[i].Height / 2;
			LandPixel[i].DisplayY = LandPixel[i].Y;
			LandPixel[i].X = LandPixel[i].Width / 2 + i*LandPixel[i].Width;
			LandPixel[i].DisplayX = LandPixel[i].X;
		}
		Grass[0].Width = 60;
		GrassNum = Background.width / Grass[0].Width + 1;
		for (int i = 0; i < GrassNum; i++) {
			Grass[i].Height = 120;
			Grass[i].Width = 60;
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
			Footing[i].DisplayY = Footing[i].Y;
			Footing[i].DisplayX = Footing[i].X;
		}
		break;
	default:
		break;
	}
	

}

void ImageClass::Update(){
	switch (Status)
	{
	case TITLE:
		TitleInit.cnt += 1;
		if (TitleInit.cnt >= 60) { TitleInit.cnt = 0; }
		if (Bingging) {
			LOGOBigging += 0.01f;
			if (LOGOBigging >= 1.2f) { Bingging = false; }
		}else{
			LOGOBigging -= 0.01f;
			if (LOGOBigging <= 0.8f) { Bingging = true; }
		}
		

		break;
	case GAME_PLAY:
		xyz += 0.1f;
		if (xyz >= 360.0f) { xyz = 0.0f; }
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
		XYZ.Sync(Display);
		break;
	default:
		break;
	}
	
}
void ImageClass::TitleDraw() {
	DXDrawPolygon(TitleBackground.X, TitleBackground.Y, 0, TitleBackground.Width, TitleBackground.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleBackground.Tex);
	DXDrawPolygon(TitleLogo.X, TitleLogo.Y, 0, TitleLogo.Width, TitleLogo.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleLogo.Tex);
	/*if (TitleInit.cnt <= 30) {
		DXDrawPolygon(TitleInit.X, TitleInit.Y, 0, TitleInit.Width, TitleInit.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit.Tex);
	}*/
	DXDrawPolygon(TitleInit.X, TitleInit.Y, 0, TitleInit.Width*LOGOBigging, TitleInit.Height*LOGOBigging, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit.Tex);

}
void ImageClass::BackDraw() {
	switch (Status)
	{
	case GAME_PLAY:
		DXDrawPolygon(Scren.X, Scren.Y, 0, Scren.Width, Scren.Height, D3DCOLOR_RGBA(255, 255, 255, 255), Scren.Tex);
		DXDrawAnglePolygon(XYZ.DisplayX, XYZ.DisplayY, 0, XYZ.Width, XYZ.Height, XYZ.Ustart, XYZ.Uwidth, XYZ.Vstart, XYZ.Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), XYZ.Tex, xyz);

		for (int i = 0; i < LandNum; i++) {
			DXDrawAnimePolygon(LandPixel[i].DisplayX, LandPixel[i].DisplayY, 0, LandPixel[i].Width, LandPixel[i].Height, LandPixel[i].Ustart, LandPixel[i].Uwidth, LandPixel[i].Vstart, LandPixel[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), LandPixel[0].Tex);

		}

		for (int i = 0; i < FootingNum; i++) {
			DXDrawAnimePolygon(Footing[i].DisplayX, Footing[i].DisplayY, 0, Footing[i].Width, Footing[i].Height, Footing[i].Ustart, Footing[i].Uwidth, Footing[i].Vstart, Footing[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Footing[0].Tex);
		}
		break;
	default:
		break;
	}

}

void ImageClass::UpDraw() {
	switch (Status)
	{
	case GAME_PLAY:
		for (int i = 0; i < GrassNum; i++) {
			DXDrawAnimePolygon(Grass[i].DisplayX, Grass[i].DisplayY, 0, Grass[i].Width, Grass[i].Height, Grass[i].Ustart, Grass[i].Uwidth, Grass[i].Vstart, Grass[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Grass[0].Tex);
		}
		break;
	default:
		break;
	}
	
}





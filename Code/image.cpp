//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		îwåièàóùä÷êî
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
//#include "input.h"
#include "Background.h"
#include "Quantitative.h"

//==========================================================================================================
//		íËã`
//==========================================================================================================

extern byte Status;	// game Modeë„ì¸
extern ImaginaryBackground Background;	// âºëzîwåiñ êœë„ì¸
extern StairClass *Stair;

float xyz;
bool Bingging;
float LOGOBigging;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	âÊñ èâä˙âªä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageSystem::NumberInit() {
	LandNum = Background.width / 120 + 1;
	GrassNum = Background.width / 120 + 1;
	FootingNum = 3;
}
void ImageSystem::Init() {
	extern DisplayClass Display;	// âºëzcameraë„ì¸
	bool bret;	// Textureë„ì¸îªífïœêî
	switch (Status)
	{
		//**********************************************************************
		//	TitleâÊñ èâä˙âª
		//**********************************************************************
	case TITLE:
		if (TitleBackground == NULL) { TitleBackground = new ImageClass; }
		if (TitleInit == NULL) { TitleInit = new ImageClass; }
		
		bret = DXLoadTexture(TITLEBGTEX, &TitleBackground->Tex);
		bret = DXLoadTexture(TITLEINITTEX, &TitleInit->Tex);
		TitleBackground->Height = Display.height;
		TitleBackground->Width = Display.width;
		TitleBackground->Y = Display.height / 2;
		TitleBackground->DisplayY = TitleBackground->Y;
		TitleBackground->X = Display.width / 2;
		TitleBackground->DisplayX = TitleBackground->X;
		TitleInit->Width = 201;
		TitleInit->Height = 30;
		TitleInit->X = Display.width - 100 - TitleInit->Width / 2;
		TitleInit->Y = Display.height - 143 - TitleInit->Height / 2;
		LOGOBigging = 1.0f;
		Bingging = true;
		break;
	case GAME_START:
		NumberInit();
		if (Scren == NULL) { Scren = new ImageClass; }
		
		if (LandPixel == NULL) { LandPixel = new ImageClass[LandNum]; }
		
		if (Grass == NULL) { Grass = new ImageClass[GrassNum]; }
		
		if (Footing == NULL) { Footing = new ImageClass[FootingNum]; }
		
		if (XYZ == NULL) { XYZ = new ImageClass; }
		

		bret = DXLoadTexture(SCRENTEX, &Scren->Tex);
		bret = DXLoadTexture(LANDPIXELTEX, &LandPixel[0].Tex);
		bret = DXLoadTexture(GRASSTEX, &Grass[0].Tex);
		bret = DXLoadTexture(LANDTEX, &Footing[0].Tex);
		bret = DXLoadTexture(XYZTEX, &XYZ->Tex);
		Stair->Init();
		xyz = 0.0f;
		XYZ->Height = XYZ->Width = 128;
		XYZ->X = 512;
		XYZ->Y = Background.height - 512 - BleedSize;
		XYZ->DisplayX = XYZ->X;
		XYZ->DisplayY = XYZ->Y;

		for (int i = 0; i < LandNum; i++) {
			LandPixel[i].Height = 200;
			LandPixel[i].Width = 120;
			LandPixel[i].Y = Background.height - LandPixel[i].Height / 2 - BleedSize;
			LandPixel[i].DisplayY = LandPixel[i].Y;
			LandPixel[i].X = LandPixel[i].Width / 2 + i*LandPixel[i].Width;
			LandPixel[i].DisplayX = LandPixel[i].X;
		}

		for (int i = 0; i < GrassNum; i++) {
			Grass[i].Height = 148;
			Grass[i].Width = 120;
			Grass[i].Y = Background.height - Grass[i].Height / 2 - BleedSize + 9;
			Grass[i].DisplayY = Grass[i].Y;
			Grass[i].X = Grass[i].Width / 2 + i*Grass[i].Width;
			Grass[i].DisplayX = Grass[i].X;
		}
		Scren->Width = SCREEN_WIDTH;
		Scren->Height = SCREEN_HEIGHT;
		Scren->X = Scren->Width / 2;
		Scren->Y = Scren->Height / 2;
		
		Footing[0].X = 1024;
		Footing[0].Y = Background.height - 270 - BleedSize;
		Footing[1].X = 1224;
		Footing[1].Y = Background.height - 320 - BleedSize;
		Footing[2].X = 1200;
		Footing[2].Y = Background.height - 760 - BleedSize;

		for (int i = 0; i < FootingNum; i++) {
			Footing[i].Height = 20;
			Footing[i].Width = 100;
			Footing[i].DisplayY = Footing[i].Y;
			Footing[i].DisplayX = Footing[i].X;
		}
		Footing[2].Width = 400;
		break;
	case GAME_WIN:
		if (thankPlay == NULL) { thankPlay = new ImageClass; }
		bret = DXLoadTexture(THANKPLAYTEX, &thankPlay->Tex);
		thankPlay->Width = 339.0f;
		thankPlay->Height = 110.0f;
		thankPlay->X = Display.width / 2;
		thankPlay->Y = Display.height / 2;
		thankPlay->DisplayX = thankPlay->X;
		thankPlay->DisplayY = thankPlay->Y;
		break;
	default:
		break;
	}
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	âÊñ çXêVèàóùä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageSystem::Update(){
	extern DisplayClass Display;	// âºëzcameraë„ì¸

	switch (Status)
	{
	case TITLE:
		TitleInit->cnt += 1;
		if (TitleInit->cnt >= 60) { TitleInit->cnt = 0; }
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
		Stair->Update();
		if (xyz >= 360.0f) { xyz = 0.0f; }
		//Display.Update(Background);
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
		XYZ->Sync(Display);
		break;

	case GAME_WIN:
		if (Bingging) {
			LOGOBigging += 0.01f;
			if (LOGOBigging >= 1.2f) { Bingging = false; }
		}
		else {
			LOGOBigging -= 0.01f;
			if (LOGOBigging <= 0.8f) { Bingging = true; }
		}
		break;
	default:
		break;
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	TitleâÊñ ï`âÊä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageSystem::TitleDraw() {
	DXDrawPolygon(TitleBackground->X, TitleBackground->Y, 0, TitleBackground->Width, TitleBackground->Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleBackground->Tex);
	DXDrawPolygon(TitleInit->X, TitleInit->Y, 0, TitleInit->Width*LOGOBigging, TitleInit->Height*LOGOBigging, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit->Tex);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	îwåiâÊñ ï`âÊä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageSystem::BackDraw() {
	switch (Status)
	{
	case GAME_PLAY:
		DXDrawPolygon(Scren->X, Scren->Y, 0, Scren->Width, Scren->Height, D3DCOLOR_RGBA(255, 255, 255, 255), Scren->Tex);
		DXDrawAnglePolygon(XYZ->DisplayX, XYZ->DisplayY, 0, XYZ->Width, XYZ->Height, XYZ->Ustart, XYZ->Uwidth, XYZ->Vstart, XYZ->Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), XYZ->Tex, xyz);
		Stair->Draw();
		for (int i = 0; i < LandNum; i++) {
			DXDrawAnimePolygon(LandPixel[i].DisplayX, LandPixel[i].DisplayY, 0, LandPixel[i].Width, LandPixel[i].Height, LandPixel[i].Ustart, LandPixel[i].Uwidth, LandPixel[i].Vstart, LandPixel[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), LandPixel[0].Tex);
		}

		for (int i = 0; i < FootingNum; i++) {
			DXDrawAnimePolygon(Footing[i].DisplayX, Footing[i].DisplayY, 0, Footing[i].Width, Footing[i].Height, Footing[i].Ustart, Footing[i].Uwidth, Footing[i].Vstart, Footing[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Footing[0].Tex);
		}
		break;
	case GAME_WIN:
		DXDrawPolygon(Scren->X, Scren->Y, 0, Scren->Width, Scren->Height, D3DCOLOR_RGBA(255, 255, 255, 255), Scren->Tex);
		for (int i = 0; i < LandNum; i++) {
			DXDrawAnimePolygon(LandPixel[i].DisplayX, LandPixel[i].DisplayY, 0, LandPixel[i].Width, LandPixel[i].Height, LandPixel[i].Ustart, LandPixel[i].Uwidth, LandPixel[i].Vstart, LandPixel[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), LandPixel[0].Tex);
		}
		for (int i = 0; i < GrassNum; i++) {
			DXDrawAnimePolygon(Grass[i].DisplayX, Grass[i].DisplayY, 0, Grass[i].Width, Grass[i].Height, Grass[i].Ustart, Grass[i].Uwidth, Grass[i].Vstart, Grass[i].Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Grass[0].Tex);
		}
		DXDrawPolygon(TitleInit->X, TitleInit->Y, 0, TitleInit->Width*LOGOBigging, TitleInit->Height*LOGOBigging, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit->Tex);
		DXDrawPolygon(thankPlay->X, thankPlay->Y, 0, thankPlay->Width, thankPlay->Height, D3DCOLOR_RGBA(255, 255, 255, 255), thankPlay->Tex);
		break;
	default:
		break;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	ëOåiâÊñ ï`âÊä÷êîíËã`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageSystem::UpDraw() {
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





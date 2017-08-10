//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		�w�i�����֐�
//		�j�X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
//#include "input.h"
#include "Background.h"
#include "Quantitative.h"

//==========================================================================================================
//		��`
//==========================================================================================================
extern ImaginaryBackground Background;	// ���z�w�i�ʐϑ��
extern DisplayClass Display;	// ���zcamera���
extern byte Status;	// game Mode���

ImageClass *Image;	//	�S�Ẳ�ʏ���printer

ImageClass TitleBackground; //	Title�̔w�i
ImageClass TitleLogo; //	Title��LOGO
ImageClass TitleInit; //	Title�̒�

ImageClass Scren; //	�w�i�i�w�i�F�j
ImageClass Grass[64]; //	�n�ʔw�i
ImageClass LandPixel[LANDPIXELMAX]; //	�n�ʁi�{���j
ImageClass Footing[64];	//�����_
ImageClass XYZ;
byte LandNum; 	// �n�ʂ̐�
byte FootingNum; 	// �����_�̐�
byte GrassNum; 	// �n�ʔw�i�̐�
float xyz;
bool Bingging;
float LOGOBigging;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	��ʏ������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageClass::Init() {
	bool bret;	// Texture������f�ϐ�
	switch (Status)
	{
		//**********************************************************************
		//	Title��ʏ�����
		//**********************************************************************
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
		XYZ.Y = Background.height - 512 - BleedSize;
		XYZ.DisplayX = XYZ.X;
		XYZ.DisplayY = XYZ.Y;

		LandNum = Background.width / LandPixel[0].Width + 1;

		for (int i = 0; i < LandNum; i++) {
			LandPixel[i].Height = 210;
			LandPixel[i].Width = 60;
			LandPixel[i].Y = Background.height - LandPixel[i].Height / 2 - BleedSize;
			LandPixel[i].DisplayY = LandPixel[i].Y;
			LandPixel[i].X = LandPixel[i].Width / 2 + i*LandPixel[i].Width;
			LandPixel[i].DisplayX = LandPixel[i].X;
		}
		Grass[0].Width = 60;
		GrassNum = Background.width / Grass[0].Width + 1;
		for (int i = 0; i < GrassNum; i++) {
			Grass[i].Height = 170;
			Grass[i].Width = 60;
			Grass[i].Y = Background.height - Grass[i].Height / 2 - BleedSize;
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
		Footing[0].Y = Background.height - 270 - BleedSize;
		Footing[1].X = 1224;
		Footing[1].Y = Background.height - 320 - BleedSize;
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

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	��ʍX�V�����֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
		XYZ.Sync(Display);
		break;
	default:
		break;
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Title��ʕ`��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImageClass::TitleDraw() {
	DXDrawPolygon(TitleBackground.X, TitleBackground.Y, 0, TitleBackground.Width, TitleBackground.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleBackground.Tex);
	DXDrawPolygon(TitleLogo.X, TitleLogo.Y, 0, TitleLogo.Width, TitleLogo.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleLogo.Tex);
	/*if (TitleInit.cnt <= 30) {
		DXDrawPolygon(TitleInit.X, TitleInit.Y, 0, TitleInit.Width, TitleInit.Height, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit.Tex);
	}*/
	DXDrawPolygon(TitleInit.X, TitleInit.Y, 0, TitleInit.Width*LOGOBigging, TitleInit.Height*LOGOBigging, D3DCOLOR_RGBA(255, 255, 255, 255), TitleInit.Tex);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	�w�i��ʕ`��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	�O�i��ʕ`��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
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





#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"

IMAGE *Image;
IMAGE Scren;
IMAGE Land;

void IMAGE::Init() {
	bool 
	bret = DXLoadTexture(SCRENTEX, &Scren.Tex);
	bret = DXLoadTexture(LANDTEX, &Land.Tex);



	Land.Width = 1024;
	Land.Height = 512;
	Land.X = Land.Width / 2;
	Land.Y = SCREEN_HEIGHT - Land.Height / 2;
	Land.Ustart = 0.0f;
	Land.Uwidth = 1.0f;
	Land.Vstart = 0.0f;
	Land.Vheight = 1.0f;
	Scren.Width = SCREEN_WIDTH;
	Scren.Height = SCREEN_HEIGHT;
	Scren.X = Scren.Width / 2;
	Scren.Y = Scren.Height / 2;

}

void IMAGE::Update(){
	Land.Ustart += 0.0003f;
}
void IMAGE::TitleDraw(int fcnt) {
	
}
void IMAGE::BackDraw() {
	DXDrawPolygon(Scren.X, Scren.Y, 0, Scren.Width, Scren.Height, D3DCOLOR_RGBA(255, 255, 255, 255), Scren.Tex);
	DXDrawAnimePolygon(Land.X, Land.Y, 0, Land.Width, Land.Height, Land.Ustart, Land.Uwidth, Land.Vstart, Land.Vheight,D3DCOLOR_RGBA(255, 255, 255, 255), Land.Tex);
	
}

void IMAGE::UpDraw(int HP) {

}





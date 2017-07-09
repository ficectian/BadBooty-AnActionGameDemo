#include <windows.h>
#include <d3dx9.h>			//	•`‰æˆ—‚É•K—v
#include "main.h"


typedef struct {
	int height;
	int width;
}ImaginaryBackground;

class DisplayClass {
public:
	POINT Fix;
	POINT MoveDistance;
	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;
	bool ShockOn;
	void Init(ImaginaryBackground Background) {
		height = SCREEN_HEIGHT;
		width = SCREEN_WIDTH;
		Fix.x = 50;
		Fix.y = Background.height - height;
		MoveDistance.x = 0;
		MoveDistance.y = 0;
		ShockOn = false;
	}
	void Shock(){
		if (cnt >= 30) {
			ShockOn = false;
			cnt = 0;
		}
		switch (cnt)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
			MoveDistance.x += 2;
			break;
		default:
			MoveDistance.x -= 2;
			break;
		}
		/*if (cnt < 20) {
			if (cnt % 2 == 0) {
				
			}else{ MoveDistance.x -= 5; }
			cnt += 1;}*/
		
		cnt += 1;
	}
	void Update(ImaginaryBackground Background) {
		if (ShockOn){
			Shock();
		}
		Fix.x = MoveDistance.x;
		Fix.y = Background.height - height + MoveDistance.y;
	}
private:
	byte cnt = 0;
	
};
class ImageClass{
public:

	float	X;
	float	Y;
	float DisplayX;
	float DisplayY;
	void Init();
	void Update();
	void TitleDraw(int);
	void BackDraw();
	void UpDraw(int);
	void Sync(DisplayClass Display) {
		DisplayX = X - Display.MoveDistance.x;
	}
	float Width;
	float Height;
private:
	LPDIRECT3DTEXTURE9 Tex;
	
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
};

class UIClass {
public:


	void Init();
	/*void Update();
	void BackDraw();*/
	void Draw(int);
	
private:
	LPDIRECT3DTEXTURE9 Tex;
	float	X;
	float	Y;
	float Width;
	float Height;
	float Ustart = 0.0f;
	float Vstart = 0.0f;
	float Uwidth = 1.0f;
	float Vheight = 1.0f;
};
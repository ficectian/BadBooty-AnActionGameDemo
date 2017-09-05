//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		”wŒiHear File
//		—j•X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <d3dx9.h>			//	•`‰æˆ—‚É•K—v
#include "main.h"
#include "Quantitative.h"


typedef struct {
	int height;
	int width;
}ImaginaryBackground;

class DisplayClass {
public:
	float X;
	float Y;
	float Left_X() {
		return X - width / 2;
	}
	float Up_Y() {
		return Y - height / 2;
	}
	float Right_X() {
		return X + width / 2;
	}
	float Down_Y() {
		return Y + height / 2;
	}

	POINT MoveDistance;
	int height;
	int width;
	byte ShockOn;
	void Init(ImaginaryBackground Background) {
		X = Background.width/2;
		Y =  Background.height / 2;
		MoveDistance.x = Left_X();
		MoveDistance.y = Up_Y();
	}
	void Shock(byte ShockLv){
		if (cnt >= 40) {
			ShockOn = 0;
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
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
			X -= ShockLv;
			Y -= ShockLv - 1.0f;

			break;
		default:
			X += ShockLv;
			Y += ShockLv - 1.0f;

			break;
		}

		
		cnt += 1;
	}
	void Update(ImaginaryBackground Background) {
		extern PlayerClass Player;
		if (ShockOn != 0) {
			Shock(ShockOn);
		}
		else
		{
			if (Player.X - width / 2 > BleedSize && Player.X + width / 2 < Background.width - BleedSize) {
				/*X = Player.X;*/
				if (X > Player.X) {
					if (Player.StatusStyle == DefenseStatus) {
						X -= PLAYERSPEED/2;
					}
					/*else if (Player.StatusStyle == JumpStatus) {
						X = Player.X;
					}*/
					else{
						X -= PLAYERSPEED;
					}
				}
				if (X < Player.X) {
					if (Player.StatusStyle == DefenseStatus) {
						X += PLAYERSPEED / 2;
					}
					/*else if (Player.StatusStyle == JumpStatus) {
						X = Player.X;
					}*/
					else {
						X += PLAYERSPEED;
					}
				}
			}
			if (Player.Y+ InitialPlayerHeight - height > BleedSize && Player.Y + InitialPlayerHeight < Background.height - BleedSize) {
				if (Y > Player.Y - height / 2 + InitialPlayerHeight + Player.Height / 2) {
					if (Player.StatusStyle == JumpStatus) {
						Y = Player.Y - height / 2 + InitialPlayerHeight + Player.Height / 2;
					}else{
						Y -= PLAYERSPEED;
					}
				}
				
				if (Y < Player.Y - height / 2 + InitialPlayerHeight + Player.Height / 2) {
					if (Player.StatusStyle == JumpStatus) {
						Y = Player.Y - height / 2 + InitialPlayerHeight + Player.Height / 2;
					}else {
						Y += PLAYERSPEED;
					}
				}
				 
			}
			
		}
		MoveDistance.x = Left_X();
		MoveDistance.y = Up_Y();
		
	}
	DisplayClass() {
		height = SCREEN_HEIGHT;
		width = SCREEN_WIDTH;
		MoveDistance.x = 0;
		MoveDistance.y = 0;
		ShockOn = 0;
		cnt = 0;
	}
private:
	byte cnt;
	
};
class ImageClass{
public:

	float	X;
	float	Y;
	float DisplayX;
	float DisplayY;
	void Init();
	void Update();
	void TitleDraw();
	void BackDraw();
	void UpDraw();
	void Sync(DisplayClass Display) {
		DisplayX = X - Display.MoveDistance.x;
		DisplayY = Y - Display.MoveDistance.y;
	}
	float Width;
	float Height;
	ImageClass() {
		Tex = NULL;
		Ustart = 0.0f;
		Uwidth = 1.0f;
		Vstart = 0.0f;
		Vheight = 1.0f;
		cnt = 0;
	}
private:
	LPDIRECT3DTEXTURE9 Tex;
	
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	byte cnt;
};

class UIClass {
public:


	void Init();
	/*void Update();
	void BackDraw();*/
	void Draw(int);
	UIClass() {
		Ustart = 0.0f;
		Vstart = 0.0f;
		Uwidth = 1.0f;
		Vheight = 1.0f;
	}
private:
	LPDIRECT3DTEXTURE9 Tex;
	float	X;
	float	Y;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
};

class StairClass {
public:

	float	X;
	float	Y;
	float DisplayX;
	float DisplayY;
	void Init();
	void Update();
	void Draw();
	StairClass() {
		Tex = NULL;
		Ustart = 0.0f;
		Vstart = 0.0f;
		Uwidth = 1.0f;
		Vheight = 1.0f;
		Height = 40;
		Width = 50;
	}
	void Sync(DisplayClass Display) {
		DisplayX = X - Display.MoveDistance.x;
		DisplayY = Y - Display.MoveDistance.y;
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
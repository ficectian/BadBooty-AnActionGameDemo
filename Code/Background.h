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
	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;
	byte ShockOn;
	void Init(ImaginaryBackground Background) {
		extern PlayerClass Player;
		height = SCREEN_HEIGHT;
		width = SCREEN_WIDTH;
		MoveDistance.x = 0;
		MoveDistance.y = 0;
		ShockOn = 0;
		X = Background.width/2;
		Y = Background.height / 2;;
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
					else if (Player.StatusStyle == JumpStatus) {
						X = Player.X;
					}
					else{
						X -= PLAYERSPEED;
					}
				}
				if (X < Player.X) {
					if (Player.StatusStyle == DefenseStatus) {
						X += PLAYERSPEED / 2;
					}
					else if (Player.StatusStyle == JumpStatus) {
						X = Player.X;
					}
					else {
						X += PLAYERSPEED;
					}
				}
			}
			if (Player.Y - height / 2 > BleedSize && Player.Y + height / 2 < Background.height - BleedSize) {
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
		Ustart = 0.0f;
		Vstart = 0.0f;
		Uwidth = 1.0f;
		Vheight = 1.0f;
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
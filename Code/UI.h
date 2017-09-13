//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		UI Hear File
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <d3dx9.h>			//	ï`âÊèàóùÇ…ïKóv
#include "main.h"
#include "Quantitative.h"

class UIClass {
public:


	void Init();
	void Draw();
	void Draw(float, float);
	void Draw(float, float, float, float, float, float);
	UIClass() {
		Ustart = 0.0f;
		Vstart = 0.0f;
		Uwidth = 1.0f;
		Vheight = 1.0f;
	}
	LPDIRECT3DTEXTURE9 Tex;
	float	X;
	float	Y;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
private:
	
	
};

class UIDrawClass
{
public:
	UIDrawClass() {
		PlayerHeadBackground = new UIClass;
		PlayerHead = new UIClass;
		PlayerHP = new UIClass;
	}

	~UIDrawClass() {
		delete PlayerHeadBackground;
		delete	PlayerHead;
		delete PlayerHP;
		delete EnemyHP;
		delete EnemyHPBackground;
	}
	void Init();
	void Draw(int);
private:
	UIClass	*PlayerHeadBackground;
	UIClass	*PlayerHead;
	UIClass	*PlayerHP;
	UIClass	*EnemyHP;
	UIClass	*EnemyHPBackground;
};



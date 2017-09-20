//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		Stage Hear File
//		—j•X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <d3dx9.h>			//	•`‰æˆ—‚É•K—v

#include "Player.h"
#include "Background.h"
#include "Quantitative.h"

enum Stages{
	NULLStage,
	instructionStage1,
	instructionStage2,
	instructionStage3,
	easyStage,
	normalStage
};

class GameStage
{
public:
	float startX;
	float startY;
	float wdith;
	float height;
	float endX;
	float endY;
	bool complete;
	byte swordEnemyQty;
	byte footingQty;
	byte stairQty;
	//ImageClass stageEndImage;
	GameStage() {
		complete = false;
	}
	~GameStage();

private:

};

//class Footings :public ImageClass {
//
//};

class StageHandle {
public:
	GameStage *gameStage;
	//Footings *Footing;	//—Ž‰º“_
	Stages stageNumber;
	//void init();
	void init(Stages stageNO);
	void update();
	void Draw();
	StageHandle() {
		gameStage = new GameStage;
		stageNumber = instructionStage1;
		//bool bret = DXLoadTexture(STAGEENDTEX, &gameStage->stageEndImage.Tex);
	}
	~StageHandle() {
		delete[] gameStage;
		//delete[] Footing;
	}
};

void StageHandle::init(Stages stageNO) {
	extern DisplayClass Display;
	extern ImaginaryBackground Background;
	/*extern StairClass *Stair;
	extern EnemyClass *Enemy;*/
	extern PlayerClass *Player;
	switch (stageNO)
	{
	case NULLStage:
		gameStage->wdith = 1500.0f;
		gameStage->height = 3000.0f;
		gameStage->startX = 100 + (float)Display.width / 2;
		gameStage->startY = (float)(Background.height - InitialPlayerHeight - 64 - BleedSize);
		gameStage->endX = (float)Background.width / 2 - 100;
		gameStage->endY = (float)(Background.height - InitialPlayerHeight - 64 - BleedSize);
		gameStage->complete = false;
		break;
	case instructionStage1:
		break;
	case instructionStage2:
		break;
	case instructionStage3:
		break;
	case easyStage:
		break;
	case normalStage:
		break;
	default:
		break;
	}

	Background.height = gameStage->wdith;
	Background.width = gameStage->height;
	Display.Init(Background);

	if (Player == NULL)
	{
		Player = new PlayerClass;
	}
	Player->Initial.x = gameStage->startX;
	Player->Initial.y = gameStage->startY;
	Player->Init();
}

void StageHandle::update() {
	extern PlayerClass *Player;
	extern int GameLoop;

	switch (stageNumber)
	{
	case NULLStage:
		if (GameLoop > 3) { gameStage->complete = true; }
		break;
	case instructionStage1:
		break;
	case instructionStage2:
		break;
	case instructionStage3:
		break;
	case easyStage:
		break;
	case normalStage:
		break;
	default:
		break;
	}


	if (gameStage->complete && Player->X == gameStage->endX && Player->Y == gameStage->endY) {
		switch (stageNumber)
		{
		case NULLStage:
			GameLoop = 0;
			//Status = TITLE;
			stageNumber = NULLStage;
			break;
		case instructionStage1:
			stageNumber = instructionStage2;
			break;
		case instructionStage2:
			stageNumber = instructionStage3;
			break;
		case instructionStage3:
			stageNumber = easyStage;
			break;
		case easyStage:
			stageNumber = normalStage;
			break;
		case normalStage:
			//stageNumber = instructionStage2;
			break;
		default:
			break;
		}
		init(stageNumber);
	}
}
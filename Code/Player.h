#include <windows.h>
#include <d3dx9.h>			//	描画処理に必要
#define PLAYERTEX TEXT("image/player.tga")
#define ENEMYTEX TEXT("image/Enemy.tga")

#define	GRASSTEX TEXT("image/Grass.png")
#define SCRENTEX	TEXT("image/scren.png")
#define LANDPIXELTEX	TEXT("image/LandPixel.png")
#define LANDTEX	TEXT("image/Land.png")


#define HeadBackgroundTex	TEXT("image/HeadBackground.png")
#define HeadTex	TEXT("image/Head.png")
#define PlayerHPTEX	TEXT("image/PlayerHP.png")
#define HP2TEX	TEXT("image/HP1.png")
#define STAIRTEX	TEXT("image/Stair.png")

#define	TITLETEX	 TEXT("image/title.png")
#define	TITLEINTTEX	TEXT("image/titleint.png")

#define LANDPIXELMAX (256)
#define PLAYER_HEIGHT	(64)
#define	PLAYER_WIDTH	(80)



#define PLAYERSPEED (5)
#define SWORDENEMYSPEED (3)

#define WINDOWICO TEXT("image/ico.ico")

enum {
	TITLE,
	GAME_PLAY,
	RESULT,
	GAME_OVER,
	GAME_WIN
};

enum {
	StationStatus,
	RunStatus,
	JumpStatus,
	DefenseStatus,
	AttackStatus
	//DoubleJumpStatus
};

enum {
	EnemyRunAnime,
	EnemyAttAnime,
	EnemyHitAnime
};

enum {
	PatrolMod,
	HitMod
};
//=========================================
//		構造体定義
//=========================================
class EnemyClass {
	

public: 
	float DisplayX;
	float DisplayY;
	float X;	//年齢
	float Y;	//攻撃力
	int HitBox_X() {
		if (FacedLeft) {
			return (int)X - 3;
		}
		else {
			return (int)X - 35;
		}
	}
	int HitBox_Y() {
		return (int)Y - 39;
	}
	int HitBox_Wdith = 38;
	int HitBox_Height = 103;
	int Hp;	//体力
	void AllInit();
	void AllUpdate();
	void AllDraw();
	//void Sync(DisplayClass Display) {
	//	DisplayX = X - Display.MoveDistance.x;
	//}
	char ActionMod;
	void HitOn();
	bool FacedLeft;
	char InvincibleTime;
	EnemyClass() {
		InvincibleTime = 0;
	}

private:
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
	float InitialX;
	float InitialY;
	char cnt;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;

	const byte AnimeRun[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0xff };//0xff：終了コード
	const byte AnimeAttack[64] = { 4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,4,4,4,4,4,4,0xff };
	const byte AnimeHit[64] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0xff };
	const byte *Anime_data[3] = { AnimeRun,AnimeAttack,AnimeHit };
	char StatusStyle;
	void Animetion();
	void	Patrol();
	void Update();
	void Draw();
	void Hit();
	char HitCnt;
	
};


class PlayerClass {
	
public:
	float X;
	float Y;
	float DisplayX;
	float DisplayY;
	float Width;
	float Height;
	int	Hp;	//体力
	int AttBox_X() {
		if (FacedRight) {
			return (int)X + 1;
		}else{
			return (int)X - 45;
		}
	}
	int AttBox_Y() {
		return (int)Y - 61;
	}
	int AttBox_Wdith;
	int AttBox_Height;
	void Init();
	void Update();
	void Draw();
	bool FallHitTest(  float, float, float, float);
	bool HitStair();
	void Operation();
	void Jump();
	void Attack();
	void Animetion();
	void AllHitTest();
	byte StopTime;
PlayerClass() {

		Width = 128;
		Height = 128;
		Ustart = 0.0f;
		Uwidth = (float)1 / 8;
		Vstart = 0.0f;
		Vheight = (float)1 / 8;
		FacedRight = true;
		StatusStyle = StationStatus;
		cnt = 0;
		JumpCnt = 0;
		InDoubleJumpStatus = false;
		InFall = false;
		AttBox_Wdith = 46;
		AttBox_Height = 69;
		StopTime = 0;
	}
private:
	LPDIRECT3DTEXTURE9 Tex;
	//LPDIRECT3DTEXTURE9	DeadTex;
	//LPDIRECT3DTEXTURE9	InvincibleTex;
	POINT Initial;
	int MaxHp;
	float JumpStartY;
	
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	bool InDoubleJumpStatus;
	const byte AnimeStation[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0xff };//0xff：終了コード
	const byte AnimeRun[64] = { 8,8,8,8,8,9,9,9,9,9,9,9,10,10,10,10,10,9,9,9,9,9,9,9,0xff };
	const byte AnimeJump[64] = { 16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,0xff };
	const byte AnimeDefense[64] = { 24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,25,25,25,25,25,25,25,25,25,0xff };//0xff：終了コード
	const byte AnimeAttack[64] = {32,32,32,32,32,32,32,32,32,32,32,32,33,33,33,33,33,33,33,33,33,33,33,33, 34,34,34,34,34,34,34,34,34,34,34,34,35,35,35,35,35,35,35,35,35,35,35,35,0xff };//0xff：終了コード
	const byte *Anime_data[5] = { AnimeStation,AnimeRun,AnimeJump,AnimeDefense,AnimeAttack };
	char cnt;
	bool FacedRight;
	char JumpCnt;
	char StatusStyle;
	bool InFall;
	int OnStairNum;
	bool AttHit(float x, float y, float w, float h) {
		if (((AttBox_Y() + AttBox_Height >= y) && (AttBox_Y() - h <= y)) && ((AttBox_X() + AttBox_Wdith >= x) && (AttBox_X() - w <= x)))
		{
			return true;
		}
		else
		{
			return 	false;
		}
	}
};

//typedef struct{
//	LPDIRECT3DTEXTURE9 Tex;
//	int		Flag;
//	float	X;	
//	float	DefX;
//	float	Y;
//	bool	Disp;
//	bool notshooting = true;
//	void Init(int);
//	void Update(int);
//	void Hit(int);
//	void Draw();
//}SHOOT;


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		関数宣言
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//float		UpMove(float, float, float, float);				//上移動関数
//float		RightMove(float, float, float, float);			//左移動関数
//float		LeftMove(float, float, float, float);				//左移動関数
//float		DownMove(float, float, float, float);				//下移動関数
bool		HitTest(float, float, float, float, float, float, float, float);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

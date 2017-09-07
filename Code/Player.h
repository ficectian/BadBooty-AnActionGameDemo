//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		character Hear File
//		曜氷
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <d3dx9.h>			//	描画処理に必要


enum {
	TITLE,
	GAME_START,
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
	AttackStatus,
	HitStatus,
	ClimbStatus,
	EvilHitStatus
	//DoubleJumpStatus
};

enum {
	EnemyRunAnime,
	EnemyAttAnime,
	EnemyHitAnime
};

enum {
	PatrolMod,
	HitMod,
	TrackMod,
	ReturnMod,
	EvilMod
};
//=========================================
//		構造体定義
//=========================================


class PlayerClass {
	
public:
	float X;
	float Y;
	float DisplayX;
	float DisplayY;
	float Width;
	float Height;
	float	Hp;	//体力
	float AttBox_X() {
		if (FacedRight) {
			return (float)X + 1;
		}else{
			return (float)X - 45;
		}
	}
	float AttBox_Y() {
		return (float)Y - 61;
	}
	float AttBox_Wdith;
	float AttBox_Height;
	float EvilBox_Wdith;
	float EvilBox_Height;
	float EvilBox_X(){
		if (FacedRight) {
			return (float)X - 5;
		}
		else {
			return (float)X + 5;
		}
	}
	float EvilBox_Y() {
		return (float)Y - 32;
	}
	float HitBox_X() {
		if (FacedRight) {
			return (float)X - 43;
		}
		else {
			return (float)X;
		}
	}
	float HitBox_Y() {
		return (float)Y - 47;
	}
	float HitBox_Wdith;
	float HitBox_Height;
	void Init();
	void Update();
	void Draw();
	bool FallHitTest(  float, float, float, float);
	bool HitStair();
	void Operation();
	void Jump();
	void Attack();
	void Climb();
	void EvilHit();
	void Animetion();
	void AllHitTest();
	bool BoundaryHitTest();
	byte StopTime;
	char StatusStyle;

PlayerClass() {
		Tex = NULL;
		InvincibleTime = 0;
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
		AttBox_Wdith = 46.0f;
		AttBox_Height = 69.0f;
		HitBox_Wdith = 43.0f;
		HitBox_Height = 111.0f;
		EvilBox_Wdith = 69.0f;
		EvilBox_Height = 42.0f;
		StopTime = 0;
		EnemyInPlayerRight = false;
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
	const byte AnimeStation[64] = { 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0xff };//0xff：終了コード
	const byte AnimeRun[64] = {8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,0xff };
	const byte AnimeJump[64] = { 16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,0xff };
	const byte AnimeDefense[64] = { 24,24,24,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,25,25,0xff };//0xff：終了コード
	const byte AnimeAttack[64] = {32,32,32,32,32,32,33,33,33,33,33,33,33,33,33,33,33,33, 34,34,34,34,34,34,34,34,34,35,35,35,35,35,35,35,35,35,35,35,35,0xff };//0xff：終了コード
	const byte AnimeHit[64] = { 18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,0xff };//0xff：終了コード
	const byte AnimeClimb[64] = { 40,40,40,40,40,40,41,41,41,41,42,42,42,42,42,42,43,43,43,43,0xff };
	const byte AnimeEvilHit[64] = { 48,48,48,48,48,48,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,50,50,50,50,50,50,50,50,50,51,51,51,51,51,51,51,51,51,51,51,51,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,48,48,48,48,48,48,0xff };
	const byte *Anime_data[8] = { AnimeStation,AnimeRun,AnimeJump,AnimeDefense,AnimeAttack,AnimeHit,AnimeClimb ,AnimeEvilHit };
	char cnt;
	bool FacedRight;
	char JumpCnt;
	bool InFall;
	int OnStairNum;
	bool MoveHit();
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
	bool EvilHit(float x, float y, float w, float h) {
		if (((EvilBox_Y() + EvilBox_Height >= y) && (EvilBox_Y() - h <= y)) && ((EvilBox_X() + EvilBox_Wdith >= x) && (EvilBox_X() - w <= x)))
		{
			return true;
		}
		else
		{
			return 	false;
		}
	}
	bool HitHit(float x, float y, float w, float h) {
		if (((HitBox_Y() + HitBox_Height >= y) && (HitBox_Y() - h <= y)) && ((HitBox_X() + HitBox_Wdith >= x) && (HitBox_X() - w <= x)))
		{
			return true;
		}
		else
		{
			return 	false;
		}
	}
	void HitOn();
	void Hit();
	char HitCnt;
	char InvincibleTime;
	bool EnemyInPlayerRight;
};




class EnemyClass {


public:
	float DisplayX;
	float DisplayY;
	float X;	//年齢
	float Y;	//攻撃力
	float HitBox_X() {
		if (FacedLeft) {
			return (float)X - 3;
		}
		else {
			return (float)X - 35;
		}
	}
	float HitBox_Y() {
		return (float)Y - 39;
	}
	float HitBox_Wdith;
	float HitBox_Height;

	float AttBox_X() {
		if (FacedLeft) {
			return (float)X - 61;
		}
		else {
			return (float)X + 4;
		}
	}
	float AttBox_Y() {
		return (float)Y - 39;
	}
	float AttBox_Wdith;
	float AttBox_Height;
	int Hp;	//体力
	int MaxHp;
	void AllInit();
	void AllUpdate();
	void AllDraw();
	//void Sync(DisplayClass Display) {
	//	DisplayX = X - Display.MoveDistance.x;
	//}
	char ActionMod;
	void HitOn();
	void EvilOn();
	bool FacedLeft;
	char InvincibleTime;
	void Track();
	void Return();
	bool PlayerHit() {
		extern PlayerClass Player;
		if (((HitBox_Y() + HitBox_Height >= Player.HitBox_Y()) && (HitBox_Y() - Player.HitBox_Height <= Player.HitBox_Y())) && ((HitBox_X() + HitBox_Wdith >= Player.HitBox_X()) && (HitBox_X() - Player.HitBox_Wdith <= Player.HitBox_X())))
		{
			return true;
		}
		else
		{
			return 	false;
		}
	}
	bool AllHaveHp();
	EnemyClass() {
		//bool bret = DXLoadTexture(ENEMYTEX, &Tex);
		Tex = NULL;
		Width = 128;
		Height = 128;
		InvincibleTime = 0;
		MaxHp = 5;
		Hp = MaxHp;
		Ustart = 0.0f;
		Uwidth = (float)1 / 4;
		Vstart = 0.0f;
		Vheight = (float)1 / 4;
		FacedLeft = true;
		StatusStyle = EnemyRunAnime;
		cnt = 0;
		ActionMod = PatrolMod;
		HitBox_Wdith = 38.0f;
		HitBox_Height = 103.0f;
		AttBox_Wdith = 57.0f;
		AttBox_Height = 60.0f;
	}
	byte AnimeCnt() {
		const byte *ptEnemyAnime = Anime_data[StatusStyle];
		return *(ptEnemyAnime + cnt);
	}
private:
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
	float InitialX;
	float InitialY;
	
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;

	
	void Animetion();
	void	Patrol();
	void Update();
	void Draw();
	void Hit();
	void Evil();
	char HitCnt;
	const byte AnimeRun[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0xff };//0xff：終了コード
	const byte AnimeAttack[64] = { 4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0xfe };
	const byte AnimeHit[64] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0xff };
	const byte *Anime_data[3] = { AnimeRun,AnimeAttack,AnimeHit };
	char StatusStyle;
	char cnt;
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
//bool		HitTest(float, float, float, float, float, float, float, float);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

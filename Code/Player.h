#include <windows.h>
#include <d3dx9.h>			//	描画処理に必要
#define PLAYERTEX TEXT("image/player.png")
#define	GRASSTEX TEXT("image/Grass.png")
#define SCRENTEX	TEXT("image/scren.png")
#define LANDPIXELTEX	TEXT("image/LandPixel.png")


#define	TITLETEX	 TEXT("image/title.png")
#define	TITLEINTTEX	TEXT("image/titleint.png")

#define LANDPIXELMAX (256)
#define PLAYER_HEIGHT	(64)
#define	PLAYER_WIDTH	(80)



#define PLAYERSPEED (5)

#define WINDOWICO TEXT("image/ico.ico")

//=========================================
//		構造体定義
//=========================================
class EnemyClass {
	
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
public: 
	float X;	//年齢
	float Y;	//攻撃力
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	int nHp;	//体力
	float Flg;
	int Hitting;
	void Init(int);
	void Update(int);
	void Draw();
	int cnt;
};


class PlayerClass {
	
public:
	float X;
	float Y;
	int	Hp;	//体力
	void Init();
	void Update();
	void Draw();
	bool FallHitTest(  float, float, float, float);
	void Operation();
	void Jump();
	void Attack();
	void Animetion();
private:
	LPDIRECT3DTEXTURE9 Tex;
	//LPDIRECT3DTEXTURE9	DeadTex;
	//LPDIRECT3DTEXTURE9	InvincibleTex;
	POINT Initial;
	float JumpStartY;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	bool InDoubleJumpStatus;
	const byte AnimeStation[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0xff };//0xff：終了コード
	const byte AnimeRun[64] = { 8,8,8,8,8,9,9,9,9,9,9,9,10,10,10,10,10,9,9,9,9,9,9,9,0xff };
	const byte AnimeJump[64] = { 16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,0xff };
	const byte AnimeDefense[64] = { 24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,25,25,25,25,25,25,25,25,25,0xff };//0xff：終了コード
	const byte AnimeAttack[64] = { 32,32,32,32,32,32,33,33,33,33,33,33,33,33,34,34,34,34,34,34,33,33,33,33,33,33,33,32,32,32,32,32,32,0xff };//0xff：終了コード
	const byte *Anime_data[5] = { AnimeStation,AnimeRun,AnimeJump,AnimeDefense,AnimeAttack };
	char cnt;
	bool FacedRight;
	char JumpCnt;
	char StatusStyle;
	bool InFall;
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

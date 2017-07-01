#include <windows.h>
#include <d3dx9.h>			//	描画処理に必要
#define PLAYERTEX TEXT("image/player.png")
#define	LANDTEX TEXT("image/land.png")
#define SCRENTEX	TEXT("image/scren.png")


#define	TITLETEX	 TEXT("image/title.png")
#define	TITLEINTTEX	TEXT("image/titleint.png")


#define PLAYER_HEIGHT	(64)
#define	PLAYER_WIDTH	(80)



#define PLAYERSPEED (5)

#define WINDOWICO TEXT("image/ico.ico")

//=========================================
//		構造体定義
//=========================================
typedef struct {
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
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
}ENEMY;

typedef struct {
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
	LPDIRECT3DTEXTURE9	InvincibleTex;
	float X;	
	float Y;	
	float JumpStartY;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	int	nHp;	//体力
	//int InvincibleState;
	void Init();
	void Update();
	void Draw();
	bool InDoubleJumpStatus;
	const byte AnimeStation[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0xff };//0xff：終了コード
	const byte AnimeRun[64] = { 8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,0xff };
	const byte AnimeJump[64] = { 16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,0xff };
	const byte *Anime_data[4] = { AnimeStation,AnimeRun,AnimeJump,AnimeStation };
	char cnt;
	bool FacedRight;
	char JumpCnt;
	char StatusStyle;
}PLAYER;

typedef struct{
	LPDIRECT3DTEXTURE9 Tex;
	int		Flag;
	float	X;	
	float	DefX;
	float	Y;
	bool	Disp;
	bool notshooting = true;
	void Init(int);
	void Update(int);
	void Hit(int);
	void Draw();
}SHOOT;



typedef struct  {
	LPDIRECT3DTEXTURE9 Tex;
	float	X; 
	float	Y;
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	void Init();
	void Update();
	void TitleDraw(int);
	void BackDraw();
	void UpDraw(int);
}IMAGE;

enum {
	TITLE,
	GAME_PLAY,
	RESULT,
	GAME_OVER,
	GAME_WIN
};

enum {
	StationAnime,
	RunAnime,
	JumpAnime
};
enum {
	StationStatus,
	RunStatus,
	JumpStatus,
	DefenseStatus
	//DoubleJumpStatus
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		関数宣言
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float		UpMove(float, float, float, float);				//上移動関数
float		RightMove(float, float, float, float);			//左移動関数
float		LeftMove(float, float, float, float);				//左移動関数
float		DownMove(float, float, float, float);				//下移動関数
bool		HitTest(float, float, float, float, float, float, float, float);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

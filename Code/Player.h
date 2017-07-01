#include <windows.h>
#include <d3dx9.h>			//	�`�揈���ɕK�v
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
//		�\���̒�`
//=========================================
typedef struct {
	LPDIRECT3DTEXTURE9 Tex;
	LPDIRECT3DTEXTURE9	DeadTex;
	float X;	//�N��
	float Y;	//�U����
	float Width;
	float Height;
	float Ustart;
	float Vstart;
	float Uwidth;
	float Vheight;
	int nHp;	//�̗�
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
	int	nHp;	//�̗�
	//int InvincibleState;
	void Init();
	void Update();
	void Draw();
	bool InDoubleJumpStatus;
	const byte AnimeStation[64] = { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0xff };//0xff�F�I���R�[�h
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
//		�֐��錾
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float		UpMove(float, float, float, float);				//��ړ��֐�
float		RightMove(float, float, float, float);			//���ړ��֐�
float		LeftMove(float, float, float, float);				//���ړ��֐�
float		DownMove(float, float, float, float);				//���ړ��֐�
bool		HitTest(float, float, float, float, float, float, float, float);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

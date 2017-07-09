#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "input.h"
#include "Background.h"

//==========================================================================================================
//		�֐���`
//==========================================================================================================

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�����蔻�菈���֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			HitTest(float X1, float Y1, float W1, float H1, float X2, float Y2, float W2, float H2)
{
	float XX1 = X1 - W1 / 2;
	float	XX2 = X2 - W2 / 2;
	float YY1 = Y1 - H1 / 2;
	float YY2 = Y2 - H2 / 2;

	if (((YY1 + H1 >= YY2) && (YY1 - H2 <= YY2)) && ((XX1 + W1 >= XX2) && (XX1 - W2 <= XX2)))
	{
		return true;
	}
	else
	{
		return 	false;
	}

}




//==========================================================================================================
//		��`
//==========================================================================================================
extern DisplayClass Display;
extern ImaginaryBackground Background;
PlayerClass Player;
extern ImageClass Footing[256];
extern byte FootingNum;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player�������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Init() {
	bool bret = DXLoadTexture(PLAYERTEX, &Tex);
	//bret = DXLoadTexture(BOOWTEX, &DeadTex);
	//bret = DXLoadTexture(INVINCIBLETEX, &InvincibleTex);
	Initial.x = (float)Display.width / 2;
	Initial.y = (float)(Display.height - 50 - 64);
	X = Initial.x;
	Y = Initial.y;
	Width = 128;
	Height =128;
	MaxHp = 28;
	Hp = MaxHp;
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
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player��������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			PlayerClass::FallHitTest(float X1, float Y1, float W, float H)
{
	float XX1 = X - 24/ 2;
	if (FacedRight) { 
		XX1 -= 5; 
	}else { 
		XX1 += 5; 
	}//�C��
	float	XX2 = X1 - W / 2;
	float YY1 = Y + Height / 2-10;
	float YY2 = Y1 - H / 2;

	if (((YY1 + 10 >= YY2) && (YY1 - H <= YY2)) && ((XX1 + 24 >= XX2) && (XX1 - W <= XX2)))
	{
		return true;
	}
	else
	{
		return 	false;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Game Loop��Player�X�V�֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Update() {

	if (Hp > 0) {
		if (StatusStyle != AttackStatus) {
			Operation();
			Jump();
		}else {
			Attack();
		}	
	}


	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player�`��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Draw() {
	Animetion();

	if (FacedRight) {
		DXDrawAnimePolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}else {
		DXDrawPlayerRevPolygon(X, Y, 0, Width, Height, Ustart, Uwidth, Vstart, Vheight, D3DCOLOR_RGBA(255, 255, 255, 255), Tex);//player
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player����֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void	PlayerClass::Operation() {
	//**********************************************************************
	//	Player �ړ�
	//**********************************************************************
	if (GetKeyboardPress(DIK_A) | GetKeyboardPress(DIK_LEFT)) {
		if (FacedRight) {
			if (X - Width / 2 < Display.width / 4 && Display.Fix.x + Display.MoveDistance.x > 10) {
				Display.MoveDistance.x -= PLAYERSPEED / 2;
			}
			else if (X - Width / 2 > 0) { X -= PLAYERSPEED / 2; }


			if (StatusStyle != JumpStatus) {
				if (StatusStyle != DefenseStatus) { cnt = 0;  StatusStyle = DefenseStatus; }
			}
		}
		else {
			if (X - Width / 2 < Display.width / 4 && Display.Fix.x + Display.MoveDistance.x > 10) {
				Display.MoveDistance.x -= PLAYERSPEED;
			}
			else if (X - Width / 2 > 0) {
				X -= PLAYERSPEED;
			}
			if (StatusStyle != JumpStatus) {
				if (StatusStyle != RunStatus) {
					cnt = 0;
					StatusStyle = RunStatus;
				}
			}
		}
				
			
	}
	
	if (GetKeyboardPress(DIK_D) | GetKeyboardPress(DIK_RIGHT)) {
		if (FacedRight) {
			if (X + Width / 2 > Display.width * 3 / 4 && Display.MoveDistance.x + Display.width <= Background.width - 10) {
				Display.MoveDistance.x += PLAYERSPEED;
			}
			else if (X + Width / 2 < Display.width) { X += PLAYERSPEED; }

			if (StatusStyle != JumpStatus) {
				if (StatusStyle != RunStatus) {
					cnt = 0;
					StatusStyle = RunStatus;
				}
			}
		}
		else {
			if (X + Width / 2 > Display.width * 3 / 4 && (Display.MoveDistance.x + Display.width) <= Background.width - 10) {
				Display.MoveDistance.x += PLAYERSPEED / 2;
			}
			else if (X + Width / 2 < Display.width) { X += PLAYERSPEED / 2; }
			if (StatusStyle != JumpStatus) { if (StatusStyle != DefenseStatus) { cnt = 0;  StatusStyle = DefenseStatus; } }
		}
	}

	//**********************************************************************
	//	Player �U��
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_H)) {
		if (StatusStyle != JumpStatus) {
			cnt = 0;
			StatusStyle = AttackStatus;
			Display.ShockOn = true;
		}
	}

	//**********************************************************************
	//	Player �]�g
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_LSHIFT)) {
		FacedRight = !FacedRight;
		if (StatusStyle == RunStatus) { StatusStyle = DefenseStatus; }
	}

	//**********************************************************************
	//	Player �@jump
	//**********************************************************************
	if (GetKeyboardTrigger(DIK_SPACE)) {
		if (StatusStyle != JumpStatus && !InDoubleJumpStatus) {
			JumpStartY = Initial.y;
			JumpCnt = 0;
			cnt = 0;
			StatusStyle = JumpStatus;
		}
		else if (!InDoubleJumpStatus) {
			JumpCnt = 0;
			cnt = 0;
			InDoubleJumpStatus = true;
		}
	}

	//**********************************************************************
	//	��~
	//**********************************************************************
	if (GetKeyboardRelease(DIK_A) || GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_D) || GetKeyboardRelease(DIK_RIGHT))
	{
		if (StatusStyle != JumpStatus) {
			if (StatusStyle != StationStatus) { cnt = 0; StatusStyle = StationStatus; }
		}
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player jump�Ɨ��������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Jump() {
	if (StatusStyle == JumpStatus) {
		JumpCnt += 1;
		//float vg = 10 - 0.98f*fcnt;
		Y -= 14 - 0.98f*JumpCnt;;
		const byte *ptAnime = Anime_data[StatusStyle];

		if (Y > JumpStartY) {
			Y = JumpStartY;
			JumpCnt = 0;
			cnt = 0;
			JumpStartY = 0.0f;
			InDoubleJumpStatus = false;
			StatusStyle = StationStatus;
			//Display.ShockOn = true;
		}
		if (*(ptAnime + cnt) == 18) {
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)/*HitTest(, Y, 20, Height, Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)*/) {
					Y = Footing[i].DisplayY - Footing[i].Height / 2 - Height / 2 + 10;

					JumpCnt = 0;
					cnt = 0;
					JumpStartY = 0.0f;
					InDoubleJumpStatus = false;
					StatusStyle = StationStatus;
				}
			}
		}
	}
	else {
		//����
		if (Y != Initial.y) {
			InFall = true;
			for (int i = 0; i < FootingNum; i++) {
				if (Player.FallHitTest(Footing[i].DisplayX, Footing[i].DisplayY, Footing[i].Width, Footing[i].Height)) {
					InFall = false;
					break;
				}
			}
			if (InFall) {
				JumpStartY = Initial.y;
				JumpCnt = 16;
				cnt = 16;
				StatusStyle = JumpStatus;
			}

		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player �U�������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Attack() {
	const byte *ptAnime = Anime_data[StatusStyle];
	cnt += 1;
	if (*(ptAnime + cnt) == 0xff) {
		cnt = 0;
		StatusStyle = StationStatus;
	}
	else { cnt -= 1; }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player Animetion�����֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PlayerClass::Animetion() {
	const byte *ptAnime = Anime_data[StatusStyle];
	if (*(ptAnime + cnt) == 0xff) {

		if (StatusStyle == JumpStatus) {
			cnt = 16;
		}
		else {
			cnt = 0;
		}
	}
	Ustart = ((*(ptAnime + cnt)) % (int)(1 / Uwidth))*Uwidth;
	Vstart = ((*(ptAnime + cnt)) / (int)(1 / Vheight))*Vheight;
	cnt += 1;
}
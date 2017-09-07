//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		�����蔻��֐�
//		�j�X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include	"main.h"
#include "DXpolygon.h"
#include "Player.h"
#include "Background.h"
//#include "Hit.h"
#include "Quantitative.h"

//==========================================================================================================
//		�S�Ă�Player�Ɋւ��铖���蔻�菈����`
//==========================================================================================================
void PlayerClass::AllHitTest() {
	extern DisplayClass Display;  //  ���zcamera���
	extern EnemyClass SwordEnemy[64];	// ���G���
	extern byte SwordEnemyNum;	// ���G�����

	const byte *ptAnime = Anime_data[StatusStyle];	// �v�Z�pPlayer Animation Cnt

	//**********************************************************************
	//	�G�ɍU���̓����蔻��
	//**********************************************************************
	if (*(ptAnime + cnt) == 33 || *(ptAnime + cnt) == 34) {
		// 	���G�ɍU���̓����蔻��
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0) {
				if (AttHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 5;
						SwordEnemy[i].HitOn();
					}  // ���G���ԓ��ł͂Ȃ�
				}  // �G�ɓ�����
			}  // �G�������Ă���
		}
	}
	//**********************************************************************
	//	�G��EvilHit�̓����蔻��
	//**********************************************************************
	if (*(ptAnime + cnt) == 50 || *(ptAnime + cnt) == 51) {
		// 	���G�ɍU���̓����蔻��
		for (int i = 0; i < SwordEnemyNum; i++)
		{
			if (SwordEnemy[i].Hp > 0 && SwordEnemy[i].Hp <= SwordEnemy[i].MaxHp*2/5) {
				if (EvilHit(SwordEnemy[i].HitBox_X(), SwordEnemy[i].HitBox_Y(), SwordEnemy[i].HitBox_Wdith, SwordEnemy[i].HitBox_Height)) {
					if (SwordEnemy[i].InvincibleTime == 0) {
						StopTime = 10;
						SwordEnemy[i].EvilOn();
						Hp += SwordEnemy[i].Hp * 4;
						if (Hp > MaxHp) { Hp = MaxHp; }
					}  // ���G���ԓ��ł͂Ȃ�
				}  // �G�ɓ�����
			}  // �G�������Ă���
		}
	}
	//**********************************************************************
	//	�G��damage�󂯂̓����蔻��
	//**********************************************************************
	// 	���G��damage�󂯂̓����蔻��
	for (int i = 0; i < SwordEnemyNum; i++)
	{
		if (SwordEnemy[i].Hp > 0) {
			if (SwordEnemy[i].AnimeCnt() == 5 || SwordEnemy[i].AnimeCnt() == 6) {
				if (HitHit(SwordEnemy[i].AttBox_X(), SwordEnemy[i].AttBox_Y(), SwordEnemy[i].AttBox_Wdith, SwordEnemy[i].AttBox_Height)) {
					if (InvincibleTime == 0) {
						if (StatusStyle != HitStatus) {
							if ((StatusStyle == DefenseStatus) &&( (X < SwordEnemy[i].X && FacedRight) || (X > SwordEnemy[i].X && !FacedRight))) {
								// �h�䂷���
								if (Display.ShockOn == 0) {Display.ShockOn = 1;}
								InvincibleTime = 30;
								Hp -= 1;
							}else {
								// �h�䂵�Ă��Ȃ�
								if (X < SwordEnemy[i].X) {EnemyInPlayerRight = true;}else {
									EnemyInPlayerRight = false;} // �G���ʔ���
								HitOn();
							}
						}
					}  // ���G���ԓ��ł͂Ȃ�
				}  // Player�ɓ�����
			}  // �G�U��Cnt�̎�
		}  // �G�������Ă���
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player�ړ������蔻��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::MoveHit() {
	extern EnemyClass SwordEnemy[64];  // ���G���
	extern byte SwordEnemyNum;	// ���G�����
	
	// 	���G�ɓ����蔻��
	for (int i = 0; i < SwordEnemyNum; i++){
		if (SwordEnemy[i].Hp > 0) {
			if (SwordEnemy[i].PlayerHit()) {
				if (HitBox_X() < SwordEnemy[i].HitBox_X()) { 
					X -= PLAYERSPEED; 
				}else {
					X += PLAYERSPEED;
				}
				return true;
			}
		}  // �G�������Ă���
	}
	if(BoundaryHitTest()){ return true; }
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Map�����蔻��֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::BoundaryHitTest() {
	extern ImaginaryBackground Background;
	if (X - Width / 2 < BleedSize) {
		X += PLAYERSPEED;
		return true;
	}else if (X + Width / 2 > Background.width - BleedSize)	{
		X -= PLAYERSPEED;
		return true;
	}
	return false;

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player��������֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			PlayerClass::FallHitTest(float X1, float Y1, float W, float H)
{
	float XX1 = X - 24 / 2;
	if (FacedRight) {
		XX1 -= 5;
	}
	else {
		XX1 += 5;
	}//�C��
	float	XX2 = X1 - W / 2;
	float YY1 = Y;
	float YY2 = Y1 - H / 2;

	if (((YY1 + 64 >= YY2) && (YY1 - H <= YY2)) && ((XX1 + 24 >= XX2) && (XX1 - W <= XX2)))
	{
		return true;
	}
	else
	{
		return 	false;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Player�K�i����֐���`
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool PlayerClass::HitStair() {
	extern StairClass StairL[64];
	extern byte StairNum;
	float X1;
	float	X2;
	float Y1;
	float Y2;
	for (int i = 0; i < StairNum; i++) {
		X1 = X - Width / 2;
		X2 = StairL[i].X - StairL[i].Width / 2;
		Y1 = Y - Height / 2;
		Y2 = StairL[i].Y - StairL[i].Height / 2;
		if (((Y1 + Height >= Y2) && (Y - StairL[i].Height <= Y2)) && ((X1 + Width >= X2) && (X1 - StairL[i].Width <= StairL[i].X)))
		{
			OnStairNum = i;
			return true;
			break;
		}
	}
	return false;
}


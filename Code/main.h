#ifndef _MAIN_H_
#define	_MAIN_H_

//=========================================
//		Include File
//=========================================
#include <windows.h>
#include <d3dx9.h>			//	�`�揈���ɕK�v
#include <tchar.h>
//=========================================
//		Library��Link
//=========================================
#if 1																				// 	������"0"�ɂ����ꍇ�A�u�\��Property�v�|���uLink�v�|���u���́v�|���u�ǉ��̈ˑ�File�v�ɑΏ�Library��ݒ肷��
#pragma	comment	(lib, "d3d9.lib")		//		�`�揈���ɕK�v
#pragma	comment	(lib, "d3dx9.lib")	//		[d3d9.lib]�̊g��Library
#pragma	comment	(lib, "dxguid.lib")	//		DirectX Component�g�p�ɕK�v
#endif 

//=========================================
//		Macro�̒�`
//=========================================
#define	SCREEN_WIDTH		(1280)		//		Window�̕�
#define	SCREEN_HEIGHT	(720)		//		Window�̍���
//#define	SCREEN_WIDTH		(960)		//		Window�̕�
//#define	SCREEN_HEIGHT	(544)		//		Window�̍���
//#define	SCREEN_WIDTH		(640)		//		Window�̕�
//#define	SCREEN_HEIGHT	(480)		//		Window�̍���
#endif




//struct VERTEX2D{			//�O�p�`
//	float x, y, z;					//���_���W
//	float rhw;						//�������W =�P
//	D3DCOLOR  diffuse;	//�g�U��
//};
//struct VERTEX2DTEX{		//�l�p�`
//	float x, y, z;						//���_���W
//	float rhw;							//�������W =�P
//	D3DCOLOR  diffuse;		//�g�U��
//	float u, v;							//uv���W
//};

//bool DXLoadTexture(char *, LPDIRECT3DTEXTURE9 *);
//void DXDrawPolygon(float, float, float, float, float, DWORD, LPDIRECT3DTEXTURE9);
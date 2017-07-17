//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		DX API Hear File
//		�j�X
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once		//�ړ�Include guard

#include <windows.h>
#include <d3dx9.h>			//	�`�揈���ɕK�v
#include <tchar.h>

bool DXLoadTexture(LPCWSTR filename, LPDIRECT3DTEXTURE9 * tex);
void DXDrawPolygon(float x, float y, float z, float width, float height, DWORD color, LPDIRECT3DTEXTURE9 tex);

void DXDrawAnimePolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex);
void DXDrawPlayerRevPolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex);
void DXDrawAnglePolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex, float angle);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		DX API Hear File
//		ójïX
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once		//à⁄ìÆInclude guard

#include <windows.h>
#include <d3dx9.h>			//	ï`âÊèàóùÇ…ïKóv
#include <tchar.h>

bool DXLoadTexture(LPCWSTR filename, LPDIRECT3DTEXTURE9 * tex);
void DXDrawPolygon(float x, float y, float z, float width, float height, DWORD color, LPDIRECT3DTEXTURE9 tex);

void DXDrawAnimePolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex);
void DXDrawPlayerRevPolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex);
void DXDrawAnglePolygon(float x, float y, float z, float width, float height, float u, float uw, float v, float vh, DWORD color, LPDIRECT3DTEXTURE9 tex, float angle);

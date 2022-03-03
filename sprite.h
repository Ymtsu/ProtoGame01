//=============================================================================
//
// プレイヤー処理 [sprite.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
void DrawSpriteRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, float Rot);
void DrawSpriteVertex(int texNo, D3DXVECTOR2 vertex_left_top, D3DXVECTOR2 vertex_right_top, D3DXVECTOR2 vertex_left_down, D3DXVECTOR2 vertex_right_down,
						float U, float V, float UW, float VH);
void DrawSpriteFreeVertex(int texNo, D3DXVECTOR3 vertex_left_top, D3DXVECTOR3 vertex_right_top, D3DXVECTOR3 vertex_left_down, D3DXVECTOR3 vertex_right_down, float U, float V, float UW, float VH);


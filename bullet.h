//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX		(50)		// バレットのMax数
#define BULLET_SPEED	(4.0f)		// バレットの移動スピード


// バレット構造体
struct BULLET
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標
	float					rot;					// バレットの回転量
	D3DXVECTOR2				move;					// バレットの移動量
	int						texNo;					// 何番目のテクスチャーを使用するのか

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(D3DXVECTOR2 pos);



//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX		(30)			// エネミーのMax人数

// エネミー構造体
struct ENEMY
{
	bool					use;		// true:使っている  false:未使用
	float					w, h;		// 幅と高さ
	D3DXVECTOR2				pos;		// ポリゴンの座標
	float					rot;		// ポリゴンの回転量
	int						texNo;		// 何番目のテクスチャーを使用するのか

	int						HP;			//エネミーHP
	int						kind;		//エネミーの種類

	int						state;		// 状態
	int						frame;		// フレーム

	bool					destroy;	//ブロックがこわれているかどうか
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
void SetEnemy(D3DXVECTOR2 pos, int EnemyKind);
void DelEnemyHP(int EnemyNum);

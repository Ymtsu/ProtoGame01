//=============================================================================
//
// チェンソー処理 [Chainsaw.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHAINSAW_MAX		(2)		// バレットのMax数


// バレット構造体
struct CHAINSAW
{
	bool					use;						// true:使っている  false:未使用
	float					w, h;						// 幅と高さ
	D3DXVECTOR2				pos;						// バレットの座標
	D3DXVECTOR2				CollisionSize;				//あたり判定の大きさ
	D3DXVECTOR2				CollisionPos;				//あたり判定の位置座標
	int						direction;					//チェンソーの向き
	float					rot;						// バレットの回転量
	int						StopCount;					// ヒットストップカウント
	D3DXVECTOR2				Vector;						//プレイヤーまでのベクトル
	float				    Moverot;					//回転加速度
	bool					Preliminary;				//振り上げ準備期間
	int						Charge;						//チャージタイム
	int						OldCharge;					//前処理分の更新処理
	int						Animetion;					//アニメ―ション時間
	int						texNo;						// 何番目のテクスチャーを使用するのか
	int						CollisionTextNo;			// あたり判定テクスチャ―
	int						ChageTextNo;				//チャージテキスチャー
	int						CollisionAnimetionTextNo;	//当たった時のアニメーションテキスチャー
	int					Collisionflg;
	int						SE;
	bool					SEUse;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitChainsaw(void);
void UninitChainsaw(void);
void UpdateChainsaw(void);
void DrawChainsaw(void);

CHAINSAW *GetChainsaw(void);
void SetChainsaw(D3DXVECTOR2 pos);
/*==============================================================================

   頂点管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//プレイヤーの方向構造体
typedef enum  DIRCTION {
	Right,
	Left,
	Up,
	Down
}PLAYER_DIR;

// プレイヤー構造体
struct PLAYER
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	D3DXVECTOR2				oldpos;					// ポリゴンの座標
	float					rot;					// ポリゴンの回転量
	int						texNo;					// テクスチャ番号
	int						dirction;
	bool                    isgrounded;
	bool                    isdashing;
	float                   dashtimer;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
D3DXVECTOR2 GetPlayerPos(void);
int GetPlayerDir(void);
void PlayerMoveReset(void);
int GetMapNumber(void);

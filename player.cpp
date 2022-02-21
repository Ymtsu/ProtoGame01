/*==============================================================================

   頂点管理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER g_Player;
static int g_ShotSENo = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	g_Player.texNo = LoadTexture("data/TEXTURE/majo.png");

	//
	g_ShotSENo = LoadSound("data/SE/shot000.wav");

	//初期化
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = 440;
	g_Player.w = 50.0f;
	g_Player.h = 50.0f;
	g_Player.use = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (GetKeyboardPress(DIK_UP))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y - 1.0f)) != 1)
			g_Player.pos.y -= 1.0f;

		g_CharaUV = 0.75f;
	}

	if (GetKeyboardPress(DIK_DOWN))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + 1.0f)) != 1)
			g_Player.pos.y += 1.0f;

		g_CharaUV = 0.0f;
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y)) != 1)
			g_Player.pos.x -= 1.0f;

		g_CharaUV = 0.25f;
	}

	if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
			g_Player.pos.x += 1.0f;

		g_CharaUV = 0.5f;
	}

	//マップ1へ切り替える
	if (GetKeyboardTrigger(DIK_L))
	{
		SetCurrentMap(1);
	}
	//マップ0へ切り替える
	if (GetKeyboardTrigger(DIK_K))
	{
		SetCurrentMap(0);
	}


	// 弾発射
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		PlaySounds(g_ShotSENo, 0);

		SetVolume(g_ShotSENo, 0.1f);

		D3DXVECTOR2 pos = g_Player.pos;
		SetBullet(pos);		// １発目
		AddScore(123);
	}

	//歩きアニメーション
	if (g_AnimeWaitFrame > 10)
	{
		g_AnimePtn++;
		if (g_AnimePtn > 2)
			g_AnimePtn = 0;

		g_AnimeWaitFrame = 0;
	}
	g_AnimeWaitFrame++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	DrawSprite(g_Player.texNo, g_Player.pos.x, g_Player.pos.y, g_Player.w, g_Player.h, g_AnimePtn * 0.33333f, g_CharaUV, 0.3333f, 0.25f);
}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}



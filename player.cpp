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
#include "collision.h"
#include "Physics.h"
#include "Chainsaw.h"


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

//重力部分
static bool g_GravityUse = false;
static float g_Gravity = 0.0f;
//ジャンプ部分
static bool g_JumpUse = false;

//ステージ移動
static int g_MoveStage = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	g_Player.texNo = LoadTexture("data/TEXTURE/majo.png");

	//SE読み込み
	g_ShotSENo = LoadSound("data/SE/shot000.wav");

	//初期化
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = 370;
	g_Player.oldpos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.w = 100.0f;
	g_Player.h = 100.0f;
	g_Player.use = true;

	//重力初期化
	g_GravityUse = true;
	g_Gravity = Gravity(1.0f);
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
	if (g_Player.pos != g_Player.oldpos)
	{
		g_Player.oldpos = g_Player.pos;
	}
	if (GetKeyboardPress(DIK_W))
	{
		g_JumpUse = true;


		g_CharaUV = 0.75f;
	}

	/*if (GetKeyboardPress(DIK_S))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + 1.0f)) != 1)
			g_Player.pos.y += 1.0f;

		g_CharaUV = 0.0f;
	}*/

	if (GetKeyboardPress(DIK_A))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y)) != 1)
			g_Player.pos.x -= 3.0f;

		g_CharaUV = 0.25f;
	}

	if (GetKeyboardPress(DIK_D))
	{
		if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
			g_Player.pos.x += 3.0f;

		g_CharaUV = 0.5f;
	}

	if (g_JumpUse == true)
	{
		g_Player.pos.y -= 3.0f;
		if (g_Player.pos.y <= 320.0f)
		{
			g_JumpUse = false;
		}

	}

	if (g_GravityUse == true)
	{
		g_Player.pos.y += g_Gravity;
	}
	if (CollisionBB(g_Player.pos, D3DXVECTOR2((SCREEN_WIDTH / 2), 480.0f), D3DXVECTOR2((g_Player.w), (g_Player.h)), D3DXVECTOR2((SCREEN_WIDTH + 160.0f), 160.0f)) == true)
	{
		g_GravityUse = false;
		g_Gravity = 0.0f;
	}
	else
	{
		g_Gravity = Gravity(1.0f);
		g_GravityUse = true;
	}


	//次マップへ切り替える
	if (g_Player.pos.x > SCREEN_WIDTH)
	{
		g_Player.pos.x = 8.0f;
		g_MoveStage += 1;
		if (g_MoveStage > (MAX_MAP_STAGE - 1))
		{
			g_MoveStage = g_MoveStage - 1;
		}
		SetCurrentMap(g_MoveStage);
	}
	//前マップへ切り替える
	if (g_Player.pos.x < 0.0f)
	{
		g_Player.pos.x = (SCREEN_WIDTH - 8.0f);
		g_MoveStage -= 1;
		if (g_MoveStage < 0)
		{
			g_MoveStage = g_MoveStage + 1;
		}
		SetCurrentMap(g_MoveStage);
	}


	// 弾発射
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		PlaySound(g_ShotSENo, 0);

		SetVolume(g_ShotSENo, 0.1f);

		D3DXVECTOR2 pos = g_Player.pos;
		SetBullet(pos);		// １発目
		AddScore(123);
	}

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		PlaySound(g_ShotSENo, 0);

		SetVolume(g_ShotSENo, 0.1f);

		D3DXVECTOR2 pos = g_Player.pos;
		SetChainsaw(pos);		// １発目
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

//=============================================================================
// プレイヤーの位置を取得
//=============================================================================
D3DXVECTOR2 GetPlayerPos(void)
{
	return g_Player.pos;
}
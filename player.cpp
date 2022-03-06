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
#include "Enemy.h"


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

//移動フラグ
static int g_PlayerMoveFlg = 0;
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
	g_Player.pos.y = 350.0f;
	g_Player.oldpos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.vector = D3DXVECTOR2(5.0f, 3.0f);
	g_Player.size = D3DXVECTOR2(100.0f, 100.0f);
	g_Player.use = true;
	g_Player.dirction = Right;
	g_Player.isgrounded = false;
	g_Player.isdashing = false;
	g_Player.dashtimer = 0.0f;

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

	//移動フラグが0の時のみ移動可能
	if (g_PlayerMoveFlg == 0)
	{


		if (GetKeyboardPress(DIK_W) || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && g_Player.isgrounded == true)
		{
			g_JumpUse = true;

			/*g_Player.dirction = Up;*/
			
		}

		////下方向（現在使用予定なし）
		//if (GetKeyboardPress(DIK_S))
		//{
		//	/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + 1.0f)) != 1)
		//		g_Player.pos.y += 1.0f;*/

		//	/*g_Player.dirction = Down;*/
		//	
		//}

		
		int PAD = GetThumbLeftX(0);

		if (GetKeyboardPress(DIK_A) || PAD < 0)
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y)) != 1)
				//g_Player.pos.x -= 5.0f;
			   g_Player.pos.x -= g_Player.vector.x;

			g_Player.dirction = Left;
			
		}
		
		if (GetKeyboardPress(DIK_D) || PAD > 0)
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				//g_Player.pos.x += 5.0f;
			    g_Player.pos.x += g_Player.vector.x;

			g_Player.dirction = Right;
			
		}

		//ダッシュ
		if(GetKeyboardPress(DIK_E) && g_Player.dirction == Right && g_Player.isdashing == false)
		{
			g_Player.isdashing = true;
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x += 195.0f;
		}

		if (GetKeyboardPress(DIK_E) && g_Player.dirction == Left && g_Player.isdashing == false)
		{
			g_Player.isdashing = true;
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x -= 195.0f;
		}

		if (g_Player.isdashing == true)
		{
			g_Player.dashtimer = g_Player.dashtimer  + 1.0f;
		}

		if (g_Player.dashtimer >= 60.0f) //1s間 クールダウン
		{
			g_Player.dashtimer = 0.0f;
			g_Player.isdashing = false;
		}
	}

	switch (g_Player.dirction)
	{
	case Right:
		g_CharaUV = 0.5f;
		break;

	case Left:
		g_CharaUV = 0.25f;
		break;

	case Down:
		g_CharaUV = 0.0f;
		break;

	case Up:
		g_CharaUV = 0.75f;
		break;

	default:
		break;
	}

	//ジャンプフラグ使用時
	if (g_JumpUse == true)
	{
		//g_Player.pos.y -= 9.0f; //jump speed ジャンプ速度
		g_Player.pos.y -= g_Player.vector.y;

		if (g_Player.pos.y <= 220.0f) //max jump height ジャンプの高さ
		{
			g_JumpUse = false;
		}
	}

	//地面判定（現在はCollisionBB使用）
	//if (CollisionBB(g_Player.pos, D3DXVECTOR2((SCREEN_WIDTH / 2), 480.0f), D3DXVECTOR2((g_Player.size.x), (g_Player.size.y)), D3DXVECTOR2((SCREEN_WIDTH + 160.0f), 160.0f)) == true)
	//{
	//	g_JumpUse = false;
	//	g_Player.vector.y = 5.0f;
	//	/*g_GravityUse = false;
	//	g_Gravity = 0.0f;*/
	//}
	//else
	//{
	//	g_Gravity = Gravity(1.0f);
	//	g_GravityUse = true;
	//}

	//temporary groundcheck
	if (g_Player.pos.y >= 370.0f)
	{
		g_Player.isgrounded = true;
		g_GravityUse = false;
		g_Gravity = 0.0f;
	}
	else
	{
		g_Player.isgrounded = false;
		g_Gravity = Gravity(3.0f);
		g_GravityUse = true;
	}

	//重力フラグ使用時
	if (g_GravityUse == true)
	{
		g_Player.vector.y = Gravity(g_Player.vector.y);
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


	ENEMY * pEnemy = GetEnemy();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (pEnemy[i].use == true)
		{
			if (CollisionBB(g_Player.pos,pEnemy[i].pos, D3DXVECTOR2((g_Player.size.x), (g_Player.size.y)), D3DXVECTOR2((pEnemy[i].w), (pEnemy[i].h)))) {
				g_Player.size.x -= 1.0f;
				g_Player.size.y -= 1.0f;
			}
		}
	}
	//// 弾発射
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	PlaySound(g_ShotSENo, 0);

	//	SetVolume(g_ShotSENo, 0.1f);

	//	D3DXVECTOR2 pos = g_Player.pos;
	//	SetBullet(pos);		// １発目
	//	AddScore(123);
	//}

	//チェンソー使用
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		/*PlaySound(g_ShotSENo, 0);*/

		SetVolume(g_ShotSENo, 0.1f);

		D3DXVECTOR2 pos = g_Player.pos;
		SetChainsaw(pos);		// １発目
		g_PlayerMoveFlg = 1;
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
	
	DrawSprite(g_Player.texNo, g_Player.pos.x, g_Player.pos.y, g_Player.size.x, g_Player.size.y, g_AnimePtn * 0.33333f, g_CharaUV, 0.3333f, 0.25f);
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

//=============================================================================
// プレイヤーの方向を取得
//=============================================================================
int GetPlayerDir(void)
{
	return g_Player.dirction;
}

//=============================================================================
// プレイヤーを動けるようにリセットする機能
//=============================================================================
void PlayerMoveReset(void)
{
	g_PlayerMoveFlg = 0;
}

//=============================================================================
// マップナンバーを取得
//=============================================================================
int GetMapNumber(void)
{
	return g_MoveStage;
}

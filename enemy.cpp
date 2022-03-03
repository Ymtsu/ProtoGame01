//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 
//小島
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "Player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void ResetEnemy(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

static ENEMY g_Enemy[ENEMY_MAX];							// エネミー構造体
static int EnemyTexture_01 = 0;
static int EenmyTexture_02 = 0;
static int EnenyTexture_03 = 0;
static int EnemyTexture_04 = 0;
static int g_MapNumber = 0;
static int g_OldMapNumber = -1;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	EnemyTexture_01 = LoadTexture("data/TEXTURE/058865.png");
	EenmyTexture_02 = LoadTexture("data/TEXTURE/いわ.png");
	EnenyTexture_03 = LoadTexture("data/TEXTURE/豆腐.png");
	EnemyTexture_04 = LoadTexture("data/TEXTURE/鉱石.png");

	// エネミー構造体の初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use = false;
		g_Enemy[i].w = 100.0f;
		g_Enemy[i].h = 100.0f;
		g_Enemy[i].pos = D3DXVECTOR2(600.0f, 600.0f);
		g_Enemy[i].rot = 0.0f;
		g_Enemy[i].texNo = EnemyTexture_01;
		g_Enemy[i].state = 0;
		g_Enemy[i].frame = 0;
		g_Enemy[i].kind = 0;
		g_Enemy[i].hard = 0.0f;
		g_Enemy[i].HP = 0;
		g_Enemy[i].destroy = false;
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	g_MapNumber = GetMapNumber();
	if (g_MapNumber != g_OldMapNumber)
	{
		switch (g_MapNumber)
		{
		case 0:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(600.0f, 400.0f), 0);
			break;

		case 1:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 1);
			break;

		case 2:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 2);
			break;

		case 3:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 3);
			break;
		case 4:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 4);
			break;

		case 5:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 5);
			break;

		default:
			break;
		}
		g_OldMapNumber = g_MapNumber;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// このエネミーが使われている？
		{								// Yes	
			if (g_Enemy[i].HP <= 0)
			{
				g_Enemy[i].use = false;
				g_Enemy[i].destroy = true;
			}



			//フレームの追加
			g_Enemy[i].frame++;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)
		{
			//エネミーの位置やテクスチャー座標を反映
			float px = g_Enemy[i].pos.x;	// エネミーの表示位置X
			float py = g_Enemy[i].pos.y;	// エネミーの表示位置Y
			float pw = g_Enemy[i].w;		// エネミーの表示幅
			float ph = g_Enemy[i].h;		// エネミーの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Enemy[i].rot);
		}

		//オブジェクトが壊れたとき
		if (!g_Enemy[i].use && g_Enemy[i].destroy)
		{
			float destroy_pos = (g_Enemy[i].w / 4) + 20.0f;
			//左側
			float px = g_Enemy[i].pos.x - destroy_pos;	// エネミーの表示位置X
			float py = g_Enemy[i].pos.y;	// エネミーの表示位置Y
			float pw = g_Enemy[i].w / 2;		// エネミーの表示幅
			float ph = g_Enemy[i].h;		// エネミーの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 0.5f, 1.0f, col, g_Enemy[i].rot);

			//右側
			px = g_Enemy[i].pos.x + destroy_pos;	// エネミーの表示位置X

			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.5f, 0.0f, 0.5f, 1.0f, col, g_Enemy[i].rot);
		}
	}
}

//=============================================================================
// エネミー構造体の先頭アドレスを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}


//=============================================================================
// 敵の発生処理
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos, int EnemyKind)
{
	// もし未使用のデータを探す
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == false)		// 未使用状態の敵データを見つける
		{
			g_Enemy[i].use = true;			// 使用状態へ変更する
			g_Enemy[i].pos = pos;			// 座標をセット
			g_Enemy[i].rot = 0.0f;			// 回転角のリセット
			g_Enemy[i].state = 0;			// 状態をリセット
			g_Enemy[i].frame = 0;			// フレームのリセット

			switch (EnemyKind)
			{
			case 0:
				g_Enemy[i].HP = 5;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnenyTexture_03;
				g_Enemy[i].hard = 1.0f;
				break;

			case 1:
				g_Enemy[i].HP = 10;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnenyTexture_03;
				g_Enemy[i].hard = 0.8f;
				break;

			case 2:
				g_Enemy[i].HP = 10;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_01;
				g_Enemy[i].hard = 0.6f;
				break;

			case 3:
				g_Enemy[i].HP = 20;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_01;
				g_Enemy[i].hard = 0.4f;
				break;


			case 4:
				g_Enemy[i].HP = 30;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EenmyTexture_02;
				g_Enemy[i].hard = 0.005f;
				break;

			case 5:
				g_Enemy[i].HP = 30;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_04;
				g_Enemy[i].hard = 0.001f;
				break;
			}
			return;							// 敵をセットできたので終了する
		}
	}

}


//=============================================================================
// 敵の消す処理
//=============================================================================
void ResetEnemy(void)
{
	// もし未使用のデータを探す
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// 未使用状態の敵データを見つける
		{
			g_Enemy[i].use = false;			// 使用状態へ変更する


		}
	}
	return;
}

//=============================================================================
// 敵のHPを減らす処理
//=============================================================================
void DelEnemyHP(int EnemyNum)
{
	// もし未使用のデータを探す
	g_Enemy[EnemyNum].HP -= 1;
	return;
}

float GetEnemyHard(int index)
{
	return g_Enemy[index].hard;
}

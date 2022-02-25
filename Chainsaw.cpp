//=============================================================================
//
// チェンソー処理 [Chainsaw.cpp]
// Author : 
//
//=============================================================================
#include "Chainsaw.h"
#include "texture.h"
#include "sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "collision.h"
#include "Hit_stop.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static CHAINSAW g_Chainsaw[CHAINSAW_MAX];							// チェンソー構造体


static D3DXVECTOR2 g_Collisiona_Move = D3DXVECTOR2(0.0f, 0.0f);
static int ChangeHit = 0;
static float Moverot[CHAINSAW_MAX] = { 0.0f };

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitChainsaw(void)
{
	//チェンソーの画像
	int texNo = LoadTexture("data/TEXTURE/CSaw.png");
	//あたり判定の画像
	int ColiTexNo = LoadTexture("data/Texture/collisionDisplay.png");

	//あたり判定可視化の位置移動の初期化
	g_Collisiona_Move.x = 75.0f / 20.0f;
	g_Collisiona_Move.y = 60.0f / 40.0f;

	// チェンソー構造体の初期化
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		g_Chainsaw[i].use = false;
		g_Chainsaw[i].w = 100.0f;
		g_Chainsaw[i].h = 50.0f;
		g_Chainsaw[i].pos = D3DXVECTOR2(100, 50.0f);
		g_Chainsaw[i].CollisionPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Chainsaw[i].CollisionSize = D3DXVECTOR2(100.0f, 50.0f);
		g_Chainsaw[i].rot = 0.0f;
		g_Chainsaw[i].texNo = texNo;
		g_Chainsaw[i].CollisionTextNo = ColiTexNo;
		g_Chainsaw[i].Anime = 0;		
		g_Chainsaw[i].Vector = D3DXVECTOR2(0.0f, 100.0f);
		Moverot[i] = 0.1f;
		
	}

	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitChainsaw(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateChainsaw(void)
{
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == true)	// このチェンソーが使われている？
		{								// Yes
			
			if (g_Chainsaw[i].direction == Right)
			{
				g_Chainsaw[i].rot += Moverot[i];
			}
			
			if (g_Chainsaw[i].direction == Left)
			{
				g_Chainsaw[i].rot -= Moverot[i];
			}
			
			//playerの座標取得
			D3DXVECTOR2 pPlayer_pos = GetPlayerPos();

			g_Chainsaw[i].pos = pPlayer_pos;

			


			float circle_block_vector_length = sqrtf(LENGTH(g_Chainsaw[i].Vector));
			//ボールとブロックを結んだ仮想ベクトル
			g_Chainsaw[i].pos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[i].rot);
			g_Chainsaw[i].pos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[i].rot);


			g_Chainsaw[i].CollisionPos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[i].rot);
			g_Chainsaw[i].CollisionPos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[i].rot);

			

			ENEMY * pEnemy = GetEnemy();

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (pEnemy[i].use == true)
				{
					for (int z = 0; z < CHAINSAW_MAX; z++)
					{
						if (CollisionBB(g_Chainsaw[z].CollisionPos, pEnemy[i].pos, D3DXVECTOR2((g_Chainsaw[z].w), (g_Chainsaw[z].h)), D3DXVECTOR2((pEnemy[i].w), (pEnemy[i].h)))) {
							switch (pEnemy[i].kind)
							{
							case 0:
								Moverot[z] = Hitstop_angle(Moverot[z], g_Chainsaw[z].rot, (g_Chainsaw[z].rot + 1.0f), 0.8f);
								break;

							case 1:
								Moverot[z] = Hitstop_angle(Moverot[z], g_Chainsaw[z].rot, (g_Chainsaw[z].rot + 1.0f), 0.5f);
								break;

							default:
								break;
							}
							
							DelEnemyHP(i);
						}
					}
					
				}
			}

			//チェンソーの画像がある程度回転したらリセットするように設定
			if (g_Chainsaw[i].direction == Right)
			{
				if (g_Chainsaw[i].rot >= 6.5f)
				{
					g_Chainsaw[i].use = false;
					PlayerMoveReset();
					SetFlag();
				}
			}
			
			if (g_Chainsaw[i].direction == Left)
			{
				if (g_Chainsaw[i].rot <= 3.0f)
				{
					g_Chainsaw[i].use = false;
					PlayerMoveReset();
					SetFlag();
				}
			}
			
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawChainsaw(void)
{
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == true)	// このチェンソーが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Chainsaw[i].pos.x;	// バレットの表示位置X
			float py = g_Chainsaw[i].pos.y;	// バレットの表示位置Y
			float pw = g_Chainsaw[i].w;		// バレットの表示幅
			float ph = g_Chainsaw[i].h;		// バレットの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			

			//あたり判定テクスチャー（後で消すかも）
			DrawSpriteColorRotate(g_Chainsaw[i].CollisionTextNo, g_Chainsaw[i].CollisionPos.x, g_Chainsaw[i].CollisionPos.y, g_Chainsaw[i].CollisionSize.x, g_Chainsaw[i].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Chainsaw[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);
		}
	}

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
CHAINSAW *GetChainsaw(void)
{
	return &g_Chainsaw[0];
}


//=============================================================================
// バレットの発射設定
//=============================================================================
void SetChainsaw(D3DXVECTOR2 pos)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == false)							// 未使用状態のバレットを見つける
		{
			g_Chainsaw[i].use = true;							// 使用状態へ変更する
			g_Chainsaw[i].pos = pos;							// 座標をセット
			g_Chainsaw[i].direction = GetPlayerDir();			//どっち方向に使用するのかを設定する
			if (g_Chainsaw[i].direction == Right)
			{
				g_Chainsaw[i].rot = 3.75f;							//回転位置を上になるように設定
			}
			if (g_Chainsaw[i].direction == Left)
			{
				g_Chainsaw[i].rot = 5.00f;							//回転位置を上になるように設定
			}
			g_Chainsaw[i].Vector = D3DXVECTOR2(0.0f, 100.0f);
			Moverot[i] = 0.1f; 
			return;												// 1発セットしたので終了する
		}
	}
}
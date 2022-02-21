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
static bool Move_x[CHAINSAW_MAX];
static bool Move_y[CHAINSAW_MAX];

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
	g_Collisiona_Move.x = 75.0f / 10.0f;
	g_Collisiona_Move.y = 60.0f / 20.0f;

	// チェンソー構造体の初期化
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		g_Chainsaw[i].use = false;
		g_Chainsaw[i].w = 100.0f;
		g_Chainsaw[i].h = 100.0f;
		g_Chainsaw[i].pos = D3DXVECTOR2(300, 300.0f);
		g_Chainsaw[i].CollisionPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Chainsaw[i].CollisionSize = D3DXVECTOR2(30.0f, 50.0f);
		g_Chainsaw[i].rot = 0.0f;
		g_Chainsaw[i].texNo = texNo;
		g_Chainsaw[i].CollisionTextNo = ColiTexNo;
		g_Chainsaw[i].Anime = 0;
		Move_x[i] = false;
		Move_y[i] = false;
		
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
			g_Chainsaw[i].Anime += 1;
			g_Chainsaw[i].rot += 0.1f;
			
			D3DXVECTOR2 pPlayer_pos = GetPlayerPos();

			g_Chainsaw[i].pos = pPlayer_pos;

			
			switch(g_Chainsaw[i].Anime)
			{
			case 1:
 				Move_x[i] = true;
				g_Chainsaw[i].CollisionPos = D3DXVECTOR2((pPlayer_pos.x + g_Collisiona_Move.x *g_Chainsaw[i].Anime), (pPlayer_pos.y - 30.0f));
				break;

			case 10:
				Move_x[i] = false;
				Move_y[i] = true;
				g_Chainsaw[i].CollisionPos = D3DXVECTOR2((pPlayer_pos.x + 50.0f + 25.0f), (pPlayer_pos.y - 30.0f + g_Collisiona_Move.y * (g_Chainsaw[i].Anime - 10)));
				g_Chainsaw[i].CollisionSize = D3DXVECTOR2(50.0f, 50.0f);
				break;

			case 30:
				Move_x[i] = false;
				Move_y[i] = false;
				g_Chainsaw[i].CollisionPos = D3DXVECTOR2((pPlayer_pos.x + 50.0f + 25.0f), (pPlayer_pos.y ));
				break;
			

			default:
				break;


			}

			if (Move_x[i] == true) {
				g_Chainsaw[i].CollisionPos = D3DXVECTOR2((pPlayer_pos.x + g_Collisiona_Move.x *(g_Chainsaw[i].Anime - 1)), (pPlayer_pos.y - 30.0f));
			}
			
			if (Move_y[i] == true) {
				g_Chainsaw[i].CollisionPos = D3DXVECTOR2((pPlayer_pos.x + 50.0f + 25.0f), (pPlayer_pos.y - 30.0f + g_Collisiona_Move.y * (g_Chainsaw[i].Anime - 10)));
			}

			if (g_Chainsaw[i].rot >= 10.0f)
			{
				g_Chainsaw[i].rot = 0.0f;
			}
			
			// 画面外まで進んだ？
			if (g_Chainsaw[i].Anime == 30)	// 自分の大きさを考慮して画面外か判定している
			{
				g_Chainsaw[i].use = false;
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

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Chainsaw[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);

			//あたり判定テクスチャー（後で消すかも）
			DrawSprite(g_Chainsaw[i].CollisionTextNo, g_Chainsaw[i].CollisionPos.x, g_Chainsaw[i].CollisionPos.y, g_Chainsaw[i].CollisionSize.x, g_Chainsaw[i].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f);
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
		if (g_Chainsaw[i].use == false)		// 未使用状態のバレットを見つける
		{
			g_Chainsaw[i].use = true;			// 使用状態へ変更する
			g_Chainsaw[i].pos = pos;			// 座標をセット
			g_Chainsaw[i].Anime = 0;
			g_Chainsaw[i].rot = 1.25f;
			return;							// 1発セットしたので終了する
		}
	}
}
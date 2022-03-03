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
#include "input.h"
#include "sound.h"

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
static float g_hard = 0.0f;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitChainsaw(void)
{
	//チェンソーの画像
	int texNo = LoadTexture("data/TEXTURE/CSaw.png");
	//あたり判定の画像
	int ColiTexNo = LoadTexture("data/Texture/collisionDisplay.png");
	//あたり判定のアニメーション
	int effectNo = LoadTexture("data/ANIMATION/チェーンソーエフェクト.png");
	////チャージのアニメーション
	//int chageNo = LoadTexture("data/ANIMATION/チェーンソーエフェクト.png");

	int SENo = LoadSound("data/SE/ーで木を切る2.wav");

	//あたり判定可視化の位置移動の初期化
	g_Collisiona_Move.x = 75.0f / 20.0f;
	g_Collisiona_Move.y = 60.0f / 40.0f;

	// チェンソー構造体の初期化
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		g_Chainsaw[ChainsawNum].use = false;
		g_Chainsaw[ChainsawNum].w = 100.0f;
		g_Chainsaw[ChainsawNum].h = 50.0f;
		g_Chainsaw[ChainsawNum].pos = D3DXVECTOR2(100, 50.0f);
		g_Chainsaw[ChainsawNum].CollisionPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Chainsaw[ChainsawNum].CollisionSize = D3DXVECTOR2(100.0f, 50.0f);
		g_Chainsaw[ChainsawNum].rot = 0.0f;
		g_Chainsaw[ChainsawNum].texNo = texNo;
		g_Chainsaw[ChainsawNum].CollisionTextNo = ColiTexNo;
		g_Chainsaw[ChainsawNum].StopCount = 0;		
		g_Chainsaw[ChainsawNum].Vector = D3DXVECTOR2(0.0f, 100.0f);
		g_Chainsaw[ChainsawNum].Moverot = 0.1f;
		g_Chainsaw[ChainsawNum].Preliminary = false;
		g_Chainsaw[ChainsawNum].Charge = 0;
		g_Chainsaw[ChainsawNum].OldCharge = 0;
		g_Chainsaw[ChainsawNum].CollisionAnimetionTextNo = effectNo;
		g_Chainsaw[ChainsawNum].Collisionflg = 0;
		g_Chainsaw[ChainsawNum].SE = SENo;
		g_Chainsaw[ChainsawNum].SEUse = false;
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == true)	// このチェンソーが使われている？
		{								// Yes
			
			if (g_Chainsaw[ChainsawNum].SEUse == true)
			{
				PlaySounds(g_Chainsaw[ChainsawNum].SE, -1);
				g_Chainsaw[ChainsawNum].SEUse = false;
			}
			//OldChage更新
			g_Chainsaw[ChainsawNum].OldCharge = g_Chainsaw[ChainsawNum].Charge;

			//Charge更新
			if (GetKeyboardPress(DIK_SPACE)||IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
			{
				g_Chainsaw[ChainsawNum].Charge += 1;
			}

			//チェンソー右向きの更新処理
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				//チェンソー振り上げ期間
				if (g_Chainsaw[ChainsawNum].Preliminary == true)
				{
					g_Chainsaw[ChainsawNum].Moverot += 0.002f;
					g_Chainsaw[ChainsawNum].rot -= g_Chainsaw[ChainsawNum].Moverot;
					if (g_Chainsaw[ChainsawNum].rot <= 4.0)
					{
						g_Chainsaw[ChainsawNum].Preliminary = false;
						g_Chainsaw[ChainsawNum].Moverot = 0.0f;
					}
				}
				else
				{
					//チャージによって変化
					if (g_Chainsaw[ChainsawNum].Charge == g_Chainsaw[ChainsawNum].OldCharge)
					{
						//最小チャージ時
						if (g_Chainsaw[ChainsawNum].Charge <= 20)
						{
							g_Chainsaw[ChainsawNum].StopCount += 1;
						}
						if (g_Chainsaw[ChainsawNum].StopCount >= 15)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.005f;							
						}

						//中間チャージ時
						if (g_Chainsaw[ChainsawNum].Charge <= 40 && g_Chainsaw[ChainsawNum].Charge > 20)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.008f;
						}

						//最終チャージ時
						if (g_Chainsaw[ChainsawNum].Charge > 40)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.012f;
						}
						g_Chainsaw[ChainsawNum].rot += g_Chainsaw[ChainsawNum].Moverot;
					}
				}
				

			}

			//チェンソー左向きの更新処理
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{

				//チェンソー振り上げ期間
				if (g_Chainsaw[ChainsawNum].Preliminary == true)
				{
					g_Chainsaw[ChainsawNum].Moverot += 0.002f;
					g_Chainsaw[ChainsawNum].rot += g_Chainsaw[ChainsawNum].Moverot;
					if (g_Chainsaw[ChainsawNum].rot >= 5.5)
					{
						g_Chainsaw[ChainsawNum].Preliminary = false;
						g_Chainsaw[ChainsawNum].Moverot = 0.0f;
					}
				}
				else
				{
					//チャージによって変化
					if (g_Chainsaw[ChainsawNum].Charge == g_Chainsaw[ChainsawNum].OldCharge)
					{
						//最小チャージ時
						if (g_Chainsaw[ChainsawNum].Charge <= 20)
						{
							g_Chainsaw[ChainsawNum].StopCount += 1;
						}
						if (g_Chainsaw[ChainsawNum].StopCount >= 15)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.005f;
						}

						//中間チャージ時
						if (g_Chainsaw[ChainsawNum].Charge <= 40 && g_Chainsaw[ChainsawNum].Charge > 20)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.008f;
						}

						//最終チャージ時
						if (g_Chainsaw[ChainsawNum].Charge > 40)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.012f;
						}
						g_Chainsaw[ChainsawNum].rot -= g_Chainsaw[ChainsawNum].Moverot;
					}

				}
			}
			
			//playerの座標取得
			D3DXVECTOR2 pPlayer_pos = GetPlayerPos();

			g_Chainsaw[ChainsawNum].pos = pPlayer_pos;

			


			float circle_block_vector_length = sqrtf(LENGTH(g_Chainsaw[ChainsawNum].Vector));
			//ボールとブロックを結んだ仮想ベクトル
			g_Chainsaw[ChainsawNum].pos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[ChainsawNum].rot);
			g_Chainsaw[ChainsawNum].pos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[ChainsawNum].rot);


			g_Chainsaw[ChainsawNum].CollisionPos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[ChainsawNum].rot);
			g_Chainsaw[ChainsawNum].CollisionPos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[ChainsawNum].rot);

			

			ENEMY * pEnemy = GetEnemy();

			for (int enemy = 0; enemy < ENEMY_MAX; enemy++)
			{
				if (pEnemy[enemy].use == true)
				{
					if (g_Chainsaw[ChainsawNum].Preliminary == false)
					{
						if (CollisionBB(g_Chainsaw[ChainsawNum].CollisionPos, pEnemy[enemy].pos, D3DXVECTOR2((g_Chainsaw[ChainsawNum].w), (g_Chainsaw[ChainsawNum].h)), D3DXVECTOR2((pEnemy[enemy].w), (pEnemy[enemy].h)))) {
							switch (pEnemy[enemy].kind)
							{
							case 0:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;
								break;

							case 1:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 2:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 3:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 4:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 5:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;
							
							default:
								break;
							}

							DelEnemyHP(ChainsawNum);
						}
						else
						{
							if (g_Chainsaw[ChainsawNum].Collisionflg == 1)
							{
								g_Chainsaw[ChainsawNum].Collisionflg = 2;
							}
							
						}
					}
				}
			}


			if (g_Chainsaw[ChainsawNum].Collisionflg == 2)
			{
				HitstopEndAcceleration(g_Chainsaw[ChainsawNum].rot, g_hard);
			}
			//チェンソーの画像がある程度回転したらリセットするように設定（右回転）
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				if (g_Chainsaw[ChainsawNum].rot >= 7.0f)
				{
					g_Chainsaw[ChainsawNum].use = false;
					PlayerMoveReset();
					SetFlag();
					g_Chainsaw[ChainsawNum].StopCount = 0;
					StopSound(g_Chainsaw[ChainsawNum].SE);
				}
			}

			//チェンソーの画像がある程度回転したらリセットするように設定（左回転）
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{
				if (g_Chainsaw[ChainsawNum].rot <= 2.0f)
				{
					g_Chainsaw[ChainsawNum].use = false;
					PlayerMoveReset();
					SetFlag();
					StopSound(g_Chainsaw[ChainsawNum].SE);
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == true)	// このチェンソーが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Chainsaw[ChainsawNum].pos.x;	// バレットの表示位置X
			float py = g_Chainsaw[ChainsawNum].pos.y;	// バレットの表示位置Y
			float pw = g_Chainsaw[ChainsawNum].w;		// バレットの表示幅
			float ph = g_Chainsaw[ChainsawNum].h;		// バレットの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			

			//あたり判定テクスチャー（後で消すかも）
			DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].CollisionTextNo, g_Chainsaw[ChainsawNum].CollisionPos.x, g_Chainsaw[ChainsawNum].CollisionPos.y, g_Chainsaw[ChainsawNum].CollisionSize.x, g_Chainsaw[ChainsawNum].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);

			

			if (g_Chainsaw[ChainsawNum].Charge <= 40)
			{
				D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);
			}

			else if (g_Chainsaw[ChainsawNum].Charge <= 60)
			{
				D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);
			}


			if (g_Chainsaw[ChainsawNum].Collisionflg == 1)
			{
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				int	Animetion = (g_Chainsaw[ChainsawNum].Animetion / 2);
				float TextU =  (1.0f/ 6.0f) * (Animetion % 6);
				float TextV = (1.0f /5.0f) * (Animetion / 6);

				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].CollisionAnimetionTextNo, px, py, 500.0f, 500.0f, TextU, TextV, (1.0f/6.0f), (1.0f/5.0f), col, g_Chainsaw[ChainsawNum].rot);
			}

			
			// １枚のポリゴンの頂点とテクスチャ座標を設定
			
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == false)							// 未使用状態のバレットを見つける
		{
			g_Chainsaw[ChainsawNum].use = true;							// 使用状態へ変更する
			g_Chainsaw[ChainsawNum].pos = pos;							// 座標をセット
			g_Chainsaw[ChainsawNum].direction = GetPlayerDir();			//どっち方向に使用するのかを設定する
			g_Chainsaw[ChainsawNum].Preliminary = true;
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				g_Chainsaw[ChainsawNum].rot = 5.5f;							//回転位置を上になるように設定
			}
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{
				g_Chainsaw[ChainsawNum].rot = 4.0f;							//回転位置を上になるように設定
			}
			g_Chainsaw[ChainsawNum].Vector = D3DXVECTOR2(0.0f, 100.0f);
			g_Chainsaw[ChainsawNum].Moverot = 0.0f;
			g_Chainsaw[ChainsawNum].Charge = 0;
			g_Chainsaw[ChainsawNum].OldCharge = 0;
			g_Chainsaw[ChainsawNum].StopCount = 0;
			g_Chainsaw[ChainsawNum].Animetion = 0;
			g_Chainsaw[ChainsawNum].SEUse = true;
			return;												// 1発セットしたので終了する
		}
	}
}
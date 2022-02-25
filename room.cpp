//=============================================================================
//
// エネミー処理 [room.cpp]
// Author : 
//
//=============================================================================

#include "room.h"
#include "collision.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "input.h"
#include "enemy.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER* pPlayer = GetPlayer();
ENEMY* pEnemy = GetEnemy();

static int room_time;					//ルームの広がる時間
static int room_texNo;					// テクスチャ番号
static int room_area;					//ルームの範囲
static bool room_use;					//ルームが広がる時間のフラグ
static bool old_use;					//１フレーム前のフラグ
static D3DXVECTOR2 room_pos;			//ルームのポジション
static D3DXVECTOR2 room_size_vector;	//
static D3DXVECTOR2 room_size;			//ルームの大きさ
static int chambres;
static float chambres_length;

//=============================================================================
// 初期化処理
//=============================================================================
void InitRoom(void)
{
	room_time = 0;
	room_texNo = LoadTexture("data/TEXTURE/room.png");
	room_use = false;
	old_use = room_use;
	room_size_vector = D3DXVECTOR2(8.0f, 8.0f);
	static int chambres = 0;
	chambres_length = 0.0f;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRoom(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRoom(void)
{
	PLAYER* GetPlayer();
	old_use = room_use;
	chambres_length = 0.0f;

	//Rを押したらルームを起動
	if (GetKeyboardPress(DIK_R))
	{
		room_use = true;
	}

	if (room_use == true)
	{
		room_time += 1;
		if (old_use == false) 
		{
			room_pos.x = pPlayer->pos.x - (pPlayer->h/ 2);
			room_pos.y = pPlayer->pos.y - (pPlayer->h / 2);
		}
	}
	if (room_use == true)
	{
		if (room_time < 30)
		{
			room_pos = room_pos - room_size_vector;
			room_size.x = fabsf((room_pos.x - pPlayer->pos.x)) * 2;
			room_size.y = fabsf((room_pos.y - pPlayer->pos.y));
		}
	}

	if (room_time > 30)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (CollisionBB_LEFT_TOP(room_pos, pEnemy[i].pos, room_size, D3DXVECTOR2(pEnemy[i].w, pEnemy[i].h)))
			{
				if (powf(room_size.x, 2.0f) > LENGTH(D3DXVECTOR2(room_pos.x + (room_size.x / 2), room_pos.y + room_size.y) - pEnemy[i].pos))
				{
					if (chambres_length < LENGTH(D3DXVECTOR2(room_pos.x + (room_size.x / 2), room_pos.y + room_size.y) - pEnemy[i].pos))
					{
						chambres_length = LENGTH(D3DXVECTOR2(room_pos.x + (room_size.x / 2), room_pos.y + room_size.y) - pEnemy[i].pos);
						chambres = i;
					}
				}
			}
		}

		if (chambres_length != 0.0f && GetKeyboardPress(DIK_C))
		{
			D3DXVECTOR2 i = pPlayer->pos;
			pPlayer->pos = pEnemy[chambres].pos;
			pEnemy[chambres].pos = i;
			room_use = false;
			room_time = 0;
		}

	}

	//起動が終わってからX秒後に消える
	if (room_time > 210)
	{
		room_use = false;
		room_time = 0;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRoom(void)
{
	if (room_use == true)
	{
		DrawSpriteLeftTopColor(room_texNo, room_pos.x, room_pos.y + (pPlayer->h / 2), room_size.x, room_size.y, 0.0f, 0.0f, 1.0f, 0.5f,D3DXCOLOR(1.0f,1.0f,1.0f,0.3f));
	}
}


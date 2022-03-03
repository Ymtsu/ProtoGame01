//=============================================================================
//
// 樹木処理 [wood.cpp]
// Author : 
//こば、トミー
//=============================================================================
#include "wood.h"
#include "Chainsaw.h"
#include "player.h"

static CHAINSAW* p_Chainsaw = GetChainsaw();
static PLAYER* p_Player = GetPlayer();

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Wood::Init()
{
	Wood::m_texture = LoadTexture("data/TEXTURE/058865.png");
	Wood::m_pos = D3DXVECTOR2(600.0f, 600.0f);
	Wood::m_size = D3DXVECTOR2(100.0f, 600.0f);
	Wood::m_hp = 3;

	//切り株
	Wood::m_stump_texture = LoadTexture("data/TEXTURE/058865.png");
	Wood::m_stump_pos = D3DXVECTOR2(Wood::m_pos.x/2, Wood::m_pos.y / 2);
	Wood::m_stump_size = D3DXVECTOR2(100.0f, 600.0f);
	Wood::m_state = WoodState::stand;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Wood::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Wood::Update()
{

	if (Wood::m_use)
	{
		//チェーンソーとの判定
		switch ((CollisionBB_SURFACE(p_Chainsaw->pos, Wood::m_pos, p_Chainsaw->pos, Wood::m_pos, D3DXVECTOR2(p_Chainsaw->w, p_Chainsaw->h), Wood::m_size)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			
			break;
		case SURFACE::right:
			
			break;
		}
		//プレイヤーとの判定
		switch ((CollisionBB_SURFACE(p_Player->pos, Wood::m_pos, p_Player->old_pos, Wood::m_pos, D3DXVECTOR2(p_Player->w, p_Player->h), Wood::m_size)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			if (Wood::m_hp <= 0)
			{
			}
			break;
		case SURFACE::right:
			if (Wood::m_hp <= 0)
			{
			}
			break;
		}
	}


	switch (Wood::m_state)
	{
	case WoodState::no_exit:
		break;
	case WoodState::stand:
		//チェーンソーとの判定
		switch ((CollisionBB_SURFACE(p_Chainsaw->pos, Wood::m_pos, p_Chainsaw->pos, Wood::m_pos, D3DXVECTOR2(p_Chainsaw->w, p_Chainsaw->h), Wood::m_size)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			if (Wood::m_hp <= 0)
			{
				Wood::m_surface = SURFACE::left;
				Wood::m_state = WoodState::rotation;
			}
			break;
		case SURFACE::right:
			if (Wood::m_hp <= 0)
			{
				Wood::m_surface = SURFACE::right;
				Wood::m_state = WoodState::rotation;
			}
			break;
		}
		//プレイヤーとの判定
		switch ((CollisionBB_SURFACE(p_Player->pos, Wood::m_pos, p_Player->old_pos, Wood::m_pos, D3DXVECTOR2(p_Player->w, p_Player->h), Wood::m_size)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			p_Player->pos.x = Wood::m_pos.x - (Wood::m_size.x + p_Player->w) / 2;
			break;
		case SURFACE::right:
			p_Player->pos.x = Wood::m_pos.x + (Wood::m_size.x + p_Player->w) / 2;
			break;
		}
		break;
	case WoodState::rotation:
		//ブロックの頂点座標を代入
		static D3DXVECTOR2* p_block_vertex = SquareVertexPos(Wood::m_pos, Wood::m_size, Wood::m_rot);
		
		if (Wood::m_rot > PI / 2)
		{
			Wood::m_state = WoodState::fallen;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			Wood::m_vertex[i] = p_block_vertex[i];
		}

		break;

	case WoodState::fallen:

		//プレイヤーとの判定
		switch (CollisionBB_SURFACE(p_Player->pos, Wood::m_pos, p_Player->old_pos, Wood::m_pos,
			D3DXVECTOR2(p_Player->w, p_Player->h), D3DXVECTOR2(Wood::m_size.y, Wood::m_size.x)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			p_Player->pos.x = Wood::m_pos.x - (Wood::m_size.y + p_Player->w) / 2;
			break;
		case SURFACE::right:
			p_Player->pos.x = Wood::m_pos.x + (Wood::m_size.y + p_Player->w) / 2;
			break;
		case SURFACE::up:
			p_Player->pos.y = Wood::m_pos.y + (Wood::m_size.x + p_Player->h) / 2;
			break;
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Wood::Draw() 
{
	if (Wood::m_use)
	{
		DrawSprite(Wood::m_texture,Wood::m_pos.x, Wood::m_pos.y,Wood::m_size.x,Wood::m_size.y, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	/* if (Wood::m_destroy)
	{
		DrawSpriteRotate(Wood::m_texture, Wood::m_pos.x, Wood::m_pos.y, Wood::m_size.x, Wood::m_size.y,
			0.0f, 0.0f, 1.0f, 1.0f, Wood::m_rot);
	}*/
}


//=============================================================================
// 回す角度
//=============================================================================
//左から切られたとき
float CutLeftRot(float rot)
{
	float T = (PI / 2) / (90.0f / 0.8f);
	rot -= T;

	return rot;
}
//右から切られたとき
float CutRightRot(float rot)
{
	float T = (PI / 2) / (90.0f / 0.8f);
	rot += T;

	return rot;
}

//=============================================================================
// 切った樹木を動かす
//=============================================================================
//左から切られて右に倒れるとき
D3DXVECTOR2 WoodRightMove(D3DXVECTOR2 wood_move_pos,D3DXVECTOR2 stump_pos,D3DXVECTOR2 stump_size, float rot)
{
	//切り株の右上の座標(回転の軸となる点)
	D3DXVECTOR2 centerpoint = D3DXVECTOR2(stump_pos.x + stump_size.x / 2, stump_pos.y - stump_size.y / 2);

	//軸と動く点の長さ
	float move_length = sqrtf(LENGTH(centerpoint - wood_move_pos));

	wood_move_pos.x += move_length * cosf(rot);
	wood_move_pos.y -= move_length * sinf(rot);

	return wood_move_pos;
}
//右から切られて左に倒れるとき
D3DXVECTOR2 WoodLeftMove(D3DXVECTOR2 wood_move_pos, D3DXVECTOR2 stump_pos, D3DXVECTOR2 stump_size, float rot)
{
	//切り株の左上の座標(回転の軸となる点)
	D3DXVECTOR2 centerpoint = D3DXVECTOR2(stump_pos.x - stump_size.x / 2, stump_pos.y - stump_size.y / 2);

	//軸と動く点の長さ
	float move_length = sqrtf(LENGTH(centerpoint - wood_move_pos));

	wood_move_pos.x -= move_length * cosf(rot);
	wood_move_pos.y -= move_length * sinf(rot);

	return wood_move_pos;
}

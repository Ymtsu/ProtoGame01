//=============================================================================
//
// 樹木処理 [wood.cpp]
// Author : 
//こば、トミー
//=============================================================================
#include "wood.h"
#include "collision.h"
#include "Chainsaw.h"

CHAINSAW* p_Chainsaw = GetChainsaw();

HRESULT Wood::Init()
{
	Wood::m_texture = LoadTexture("data/TEXTURE/058865.png");
	Wood::m_pos = D3DXVECTOR2(600.0f, 600.0f);
	Wood::m_size = D3DXVECTOR2(100.0f, 600.0f);
	Wood::m_hp = 3;
	

	return S_OK;
}

void Wood::Uninit()
{

}

void Wood::Update()
{
	if (Wood::m_use)
	{
		switch ((CollisionBB_SURFACE(p_Chainsaw->pos, Wood::m_pos, p_Chainsaw->pos, Wood::m_pos, D3DXVECTOR2(p_Chainsaw->w, p_Chainsaw->h), Wood::m_size)))
		{
		case SQUARE_SURFACE::min_error:
			break;
		case SQUARE_SURFACE::left:
			Wood::m_use = false;

			break;
		case SQUARE_SURFACE::right:
			break;
		}
	}
	
}

void Wood::Draw() 
{
	if (Wood::m_use == true)
	{
		DrawSprite(Wood::m_texture,Wood::m_pos.x, Wood::m_pos.y,Wood::m_size.x,Wood::m_size.y, 0.0f, 0.0f, 1.0f, 1.0f);
	}
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

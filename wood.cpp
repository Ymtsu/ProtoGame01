//=============================================================================
//
// 樹木処理 [wood.cpp]
// Author : 
//こば、トミー
//=============================================================================
#include "wood.h"


HRESULT Wood::Init()
{
	Wood::m_texture = LoadTexture("data/TEXTURE/058865.png");

	return S_OK;
}

void Wood::Uninit()
{

}

void Wood::Update()
{

}

void Wood::Draw() 
{
	if (Wood::m_use == true)
	{
		DrawSprite(Wood::m_texture,Wood::m_pos.x, Wood::m_pos.y,Wood::m_size.x,Wood::m_size.y, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}
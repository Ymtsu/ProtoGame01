//=============================================================================
//
// 樹木処理 [wood.cpp]
// Author : 
//こば、トミー
//=============================================================================
#include "wood.h"
#include "texture.h"
#include "sprite.h"



HRESULT Wood::Init()
{

}

void Wood::Uninit()
{

}

void Wood::Update()
{

}

void Wood::Draw()
{
	if (Wood::use == true)
	{
		DrawSprite(Wood::texture,Wood::pos.x, Wood::pos.y,Wood::size.x,Wood::size.y, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}
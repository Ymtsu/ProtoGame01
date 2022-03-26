//=============================================================================
// ’n–Êˆ— [wood.cpp]
// Author : 
//‚±‚Î
//=============================================================================
#include "ground.h"
#include "Chainsaw.h"
#include "player.h"

static CHAINSAW* p_Chainsaw = GetChainsaw();
static PLAYER* p_Player = GetPlayer();

HRESULT Ground::Init(void)
{
    Ground::m_texture = LoadTexture("data/TEXTURE/ground.png");
    Ground::m_size = D3DXVECTOR2(60.0f, 60.0f);
    return E_NOTIMPL;
}

void Ground::Uninit(void)
{
}

void Ground::Update(void)
{
    if (Ground::m_use)
    {
        switch (CollisionBB_SURFACE(p_Player->pos,Ground::m_pos,p_Player->old_pos,Ground::m_pos,
            D3DXVECTOR2(p_Player->w,p_Player->h),Ground::m_size))
        {
        case SURFACE::no_hit:
            break;

        case SURFACE::left:
            p_Player->pos.x = Ground::m_pos.x - (p_Player->w + Ground::m_size.x) / 2;
            break;

        case SURFACE::right:
            p_Player->pos.x = Ground::m_pos.x + (p_Player->w + Ground::m_size.x) / 2;
            break;

        case SURFACE::up:
            p_Player->pos.y = Ground::m_pos.y - (p_Player->h + Ground::m_size.y) / 2;
            break;

        case SURFACE::down:
            p_Player->pos.y = Ground::m_pos.y + (p_Player->h + Ground::m_size.y) / 2;
            break;

        }
    }
}

void Ground::Draw(void)
{
    if(Ground::m_use)
    DrawSprite(Ground::m_texture, Ground::m_pos.x,Ground::m_pos.y, Ground::m_size.x,Ground::m_size.y, 0.0f, 0.0f, 0.0f, 0.0f);
}

//void Ground::SetPos(D3DXVECTOR2 pos,int use)
//{
//
//}

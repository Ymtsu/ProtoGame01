//=============================================================================
//
// ���؏��� [wood.cpp]
// Author : 
//���΁A�g�~�[
//=============================================================================
#include "wood.h"
#include "Chainsaw.h"
#include "player.h"

static CHAINSAW* p_Chainsaw = GetChainsaw();
static PLAYER* p_Player = GetPlayer();

//=============================================================================
// ����������
//=============================================================================
HRESULT Wood::Init()
{
	Wood::m_texture = LoadTexture("data/TEXTURE/058865.png");
	Wood::m_pos = D3DXVECTOR2(600.0f, 600.0f);
	Wood::m_size = D3DXVECTOR2(100.0f, 600.0f);
	Wood::m_hp = 3;

	//�؂芔
	Wood::m_stump_texture = LoadTexture("data/TEXTURE/058865.png");
	Wood::m_stump_pos = D3DXVECTOR2(Wood::m_pos.x/2, Wood::m_pos.y / 2);
	Wood::m_stump_size = D3DXVECTOR2(100.0f, 600.0f);
	Wood::m_state = WoodState::stand;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Wood::Uninit()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Wood::Update()
{

	if (Wood::m_use)
	{
		//�`�F�[���\�[�Ƃ̔���
		switch ((CollisionBB_SURFACE(p_Chainsaw->pos, Wood::m_pos, p_Chainsaw->pos, Wood::m_pos, D3DXVECTOR2(p_Chainsaw->w, p_Chainsaw->h), Wood::m_size)))
		{
		case SURFACE::min_error:
			break;
		case SURFACE::left:
			
			break;
		case SURFACE::right:
			
			break;
		}
		//�v���C���[�Ƃ̔���
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
		//�`�F�[���\�[�Ƃ̔���
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
		//�v���C���[�Ƃ̔���
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
		//�u���b�N�̒��_���W����
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

		//�v���C���[�Ƃ̔���
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
// �`�揈��
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
// �񂷊p�x
//=============================================================================
//������؂�ꂽ�Ƃ�
float CutLeftRot(float rot)
{
	float T = (PI / 2) / (90.0f / 0.8f);
	rot -= T;

	return rot;
}
//�E����؂�ꂽ�Ƃ�
float CutRightRot(float rot)
{
	float T = (PI / 2) / (90.0f / 0.8f);
	rot += T;

	return rot;
}

//=============================================================================
// �؂������؂𓮂���
//=============================================================================
//������؂��ĉE�ɓ|���Ƃ�
D3DXVECTOR2 WoodRightMove(D3DXVECTOR2 wood_move_pos,D3DXVECTOR2 stump_pos,D3DXVECTOR2 stump_size, float rot)
{
	//�؂芔�̉E��̍��W(��]�̎��ƂȂ�_)
	D3DXVECTOR2 centerpoint = D3DXVECTOR2(stump_pos.x + stump_size.x / 2, stump_pos.y - stump_size.y / 2);

	//���Ɠ����_�̒���
	float move_length = sqrtf(LENGTH(centerpoint - wood_move_pos));

	wood_move_pos.x += move_length * cosf(rot);
	wood_move_pos.y -= move_length * sinf(rot);

	return wood_move_pos;
}
//�E����؂��č��ɓ|���Ƃ�
D3DXVECTOR2 WoodLeftMove(D3DXVECTOR2 wood_move_pos, D3DXVECTOR2 stump_pos, D3DXVECTOR2 stump_size, float rot)
{
	//�؂芔�̍���̍��W(��]�̎��ƂȂ�_)
	D3DXVECTOR2 centerpoint = D3DXVECTOR2(stump_pos.x - stump_size.x / 2, stump_pos.y - stump_size.y / 2);

	//���Ɠ����_�̒���
	float move_length = sqrtf(LENGTH(centerpoint - wood_move_pos));

	wood_move_pos.x -= move_length * cosf(rot);
	wood_move_pos.y -= move_length * sinf(rot);

	return wood_move_pos;
}

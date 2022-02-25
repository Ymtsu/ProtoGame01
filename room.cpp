//=============================================================================
//
// �G�l�~�[���� [room.cpp]
// Author : 
//
//=============================================================================

#include "room.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "input.h"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER* pPlayer = GetPlayer();


static int room_time;					//���[���̍L���鎞��
static int room_texNo;					// �e�N�X�`���ԍ�
static int room_area;					//���[���͈̔�
static bool room_use;					//���[�����L���鎞�Ԃ̃t���O
static bool old_use;					//�P�t���[���O�̃t���O
static D3DXVECTOR2 room_pos;			//���[���̃|�W�V����
static D3DXVECTOR2 room_size_vector;	//
static D3DXVECTOR2 room_size;			//���[���̑傫��

//=============================================================================
// ����������
//=============================================================================
void InitRoom(void)
{
	room_time = 0;
	room_texNo = LoadTexture("data/TEXTURE/room.png");
	room_use = false;
	old_use = room_use;
	room_size_vector = D3DXVECTOR2(8.0f, 8.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRoom(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRoom(void)
{
	PLAYER* GetPlayer();
	old_use = room_use;

	//R���������烋�[�����N��
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

	//�N�����I����Ă���X�b��ɏ�����
	if (room_time > 210)
	{
		room_use = false;
		room_time = 0;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRoom(void)
{
	if (room_use == true)
	{
		if (room_time < 30)
		{
			room_pos = room_pos - room_size_vector;
			room_size.x = fabsf((room_pos.x - pPlayer->pos.x)) * 2;
			room_size.y = fabsf((room_pos.y - pPlayer->pos.y));
		}

		DrawSpriteLeftTopColor(room_texNo, room_pos.x, room_pos.y + (pPlayer->h / 2), room_size.x, room_size.y, 0.0f, 0.0f, 1.0f, 0.5f,D3DXCOLOR(1.0f,1.0f,1.0f,0.3f));
	}
}


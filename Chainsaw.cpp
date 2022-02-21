//=============================================================================
//
// �`�F���\�[���� [Chainsaw.cpp]
// Author : 
//
//=============================================================================
#include "Chainsaw.h"
#include "texture.h"
#include "sprite.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static CHAINSAW g_Chainsaw[CHAINSAW_MAX];							// �`�F���\�[�\����


static D3DXVECTOR2 g_Collisiona_Move = D3DXVECTOR2(0.0f, 0.0f);
static bool Move_x[CHAINSAW_MAX];
static bool Move_y[CHAINSAW_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitChainsaw(void)
{
	//�`�F���\�[�̉摜
	int texNo = LoadTexture("data/TEXTURE/CSaw.png");
	//�����蔻��̉摜
	int ColiTexNo = LoadTexture("data/Texture/collisionDisplay.png");

	//�����蔻������̈ʒu�ړ��̏�����
	g_Collisiona_Move.x = 75.0f / 10.0f;
	g_Collisiona_Move.y = 60.0f / 20.0f;

	// �`�F���\�[�\���̂̏�����
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
// �I������
//=============================================================================
void UninitChainsaw(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateChainsaw(void)
{
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == true)	// ���̃`�F���\�[���g���Ă���H
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
			
			// ��ʊO�܂Ői�񂾁H
			if (g_Chainsaw[i].Anime == 30)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				g_Chainsaw[i].use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawChainsaw(void)
{
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == true)	// ���̃`�F���\�[���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Chainsaw[i].pos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Chainsaw[i].pos.y;	// �o���b�g�̕\���ʒuY
			float pw = g_Chainsaw[i].w;		// �o���b�g�̕\����
			float ph = g_Chainsaw[i].h;		// �o���b�g�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Chainsaw[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);

			//�����蔻��e�N�X�`���[�i��ŏ��������j
			DrawSprite(g_Chainsaw[i].CollisionTextNo, g_Chainsaw[i].CollisionPos.x, g_Chainsaw[i].CollisionPos.y, g_Chainsaw[i].CollisionSize.x, g_Chainsaw[i].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f);
		}
	}

}


//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
CHAINSAW *GetChainsaw(void)
{
	return &g_Chainsaw[0];
}


//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetChainsaw(D3DXVECTOR2 pos)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		if (g_Chainsaw[i].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			g_Chainsaw[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Chainsaw[i].pos = pos;			// ���W���Z�b�g
			g_Chainsaw[i].Anime = 0;
			g_Chainsaw[i].rot = 1.25f;
			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}
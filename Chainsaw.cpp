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
#include "Enemy.h"
#include "collision.h"
#include "Hit_stop.h"

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
static int ChangeHit = 0;
static float Moverot[CHAINSAW_MAX] = { 0.0f };

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
	g_Collisiona_Move.x = 75.0f / 20.0f;
	g_Collisiona_Move.y = 60.0f / 40.0f;

	// �`�F���\�[�\���̂̏�����
	for (int i = 0; i < CHAINSAW_MAX; i++)
	{
		g_Chainsaw[i].use = false;
		g_Chainsaw[i].w = 100.0f;
		g_Chainsaw[i].h = 50.0f;
		g_Chainsaw[i].pos = D3DXVECTOR2(100, 50.0f);
		g_Chainsaw[i].CollisionPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Chainsaw[i].CollisionSize = D3DXVECTOR2(100.0f, 50.0f);
		g_Chainsaw[i].rot = 0.0f;
		g_Chainsaw[i].texNo = texNo;
		g_Chainsaw[i].CollisionTextNo = ColiTexNo;
		g_Chainsaw[i].Anime = 0;		
		g_Chainsaw[i].Vector = D3DXVECTOR2(0.0f, 100.0f);
		Moverot[i] = 0.1f;
		
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
			
			if (g_Chainsaw[i].direction == Right)
			{
				g_Chainsaw[i].rot += Moverot[i];
			}
			
			if (g_Chainsaw[i].direction == Left)
			{
				g_Chainsaw[i].rot -= Moverot[i];
			}
			
			//player�̍��W�擾
			D3DXVECTOR2 pPlayer_pos = GetPlayerPos();

			g_Chainsaw[i].pos = pPlayer_pos;

			


			float circle_block_vector_length = sqrtf(LENGTH(g_Chainsaw[i].Vector));
			//�{�[���ƃu���b�N�����񂾉��z�x�N�g��
			g_Chainsaw[i].pos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[i].rot);
			g_Chainsaw[i].pos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[i].rot);


			g_Chainsaw[i].CollisionPos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[i].rot);
			g_Chainsaw[i].CollisionPos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[i].rot);

			

			ENEMY * pEnemy = GetEnemy();

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (pEnemy[i].use == true)
				{
					for (int z = 0; z < CHAINSAW_MAX; z++)
					{
						if (CollisionBB(g_Chainsaw[z].CollisionPos, pEnemy[i].pos, D3DXVECTOR2((g_Chainsaw[z].w), (g_Chainsaw[z].h)), D3DXVECTOR2((pEnemy[i].w), (pEnemy[i].h)))) {
							switch (pEnemy[i].kind)
							{
							case 0:
								Moverot[z] = Hitstop_angle(Moverot[z], g_Chainsaw[z].rot, (g_Chainsaw[z].rot + 1.0f), 0.8f);
								break;

							case 1:
								Moverot[z] = Hitstop_angle(Moverot[z], g_Chainsaw[z].rot, (g_Chainsaw[z].rot + 1.0f), 0.5f);
								break;

							default:
								break;
							}
							
							DelEnemyHP(i);
						}
					}
					
				}
			}

			//�`�F���\�[�̉摜��������x��]�����烊�Z�b�g����悤�ɐݒ�
			if (g_Chainsaw[i].direction == Right)
			{
				if (g_Chainsaw[i].rot >= 6.5f)
				{
					g_Chainsaw[i].use = false;
					PlayerMoveReset();
					SetFlag();
				}
			}
			
			if (g_Chainsaw[i].direction == Left)
			{
				if (g_Chainsaw[i].rot <= 3.0f)
				{
					g_Chainsaw[i].use = false;
					PlayerMoveReset();
					SetFlag();
				}
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

			

			//�����蔻��e�N�X�`���[�i��ŏ��������j
			DrawSpriteColorRotate(g_Chainsaw[i].CollisionTextNo, g_Chainsaw[i].CollisionPos.x, g_Chainsaw[i].CollisionPos.y, g_Chainsaw[i].CollisionSize.x, g_Chainsaw[i].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Chainsaw[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[i].rot);
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
		if (g_Chainsaw[i].use == false)							// ���g�p��Ԃ̃o���b�g��������
		{
			g_Chainsaw[i].use = true;							// �g�p��Ԃ֕ύX����
			g_Chainsaw[i].pos = pos;							// ���W���Z�b�g
			g_Chainsaw[i].direction = GetPlayerDir();			//�ǂ��������Ɏg�p����̂���ݒ肷��
			if (g_Chainsaw[i].direction == Right)
			{
				g_Chainsaw[i].rot = 3.75f;							//��]�ʒu����ɂȂ�悤�ɐݒ�
			}
			if (g_Chainsaw[i].direction == Left)
			{
				g_Chainsaw[i].rot = 5.00f;							//��]�ʒu����ɂȂ�悤�ɐݒ�
			}
			g_Chainsaw[i].Vector = D3DXVECTOR2(0.0f, 100.0f);
			Moverot[i] = 0.1f; 
			return;												// 1���Z�b�g�����̂ŏI������
		}
	}
}
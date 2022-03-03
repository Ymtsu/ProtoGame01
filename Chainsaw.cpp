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
#include "input.h"
#include "sound.h"

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
static float g_hard = 0.0f;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitChainsaw(void)
{
	//�`�F���\�[�̉摜
	int texNo = LoadTexture("data/TEXTURE/CSaw.png");
	//�����蔻��̉摜
	int ColiTexNo = LoadTexture("data/Texture/collisionDisplay.png");
	//�����蔻��̃A�j���[�V����
	int effectNo = LoadTexture("data/ANIMATION/�`�F�[���\�[�G�t�F�N�g.png");
	////�`���[�W�̃A�j���[�V����
	//int chageNo = LoadTexture("data/ANIMATION/�`�F�[���\�[�G�t�F�N�g.png");

	int SENo = LoadSound("data/SE/�[�Ŗ؂�؂�2.wav");

	//�����蔻������̈ʒu�ړ��̏�����
	g_Collisiona_Move.x = 75.0f / 20.0f;
	g_Collisiona_Move.y = 60.0f / 40.0f;

	// �`�F���\�[�\���̂̏�����
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		g_Chainsaw[ChainsawNum].use = false;
		g_Chainsaw[ChainsawNum].w = 100.0f;
		g_Chainsaw[ChainsawNum].h = 50.0f;
		g_Chainsaw[ChainsawNum].pos = D3DXVECTOR2(100, 50.0f);
		g_Chainsaw[ChainsawNum].CollisionPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Chainsaw[ChainsawNum].CollisionSize = D3DXVECTOR2(100.0f, 50.0f);
		g_Chainsaw[ChainsawNum].rot = 0.0f;
		g_Chainsaw[ChainsawNum].texNo = texNo;
		g_Chainsaw[ChainsawNum].CollisionTextNo = ColiTexNo;
		g_Chainsaw[ChainsawNum].StopCount = 0;		
		g_Chainsaw[ChainsawNum].Vector = D3DXVECTOR2(0.0f, 100.0f);
		g_Chainsaw[ChainsawNum].Moverot = 0.1f;
		g_Chainsaw[ChainsawNum].Preliminary = false;
		g_Chainsaw[ChainsawNum].Charge = 0;
		g_Chainsaw[ChainsawNum].OldCharge = 0;
		g_Chainsaw[ChainsawNum].CollisionAnimetionTextNo = effectNo;
		g_Chainsaw[ChainsawNum].Collisionflg = 0;
		g_Chainsaw[ChainsawNum].SE = SENo;
		g_Chainsaw[ChainsawNum].SEUse = false;
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == true)	// ���̃`�F���\�[���g���Ă���H
		{								// Yes
			
			if (g_Chainsaw[ChainsawNum].SEUse == true)
			{
				PlaySounds(g_Chainsaw[ChainsawNum].SE, -1);
				g_Chainsaw[ChainsawNum].SEUse = false;
			}
			//OldChage�X�V
			g_Chainsaw[ChainsawNum].OldCharge = g_Chainsaw[ChainsawNum].Charge;

			//Charge�X�V
			if (GetKeyboardPress(DIK_SPACE)||IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
			{
				g_Chainsaw[ChainsawNum].Charge += 1;
			}

			//�`�F���\�[�E�����̍X�V����
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				//�`�F���\�[�U��グ����
				if (g_Chainsaw[ChainsawNum].Preliminary == true)
				{
					g_Chainsaw[ChainsawNum].Moverot += 0.002f;
					g_Chainsaw[ChainsawNum].rot -= g_Chainsaw[ChainsawNum].Moverot;
					if (g_Chainsaw[ChainsawNum].rot <= 4.0)
					{
						g_Chainsaw[ChainsawNum].Preliminary = false;
						g_Chainsaw[ChainsawNum].Moverot = 0.0f;
					}
				}
				else
				{
					//�`���[�W�ɂ���ĕω�
					if (g_Chainsaw[ChainsawNum].Charge == g_Chainsaw[ChainsawNum].OldCharge)
					{
						//�ŏ��`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge <= 20)
						{
							g_Chainsaw[ChainsawNum].StopCount += 1;
						}
						if (g_Chainsaw[ChainsawNum].StopCount >= 15)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.005f;							
						}

						//���ԃ`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge <= 40 && g_Chainsaw[ChainsawNum].Charge > 20)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.008f;
						}

						//�ŏI�`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge > 40)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.012f;
						}
						g_Chainsaw[ChainsawNum].rot += g_Chainsaw[ChainsawNum].Moverot;
					}
				}
				

			}

			//�`�F���\�[�������̍X�V����
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{

				//�`�F���\�[�U��グ����
				if (g_Chainsaw[ChainsawNum].Preliminary == true)
				{
					g_Chainsaw[ChainsawNum].Moverot += 0.002f;
					g_Chainsaw[ChainsawNum].rot += g_Chainsaw[ChainsawNum].Moverot;
					if (g_Chainsaw[ChainsawNum].rot >= 5.5)
					{
						g_Chainsaw[ChainsawNum].Preliminary = false;
						g_Chainsaw[ChainsawNum].Moverot = 0.0f;
					}
				}
				else
				{
					//�`���[�W�ɂ���ĕω�
					if (g_Chainsaw[ChainsawNum].Charge == g_Chainsaw[ChainsawNum].OldCharge)
					{
						//�ŏ��`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge <= 20)
						{
							g_Chainsaw[ChainsawNum].StopCount += 1;
						}
						if (g_Chainsaw[ChainsawNum].StopCount >= 15)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.005f;
						}

						//���ԃ`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge <= 40 && g_Chainsaw[ChainsawNum].Charge > 20)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.008f;
						}

						//�ŏI�`���[�W��
						if (g_Chainsaw[ChainsawNum].Charge > 40)
						{
							g_Chainsaw[ChainsawNum].Moverot += 0.012f;
						}
						g_Chainsaw[ChainsawNum].rot -= g_Chainsaw[ChainsawNum].Moverot;
					}

				}
			}
			
			//player�̍��W�擾
			D3DXVECTOR2 pPlayer_pos = GetPlayerPos();

			g_Chainsaw[ChainsawNum].pos = pPlayer_pos;

			


			float circle_block_vector_length = sqrtf(LENGTH(g_Chainsaw[ChainsawNum].Vector));
			//�{�[���ƃu���b�N�����񂾉��z�x�N�g��
			g_Chainsaw[ChainsawNum].pos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[ChainsawNum].rot);
			g_Chainsaw[ChainsawNum].pos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[ChainsawNum].rot);


			g_Chainsaw[ChainsawNum].CollisionPos.x = pPlayer_pos.x + circle_block_vector_length * cosf(g_Chainsaw[ChainsawNum].rot);
			g_Chainsaw[ChainsawNum].CollisionPos.y = pPlayer_pos.y + circle_block_vector_length * sinf(g_Chainsaw[ChainsawNum].rot);

			

			ENEMY * pEnemy = GetEnemy();

			for (int enemy = 0; enemy < ENEMY_MAX; enemy++)
			{
				if (pEnemy[enemy].use == true)
				{
					if (g_Chainsaw[ChainsawNum].Preliminary == false)
					{
						if (CollisionBB(g_Chainsaw[ChainsawNum].CollisionPos, pEnemy[enemy].pos, D3DXVECTOR2((g_Chainsaw[ChainsawNum].w), (g_Chainsaw[ChainsawNum].h)), D3DXVECTOR2((pEnemy[enemy].w), (pEnemy[enemy].h)))) {
							switch (pEnemy[enemy].kind)
							{
							case 0:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;
								break;

							case 1:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 2:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 3:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 4:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;

							case 5:
								g_hard = GetEnemyHard(enemy);
								g_Chainsaw[ChainsawNum].Moverot = HitstopAngle(g_Chainsaw[ChainsawNum].Moverot, g_Chainsaw[ChainsawNum].rot, (g_Chainsaw[ChainsawNum].rot + 1.0f), g_hard);
								g_Chainsaw[ChainsawNum].Animetion += 1;
								if (g_Chainsaw[ChainsawNum].Animetion > 30)
								{
									g_Chainsaw[ChainsawNum].Animetion = 0;
								}
								g_Chainsaw[ChainsawNum].Collisionflg = 1;

								break;
							
							default:
								break;
							}

							DelEnemyHP(ChainsawNum);
						}
						else
						{
							if (g_Chainsaw[ChainsawNum].Collisionflg == 1)
							{
								g_Chainsaw[ChainsawNum].Collisionflg = 2;
							}
							
						}
					}
				}
			}


			if (g_Chainsaw[ChainsawNum].Collisionflg == 2)
			{
				HitstopEndAcceleration(g_Chainsaw[ChainsawNum].rot, g_hard);
			}
			//�`�F���\�[�̉摜��������x��]�����烊�Z�b�g����悤�ɐݒ�i�E��]�j
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				if (g_Chainsaw[ChainsawNum].rot >= 7.0f)
				{
					g_Chainsaw[ChainsawNum].use = false;
					PlayerMoveReset();
					SetFlag();
					g_Chainsaw[ChainsawNum].StopCount = 0;
					StopSound(g_Chainsaw[ChainsawNum].SE);
				}
			}

			//�`�F���\�[�̉摜��������x��]�����烊�Z�b�g����悤�ɐݒ�i����]�j
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{
				if (g_Chainsaw[ChainsawNum].rot <= 2.0f)
				{
					g_Chainsaw[ChainsawNum].use = false;
					PlayerMoveReset();
					SetFlag();
					StopSound(g_Chainsaw[ChainsawNum].SE);
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == true)	// ���̃`�F���\�[���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Chainsaw[ChainsawNum].pos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Chainsaw[ChainsawNum].pos.y;	// �o���b�g�̕\���ʒuY
			float pw = g_Chainsaw[ChainsawNum].w;		// �o���b�g�̕\����
			float ph = g_Chainsaw[ChainsawNum].h;		// �o���b�g�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			

			//�����蔻��e�N�X�`���[�i��ŏ��������j
			DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].CollisionTextNo, g_Chainsaw[ChainsawNum].CollisionPos.x, g_Chainsaw[ChainsawNum].CollisionPos.y, g_Chainsaw[ChainsawNum].CollisionSize.x, g_Chainsaw[ChainsawNum].CollisionSize.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);

			

			if (g_Chainsaw[ChainsawNum].Charge <= 40)
			{
				D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);
			}

			else if (g_Chainsaw[ChainsawNum].Charge <= 60)
			{
				D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Chainsaw[ChainsawNum].rot);
			}


			if (g_Chainsaw[ChainsawNum].Collisionflg == 1)
			{
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				int	Animetion = (g_Chainsaw[ChainsawNum].Animetion / 2);
				float TextU =  (1.0f/ 6.0f) * (Animetion % 6);
				float TextV = (1.0f /5.0f) * (Animetion / 6);

				DrawSpriteColorRotate(g_Chainsaw[ChainsawNum].CollisionAnimetionTextNo, px, py, 500.0f, 500.0f, TextU, TextV, (1.0f/6.0f), (1.0f/5.0f), col, g_Chainsaw[ChainsawNum].rot);
			}

			
			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			
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
	for (int ChainsawNum = 0; ChainsawNum < CHAINSAW_MAX; ChainsawNum++)
	{
		if (g_Chainsaw[ChainsawNum].use == false)							// ���g�p��Ԃ̃o���b�g��������
		{
			g_Chainsaw[ChainsawNum].use = true;							// �g�p��Ԃ֕ύX����
			g_Chainsaw[ChainsawNum].pos = pos;							// ���W���Z�b�g
			g_Chainsaw[ChainsawNum].direction = GetPlayerDir();			//�ǂ��������Ɏg�p����̂���ݒ肷��
			g_Chainsaw[ChainsawNum].Preliminary = true;
			if (g_Chainsaw[ChainsawNum].direction == Right)
			{
				g_Chainsaw[ChainsawNum].rot = 5.5f;							//��]�ʒu����ɂȂ�悤�ɐݒ�
			}
			if (g_Chainsaw[ChainsawNum].direction == Left)
			{
				g_Chainsaw[ChainsawNum].rot = 4.0f;							//��]�ʒu����ɂȂ�悤�ɐݒ�
			}
			g_Chainsaw[ChainsawNum].Vector = D3DXVECTOR2(0.0f, 100.0f);
			g_Chainsaw[ChainsawNum].Moverot = 0.0f;
			g_Chainsaw[ChainsawNum].Charge = 0;
			g_Chainsaw[ChainsawNum].OldCharge = 0;
			g_Chainsaw[ChainsawNum].StopCount = 0;
			g_Chainsaw[ChainsawNum].Animetion = 0;
			g_Chainsaw[ChainsawNum].SEUse = true;
			return;												// 1���Z�b�g�����̂ŏI������
		}
	}
}
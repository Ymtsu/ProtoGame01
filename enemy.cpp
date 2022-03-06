//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : 
//����
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "Player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ResetEnemy(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static ENEMY g_Enemy[ENEMY_MAX];							// �G�l�~�[�\����
static int EnemyTexture_01 = 0;
static int EenmyTexture_02 = 0;
static int EnenyTexture_03 = 0;
static int EnemyTexture_04 = 0;
static int g_MapNumber = 0;
static int g_OldMapNumber = -1;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	EnemyTexture_01 = LoadTexture("data/TEXTURE/058865.png");
	EenmyTexture_02 = LoadTexture("data/TEXTURE/����.png");
	EnenyTexture_03 = LoadTexture("data/TEXTURE/����.png");
	EnemyTexture_04 = LoadTexture("data/TEXTURE/�z��.png");

	// �G�l�~�[�\���̂̏�����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use = false;
		g_Enemy[i].w = 100.0f;
		g_Enemy[i].h = 100.0f;
		g_Enemy[i].pos = D3DXVECTOR2(600.0f, 600.0f);
		g_Enemy[i].rot = 0.0f;
		g_Enemy[i].texNo = EnemyTexture_01;
		g_Enemy[i].state = 0;
		g_Enemy[i].frame = 0;
		g_Enemy[i].kind = 0;
		g_Enemy[i].hard = 0.0f;
		g_Enemy[i].HP = 0;
		g_Enemy[i].destroy = false;
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	g_MapNumber = GetMapNumber();
	if (g_MapNumber != g_OldMapNumber)
	{
		switch (g_MapNumber)
		{
		case 0:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(600.0f, 400.0f), 0);
			break;

		case 1:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 1);
			break;

		case 2:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 2);
			break;

		case 3:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 3);
			break;
		case 4:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 4);
			break;

		case 5:
			ResetEnemy();
			SetEnemy(D3DXVECTOR2(400.0f, 400.0f), 5);
			break;

		default:
			break;
		}
		g_OldMapNumber = g_MapNumber;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// ���̃G�l�~�[���g���Ă���H
		{								// Yes	
			if (g_Enemy[i].HP <= 0)
			{
				g_Enemy[i].use = false;
				g_Enemy[i].destroy = true;
			}



			//�t���[���̒ǉ�
			g_Enemy[i].frame++;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)
		{
			//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Enemy[i].pos.x;	// �G�l�~�[�̕\���ʒuX
			float py = g_Enemy[i].pos.y;	// �G�l�~�[�̕\���ʒuY
			float pw = g_Enemy[i].w;		// �G�l�~�[�̕\����
			float ph = g_Enemy[i].h;		// �G�l�~�[�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Enemy[i].rot);
		}

		//�I�u�W�F�N�g����ꂽ�Ƃ�
		if (!g_Enemy[i].use && g_Enemy[i].destroy)
		{
			float destroy_pos = (g_Enemy[i].w / 4) + 20.0f;
			//����
			float px = g_Enemy[i].pos.x - destroy_pos;	// �G�l�~�[�̕\���ʒuX
			float py = g_Enemy[i].pos.y;	// �G�l�~�[�̕\���ʒuY
			float pw = g_Enemy[i].w / 2;		// �G�l�~�[�̕\����
			float ph = g_Enemy[i].h;		// �G�l�~�[�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 0.5f, 1.0f, col, g_Enemy[i].rot);

			//�E��
			px = g_Enemy[i].pos.x + destroy_pos;	// �G�l�~�[�̕\���ʒuX

			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.5f, 0.0f, 0.5f, 1.0f, col, g_Enemy[i].rot);
		}
	}
}

//=============================================================================
// �G�l�~�[�\���̂̐擪�A�h���X���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}


//=============================================================================
// �G�̔�������
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos, int EnemyKind)
{
	// �������g�p�̃f�[�^��T��
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == false)		// ���g�p��Ԃ̓G�f�[�^��������
		{
			g_Enemy[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Enemy[i].pos = pos;			// ���W���Z�b�g
			g_Enemy[i].rot = 0.0f;			// ��]�p�̃��Z�b�g
			g_Enemy[i].state = 0;			// ��Ԃ����Z�b�g
			g_Enemy[i].frame = 0;			// �t���[���̃��Z�b�g

			switch (EnemyKind)
			{
			case 0:
				g_Enemy[i].HP = 5;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnenyTexture_03;
				g_Enemy[i].hard = 1.0f;
				break;

			case 1:
				g_Enemy[i].HP = 10;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnenyTexture_03;
				g_Enemy[i].hard = 0.8f;
				break;

			case 2:
				g_Enemy[i].HP = 10;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_01;
				g_Enemy[i].hard = 0.6f;
				break;

			case 3:
				g_Enemy[i].HP = 20;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_01;
				g_Enemy[i].hard = 0.4f;
				break;


			case 4:
				g_Enemy[i].HP = 30;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EenmyTexture_02;
				g_Enemy[i].hard = 0.005f;
				break;

			case 5:
				g_Enemy[i].HP = 30;
				g_Enemy[i].kind = EnemyKind;
				g_Enemy[i].texNo = EnemyTexture_04;
				g_Enemy[i].hard = 0.001f;
				break;
			}
			return;							// �G���Z�b�g�ł����̂ŏI������
		}
	}

}


//=============================================================================
// �G�̏�������
//=============================================================================
void ResetEnemy(void)
{
	// �������g�p�̃f�[�^��T��
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// ���g�p��Ԃ̓G�f�[�^��������
		{
			g_Enemy[i].use = false;			// �g�p��Ԃ֕ύX����


		}
	}
	return;
}

//=============================================================================
// �G��HP�����炷����
//=============================================================================
void DelEnemyHP(int EnemyNum)
{
	// �������g�p�̃f�[�^��T��
	g_Enemy[EnemyNum].HP -= 1;
	return;
}

float GetEnemyHard(int index)
{
	return g_Enemy[index].hard;
}

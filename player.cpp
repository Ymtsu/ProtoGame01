/*==============================================================================

   ���_�Ǘ� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "collision.h"
#include "Physics.h"
#include "Chainsaw.h"
#include "Enemy.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MAP_STAGE (3)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player;
static int g_ShotSENo = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//�ړ��t���O
static int g_PlayerMoveFlg = 0;
//�d�͕���
static bool g_GravityUse = false;
static float g_Gravity = 0.0f;
//�W�����v����
static bool g_JumpUse = false;

//�X�e�[�W�ړ�
static int g_MoveStage = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���
	g_Player.texNo = LoadTexture("data/TEXTURE/majo.png");

	//SE�ǂݍ���
	g_ShotSENo = LoadSound("data/SE/shot000.wav");

	//������
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = 370;
	g_Player.oldpos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.w = 100.0f;
	g_Player.h = 100.0f;
	g_Player.use = true;
	g_Player.dirction = Right;

	//�d�͏�����
	g_GravityUse = true;
	g_Gravity = Gravity(1.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.pos != g_Player.oldpos)
	{
		g_Player.oldpos = g_Player.pos;
	}

	//�ړ��t���O��0�̎��݈̂ړ��\
	if (g_PlayerMoveFlg == 0)
	{


		if (GetKeyboardPress(DIK_W))
		{
			g_JumpUse = true;

			/*g_Player.dirction = Up;*/
			
		}

		////�������i���ݎg�p�\��Ȃ��j
		//if (GetKeyboardPress(DIK_S))
		//{
		//	/*if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y + 1.0f)) != 1)
		//		g_Player.pos.y += 1.0f;*/

		//	/*g_Player.dirction = Down;*/
		//	
		//}

		int PadMove = GetThumbLeftX(0);

		if (GetKeyboardPress(DIK_A) || PadMove < 0)
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x -= 3.0f;

			g_Player.dirction = Left;
			
		}

		if (GetKeyboardPress(DIK_D))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x += 3.0f;

			g_Player.dirction = Right;
			
		}

	}

	switch (g_Player.dirction)
	{
	case Right:
		g_CharaUV = 0.5f;
		break;

	case Left:
		g_CharaUV = 0.25f;
		break;

	case Down:
		g_CharaUV = 0.0f;
		break;

	case Up:
		g_CharaUV = 0.75f;
		break;

	default:
		break;
	}

	//�W�����v�t���O�g�p��
	if (g_JumpUse == true)
	{
		g_Player.pos.y -= 3.0f;
		if (g_Player.pos.y <= 320.0f)
		{
			g_JumpUse = false;
		}

	}

	//�d�̓t���O�g�p��
	if (g_GravityUse == true)
	{
		g_Player.pos.y += g_Gravity;
	}

	//�n�ʔ���i���݂�CollisionBB�g�p�j
	if (CollisionBB(g_Player.pos, D3DXVECTOR2((SCREEN_WIDTH / 2), 480.0f), D3DXVECTOR2((g_Player.w), (g_Player.h)), D3DXVECTOR2((SCREEN_WIDTH + 160.0f), 160.0f)) == true)
	{
		g_GravityUse = false;
		g_Gravity = 0.0f;
	}
	else
	{
		g_Gravity = Gravity(1.0f);
		g_GravityUse = true;
	}


	//���}�b�v�֐؂�ւ���
	if (g_Player.pos.x > SCREEN_WIDTH)
	{
		g_Player.pos.x = 8.0f;
		g_MoveStage += 1;
		if (g_MoveStage > (MAX_MAP_STAGE - 1))
		{
			g_MoveStage = g_MoveStage - 1;
		}
		SetCurrentMap(g_MoveStage);
	}
	//�O�}�b�v�֐؂�ւ���
	if (g_Player.pos.x < 0.0f)
	{
		g_Player.pos.x = (SCREEN_WIDTH - 8.0f);
		g_MoveStage -= 1;
		if (g_MoveStage < 0)
		{
			g_MoveStage = g_MoveStage + 1;
		}
		SetCurrentMap(g_MoveStage);
	}


	ENEMY * pEnemy = GetEnemy();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (pEnemy[i].use == true)
		{
			if (CollisionBB(g_Player.pos,pEnemy[i].pos, D3DXVECTOR2((g_Player.w), (g_Player.h)), D3DXVECTOR2((pEnemy[i].w), (pEnemy[i].h)))) {
				g_Player.w -= 1.0f;
				g_Player.h -= 1.0f;
			}
		}
	}
	//// �e����
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	PlaySound(g_ShotSENo, 0);

	//	SetVolume(g_ShotSENo, 0.1f);

	//	D3DXVECTOR2 pos = g_Player.pos;
	//	SetBullet(pos);		// �P����
	//	AddScore(123);
	//}

	//�`�F���\�[�g�p
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_A))
	{
		/*PlaySound(g_ShotSENo, 0);*/

		SetVolume(g_ShotSENo, 0.1f);

		D3DXVECTOR2 pos = g_Player.pos;
		SetChainsaw(pos);		// �P����
		g_PlayerMoveFlg = 1;
	}


	//�����A�j���[�V����
	if (g_AnimeWaitFrame > 10)
	{
		g_AnimePtn++;
		if (g_AnimePtn > 2)
			g_AnimePtn = 0;

		g_AnimeWaitFrame = 0;
	}
	g_AnimeWaitFrame++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	
	DrawSprite(g_Player.texNo, g_Player.pos.x, g_Player.pos.y, g_Player.w, g_Player.h, g_AnimePtn * 0.33333f, g_CharaUV, 0.3333f, 0.25f);
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// �v���C���[�̈ʒu���擾
//=============================================================================
D3DXVECTOR2 GetPlayerPos(void)
{
	return g_Player.pos;
}

//=============================================================================
// �v���C���[�̕������擾
//=============================================================================
int GetPlayerDir(void)
{
	return g_Player.dirction;
}

//=============================================================================
// �v���C���[�𓮂���悤�Ƀ��Z�b�g����@�\
//=============================================================================
void PlayerMoveReset(void)
{
	g_PlayerMoveFlg = 0;
}

//=============================================================================
// �}�b�v�i���o�[���擾
//=============================================================================
int GetMapNumber(void)
{
	return g_MoveStage;
}

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
	g_Player.pos.y = 350.0f;
	g_Player.oldpos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.vector = D3DXVECTOR2(5.0f, 3.0f);
	g_Player.size = D3DXVECTOR2(100.0f, 100.0f);
	g_Player.use = true;
	g_Player.dirction = Right;
	g_Player.isgrounded = false;
	g_Player.isdashing = false;
	g_Player.dashtimer = 0.0f;

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


		if (GetKeyboardPress(DIK_W) || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && g_Player.isgrounded == true)
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

		
		int PAD = GetThumbLeftX(0);

		if (GetKeyboardPress(DIK_A) || PAD < 0)
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x - 1.0f, g_Player.pos.y)) != 1)
				//g_Player.pos.x -= 5.0f;
			   g_Player.pos.x -= g_Player.vector.x;

			g_Player.dirction = Left;
			
		}
		
		if (GetKeyboardPress(DIK_D) || PAD > 0)
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				//g_Player.pos.x += 5.0f;
			    g_Player.pos.x += g_Player.vector.x;

			g_Player.dirction = Right;
			
		}

		//�_�b�V��
		if(GetKeyboardPress(DIK_E) && g_Player.dirction == Right && g_Player.isdashing == false)
		{
			g_Player.isdashing = true;
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x += 195.0f;
		}

		if (GetKeyboardPress(DIK_E) && g_Player.dirction == Left && g_Player.isdashing == false)
		{
			g_Player.isdashing = true;
			if (GetMapEnter(D3DXVECTOR2(g_Player.pos.x + 1.0f, g_Player.pos.y)) != 1)
				g_Player.pos.x -= 195.0f;
		}

		if (g_Player.isdashing == true)
		{
			g_Player.dashtimer = g_Player.dashtimer  + 1.0f;
		}

		if (g_Player.dashtimer >= 60.0f) //1s�� �N�[���_�E��
		{
			g_Player.dashtimer = 0.0f;
			g_Player.isdashing = false;
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
		//g_Player.pos.y -= 9.0f; //jump speed �W�����v���x
		g_Player.pos.y -= g_Player.vector.y;

		if (g_Player.pos.y <= 220.0f) //max jump height �W�����v�̍���
		{
			g_JumpUse = false;
		}
	}

	//�n�ʔ���i���݂�CollisionBB�g�p�j
	//if (CollisionBB(g_Player.pos, D3DXVECTOR2((SCREEN_WIDTH / 2), 480.0f), D3DXVECTOR2((g_Player.size.x), (g_Player.size.y)), D3DXVECTOR2((SCREEN_WIDTH + 160.0f), 160.0f)) == true)
	//{
	//	g_JumpUse = false;
	//	g_Player.vector.y = 5.0f;
	//	/*g_GravityUse = false;
	//	g_Gravity = 0.0f;*/
	//}
	//else
	//{
	//	g_Gravity = Gravity(1.0f);
	//	g_GravityUse = true;
	//}

	//temporary groundcheck
	if (g_Player.pos.y >= 370.0f)
	{
		g_Player.isgrounded = true;
		g_GravityUse = false;
		g_Gravity = 0.0f;
	}
	else
	{
		g_Player.isgrounded = false;
		g_Gravity = Gravity(3.0f);
		g_GravityUse = true;
	}

	//�d�̓t���O�g�p��
	if (g_GravityUse == true)
	{
		g_Player.vector.y = Gravity(g_Player.vector.y);
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
			if (CollisionBB(g_Player.pos,pEnemy[i].pos, D3DXVECTOR2((g_Player.size.x), (g_Player.size.y)), D3DXVECTOR2((pEnemy[i].w), (pEnemy[i].h)))) {
				g_Player.size.x -= 1.0f;
				g_Player.size.y -= 1.0f;
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
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
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
	
	DrawSprite(g_Player.texNo, g_Player.pos.x, g_Player.pos.y, g_Player.size.x, g_Player.size.y, g_AnimePtn * 0.33333f, g_CharaUV, 0.3333f, 0.25f);
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

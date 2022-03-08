/*==============================================================================

   ���_�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//�v���C���[�̕����\����
typedef enum  DIRCTION {
	Right,
	Left,
	Up,
	Down
}PLAYER_DIR;

// �v���C���[�\����
struct PLAYER
{
	bool					use;					// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				size;					// �傫��
	D3DXVECTOR2				pos;					// �|���S���̍��W
	D3DXVECTOR2				oldpos;					// �|���S���̍��W
	D3DXVECTOR2				vector;					// �ړ�
	float					rot;					// �|���S���̉�]��
	int						texNo;					// �e�N�X�`���ԍ�
	int						dirction;
	bool                    isgrounded;
	bool                    isdashing;
	float                   dashtimer;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
D3DXVECTOR2 GetPlayerPos(void);
int GetPlayerDir(void);
void PlayerMoveReset(void);
int GetMapNumber(void);

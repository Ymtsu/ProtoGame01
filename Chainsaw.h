//=============================================================================
//
// �`�F���\�[���� [Chainsaw.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHAINSAW_MAX		(2)		// �o���b�g��Max��


// �o���b�g�\����
struct CHAINSAW
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	D3DXVECTOR2				CollisionSize;			//�����蔻��̑傫��
	D3DXVECTOR2				CollisionPos;			//�����蔻��̈ʒu���W
	int						direction;				//�`�F���\�[�̌���
	float					rot;					// �o���b�g�̉�]��
	int						texNo;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	int						CollisionTextNo;		// �����蔻��e�N�X�`���\
	int						Anime;					// �A�j���[�V����
	D3DXVECTOR2				Vector;					//�v���C���[�܂ł̃x�N�g��
						

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitChainsaw(void);
void UninitChainsaw(void);
void UpdateChainsaw(void);
void DrawChainsaw(void);

CHAINSAW *GetChainsaw(void);
void SetChainsaw(D3DXVECTOR2 pos);
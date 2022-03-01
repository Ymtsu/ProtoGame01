//=============================================================================
//
// �؂�|������ [cut_down.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CUT_DOWN_OBJECT_MAX		(5)			// �؂�|����I�u�W�F�N�g��Max��
#define PI 3.14159265f // �~����

// �؂�|����I�u�W�F�N�g�\����
struct CUT_DOWN_OBJECT{
	bool					use;		// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				size;		// ���ƍ���
	D3DXVECTOR2				pos;		// �|���S���̍��W
	float					rot;		// �|���S���̉�]��
	int						texNo;		// ���Ԗڂ̃e�N�X�`���[���g�p����̂�

	int						state;		// ���
};




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCutDownObject(void);
void	UninitCutDownObject(void);
void UpdateCutDownObject(void);
void DrawCutDownObject(void);



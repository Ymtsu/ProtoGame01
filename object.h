//=============================================================================
//
// �I�u�W�F�N�g���N���X [object.h]
// Author : 
//���΁A�g�~�[
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

class OBJECT
{
public:
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

protected:
	D3DXVECTOR2 pos = {};			//���W
	D3DXVECTOR2 size = {};			//�傫��
	D3DXVECTOR2 vector = {};		//�x�N�g��
	float rot = {};					//��]�p�x
	float strength = {};			//���x
	int hp = {};					//�ϋv�l
	int	state = {};					//���
	int texture = {};				//�ǂݍ��݉摜
	bool use = false;				//�g�p���
	bool destroy = false;			//�j����
};
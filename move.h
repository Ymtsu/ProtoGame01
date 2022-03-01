//=============================================================================
//
// ���[�u���N���X [move.h]
// Author : ����
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

class Move
{
public:
	Move() {};
	~Move() {};

	D3DXVECTOR2 GetVector() { return m_vector; }
	D3DXVECTOR2 GetOldPos() { return m_old_pos; }
	float GetSpeed() { return m_speed; }

protected:
	D3DXVECTOR2 m_vector = {};	//�x�N�g��
	float m_speed = 0.0f; //����
	D3DXVECTOR2 m_old_pos = {}; //�����W

private:

};

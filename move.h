//=============================================================================
//
// ムーブ基底クラス [move.h]
// Author : 小島
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
	D3DXVECTOR2 m_vector = {};	//ベクトル
	float m_speed = 0.0f; //速さ
	D3DXVECTOR2 m_old_pos = {}; //旧座標

private:

};

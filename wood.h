//===========================
// ==================================================
//
// 樹木クラス [wood.h]
// Author : 
//こば、トミー
//=============================================================================
#pragma once
#include "object.h"
#include "collision.h"

enum class WoodState {
	no_exit,
	stand,
	rotation,
	fallen
};

class Wood : public Object
{
public:
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	SURFACE m_direction = SURFACE::min_error;
	int m_stump_texture = {};
	D3DXVECTOR2 m_stump_pos = {};
	D3DXVECTOR2 m_stump_size = {};
	D3DXVECTOR2 m_vertex[4] = {};
	WoodState m_state = WoodState::no_exit;

};

float CutLeftRot(float rot);
//右から切られたとき
float CutRightRot(float rot);

//左から切られて右に倒れるとき
D3DXVECTOR2 WoodRightMove(D3DXVECTOR2 wood_move_pos, D3DXVECTOR2 stump_pos, D3DXVECTOR2 stump_size, float rot);
//右から切られて左に倒れるとき
D3DXVECTOR2 WoodLeftMove(D3DXVECTOR2 wood_move_pos, D3DXVECTOR2 stump_pos, D3DXVECTOR2 stump_size, float rot);
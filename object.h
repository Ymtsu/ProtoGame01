//=============================================================================
//
// オブジェクト基底クラス [object.h]
// Author : 
//こば、トミー
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

class Object
{
public:
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

protected:
	D3DXVECTOR2 pos = {};			//座標
	D3DXVECTOR2 size = {};			//大きさ
	float rot = {};					//回転角度
	float strength = {};			//強度
	int hp = {};					//耐久値
	int	state = {};					//状態
	int texture = {};				//読み込み画像
	bool use = false;				//使用状態
	bool destroy = false;			//破壊状態
};
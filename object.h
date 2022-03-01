//=============================================================================
//
// オブジェクト基底クラス [object.h]
// Author : 
//こば、トミー
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "texture.h"

//状態
enum class STATE : const char
{
	not_exit
};


class Object
{
public:
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void);
	
	//セブンスター、ゲット!!
	D3DXVECTOR2 GetPos() { return m_pos; }
	void	SetPos(D3DXVECTOR2 pos) { m_pos = pos; }

	D3DXVECTOR2 GetSize() { return m_size; }

	float GetRot() { return m_rot; }
	void SetRot(float rot) { m_rot = rot; }

	float GetStrength() { return m_strength; }
	void SetStrength(float strength) { m_strength = strength; }

	int GetHp() { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }

	bool m_use() { return m_use; }

protected:
	D3DXVECTOR2 m_pos = {};			//座標
	D3DXVECTOR2 m_size = {};		//大きさ
	float m_rot = {};				//回転角度
	float m_strength = {};			//強度
	int m_hp = {};					//耐久値
	int m_texture = {};				//読み込み画像
	bool m_use = false;				//使用状態


};

void Object::Draw(void)
{
	if (Object::m_use == true)
	{
		DrawSprite(Object::m_texture, Object::m_pos.x, Object::m_pos.y, Object::m_size.x, Object::m_size.y,0.0f, 0.0f, 1.0f, 1.0f);
	}
}



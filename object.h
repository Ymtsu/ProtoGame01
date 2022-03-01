//=============================================================================
//
// �I�u�W�F�N�g���N���X [object.h]
// Author : 
//���΁A�g�~�[
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "texture.h"

//���
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
	
	//�Z�u���X�^�[�A�Q�b�g!!
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
	D3DXVECTOR2 m_pos = {};			//���W
	D3DXVECTOR2 m_size = {};		//�傫��
	float m_rot = {};				//��]�p�x
	float m_strength = {};			//���x
	int m_hp = {};					//�ϋv�l
	int m_texture = {};				//�ǂݍ��݉摜
	bool m_use = false;				//�g�p���


};

void Object::Draw(void)
{
	if (Object::m_use == true)
	{
		DrawSprite(Object::m_texture, Object::m_pos.x, Object::m_pos.y, Object::m_size.x, Object::m_size.y,0.0f, 0.0f, 1.0f, 1.0f);
	}
}



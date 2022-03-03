//===========================
// ==================================================
//
// 樹木クラス [wood.h]
// Author : 
//こば、トミー
//=============================================================================
#pragma once
#include "object.h"

enum class WoodState {
	no_exit,
	stand,
	rotation,
	fallen
};

class Wood : public Object
{
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

class WoodCutLeft : public Object
{
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

class WoodCutRight : public Object
{
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};

class WoodMove : public Object 
{

};
//=============================================================================
//
// 樹木クラス [wood.h]
// Author : 
//こば、トミー
//=============================================================================
#pragma once
#include "object.h"

class Wood : public Object
{
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void);
};

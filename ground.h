// ==================================================
// 地面クラス [wood.h]
// Author : 
//こば
//=============================================================================
#pragma once
#include "object.h"
#include "collision.h"


class Ground : public Object
{
public:
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
};
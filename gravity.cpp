#include "main.h"
#include "gravity.h"
#include "math.h"

float Gravity(D3DXVECTOR2 vector)
{
	float gravity;
	D3DXVECTOR2 object;
	float gravity_velocity = 0.098f;

	gravity = vector.y;
	//前のy座標にyの速度を加算
	object.y += vector.y;

	//現在の速度に加速度(重力)を加算
	gravity += gravity_velocity;

	return gravity;
}
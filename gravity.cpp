#include "main.h"
#include "gravity.h"
#include "math.h"

float Gravity(D3DXVECTOR2 vector)
{
	float gravity;
	D3DXVECTOR2 object;
	float gravity_velocity = 0.098f;

	gravity = vector.y;
	//�O��y���W��y�̑��x�����Z
	object.y += vector.y;

	//���݂̑��x�ɉ����x(�d��)�����Z
	gravity += gravity_velocity;

	return gravity;
}
#include "main.h"
#include "Physics.h"

#define GRAVITATIONAL_ACCELERATION (0.098f * 2)//�d�͉����x�B�ォ�����̂Ŕ{��

float Gravity(float y_vector)
{
	float add_gravity_vector = y_vector - GRAVITATIONAL_ACCELERATION;

	return add_gravity_vector;
}

D3DXVECTOR2 AirResistance(float air_resistance, D3DXVECTOR2 vector)
{
	D3DXVECTOR2 result_vector = {};
	D3DXVECTOR2 air_resist = {}; //��C��R

	//��C��R�͂͋��̔��ł��鑬�x�ɔ�Ⴗ�邽�߁A���̑���*��C��R�萔*-1
	//(�����𔽓]�����闝�R�͔��ł��鑬�x�𗎂Ƃ����߁B)
	air_resist.x = vector.x * -air_resistance;
	air_resist.y = vector.y * -air_resistance;

	result_vector = vector + air_resist;

	return result_vector;
}

D3DXVECTOR2 SingleBounce(float Coefficient_restitution, D3DXVECTOR2 vector)
{
	D3DXVECTOR2 bounce_vector = {};
	bounce_vector.x = vector.x * -Coefficient_restitution;
	bounce_vector.y = vector.y * -Coefficient_restitution;

	return bounce_vector;
}

float Pulley(int weight, int quantity, int power)
{
	float lifting_height = 0.0f;
	lifting_height = power - (weight / quantity);

	return lifting_height;
}



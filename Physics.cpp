#include "main.h"
#include "Physics.h"

#define GRAVITATIONAL_ACCELERATION (0.098f)//�d�͉����x

float Gravity(float y_vector)
{
	float add_gravity_vector = y_vector + GRAVITATIONAL_ACCELERATION;

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

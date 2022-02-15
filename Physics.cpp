#include "main.h"
#include "Physics.h"

#define GRAVITATIONAL_ACCELERATION (0.098f)//重力加速度

float Gravity(float y_vector)
{
    float add_gravity_vector = y_vector + GRAVITATIONAL_ACCELERATION;

    return add_gravity_vector;
}

D3DXVECTOR2 AirResistance(float air_resistance, D3DXVECTOR2 vector)
{
	D3DXVECTOR2 result_vector = {};
	D3DXVECTOR2 air_resist = {}; //空気抵抗

	//空気抵抗力は球の飛んでいる速度に比例するため、球の速さ*空気抵抗定数*-1
	//(符号を反転させる理由は飛んでいる速度を落とすため。)
	air_resist.x = vector.x * -air_resistance;
	air_resist.y = vector.y * -air_resistance;

	result_vector = vector + air_resist;

    return result_vector;
}



#pragma once

float Gravity(float y_vector);//�A�b�v�f�[�g�̃R�[�h�̖����ɋL���B�߂�l�F�d�͉��Z�ς݂̑��x(y�̂�)
D3DXVECTOR2 AirResistance(float air_resistance, D3DXVECTOR2 vector);//�擪�߂��ɋL���B�߂�l�F��C��R�����ς݂̑��x(x,y)
D3DXVECTOR2 SingleBounce(float Coefficient_restitution, D3DXVECTOR2 vector);//���]��������
float Pulley(int weight, int quantity, int power);//�����F�d���A���Ԃ̐��A���������i�`�F�[���\�[�̋����j�@�߂�l�F�����オ�鍂��

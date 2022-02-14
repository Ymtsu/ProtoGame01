//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//�ڂ��͎�p�����HAPPYEND�̎􂢂������܂��B
//=============================================================================
#include "main.h"
#include "collision.h"
//#include "math.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �����蔻�菈��
//=============================================================================
//void UpdateCollision(void)
//{
//
//}

//=============================================================================
//���΂֗̕��c�[��
//=============================================================================
//�x�N�g���̒����̓����o��
float LENGTH(D3DXVECTOR2 vector)
{
	float length;
	length = (vector.x * vector.x) + (vector.y * vector.y);
	return(length);
}

//�x�N�g���̐��K��
D3DXVECTOR2 VECTOR_NORMALIZE(D3DXVECTOR2 vector)
{
	D3DXVECTOR2 vector_normalize;

	vector_normalize.x = (vector.x * vector.x) / LENGTH(vector);
	vector_normalize.y = (vector.y * vector.y) / LENGTH(vector);

	return(vector_normalize);
}

//���ς�2����o��(cos��)^2
float INNER_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B)
{
	float InnerProduct;
	InnerProduct = (vector_A.x * vector_B.x) + (vector_A.y * vector_B.y);
	return(InnerProduct);
}

//�O�ς�2����o��(sin��)^2	(A.x * B.y) - (A.y * B.x)
float CROSS_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B)
{
	float Cross_Product;

	Cross_Product = (vector_A.x * vector_B.y) - (vector_A.y * vector_B.x);

	return(Cross_Product);
}
//=============================================================================


//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// �~�Ɖ~�̓����蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionCC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float radius1, float radius2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	float size = (radius1 + radius2) * (radius1 + radius2);

	//1��2�̔��a�𑫂��Ĕ��肷��
	//�����̃x�N�g�����̕������������
	//�q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �����Ɖ~�̓����蔻��
//=============================================================================
bool CollisionCL(D3DXVECTOR2 circle_pos, D3DXVECTOR2 line_min_pos, D3DXVECTOR2 line_max_pos, float circle_radius)
{
	//�����̍ŏ��_����~�̒��S�_�܂ł̃x�N�g��
	D3DXVECTOR2 min_to_circle = circle_pos - line_min_pos;
	//�����̍ő�_����~�̒��S�_�܂ł̃x�N�g��
	D3DXVECTOR2 max_to_circle = circle_pos - line_max_pos;
	//�����̍ŏ��_����ő�_�܂ł̃x�N�g��
	D3DXVECTOR2 line_vector = line_max_pos - line_min_pos;

	//�����̍ŏ��_����ő�_�܂ł̃x�N�g���𐳋K������
	line_vector = VECTOR_NORMALIZE(line_vector);

	//�����̍ŏ��_����~�̒��S�_�܂ł̃x�N�g���Ɛ����̍ŏ��_����ő�_�܂ł̃x�N�g���̊O��
	float Cross_Product = CROSS_PRODUCT(min_to_circle, line_vector);

	// �����Ɖ~�̍ŒZ�̒��������a�������������A�������Ă���\������
	if (fabsf(Cross_Product) < circle_radius)
	{
		//�����̍ŏ��_����~�̃x�N�g���Ɛ����̓���
		float min_inner_product = INNER_PRODUCT(min_to_circle, line_vector);
		//�����̍ő�_����~�̃x�N�g���Ɛ����̓���
		float max_inner_product = INNER_PRODUCT(max_to_circle, line_vector);

		// ��̓��ς̊|���Z���ʂ�0�ȉ��Ȃ瓖����
		if (min_inner_product * max_inner_product <= 0.0f)
		{
			return true;
		}
		//�n�_����~�̒��S�̒����̓�悩�A�I�_����~�̒��S�̒����̓�悪�A�~�̔��a�̓������Z�������瓖����
		if (LENGTH(min_to_circle) < powf(circle_radius,2.0f) || LENGTH(max_to_circle) < powf(circle_radius, 2.0f))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
//�u���b�N���猩���Փ˂����ʂ�Ԃ�
// ������old_pos�̓u���b�N�������Ȃ����pos��OK
//=============================================================================
F_OLD_SURFACE CollisionBB_SURFACE(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size)
{

	D3DXVECTOR2 player_min, player_max;
	D3DXVECTOR2 block_min, block_max;
	D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;


	player_min.x = player_pos.x - player_size.x / 2;
	player_min.y = player_pos.y - player_size.y / 2;
	player_max.x = player_pos.x + player_size.x / 2;
	player_max.y = player_pos.y + player_size.y / 2;

	block_min.x = block_pos.x - block_size.x / 2;
	block_min.y = block_pos.y - block_size.y / 2;
	block_max.x = block_pos.x + block_size.x / 2;
	block_max.y = block_pos.y + block_size.y / 2;

	//�v���C���[�̉��z�����x
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;




	//X���̔���
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y���̔���
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//�v���C���[���u���b�N�̏ォ�瓖�������Ƃ�
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::up;
			}
			//�v���C���[���u���b�N�̉����瓖�������Ƃ�
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//�v���C���[���u���b�N�̍����瓖�������Ƃ�
			if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::left;
			}
			//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
			if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::right;
			}

			//�v���C���[�̉����x�̉��z�p�x
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);

			//�v���C���[�̒��_����u���b�N�̒��_�����񂾒����̊p�x
			//�v���C���[���獶��
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//�v���C���[���獶��
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//�v���C���[����E��
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//�v���C���[����E��
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//�u���b�N����E��̔���
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
				if (vertual_velocity_angle > LeftDown_angle)
				{
					//��
					return F_OLD_SURFACE::up;
				}
				else
				{
					//�E
					return F_OLD_SURFACE::right;
				}
			}

			//�u���b�N����E���̔���
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (vertual_velocity_angle > LeftUp_angle)
				{
					//�E
					return F_OLD_SURFACE::right;
				}
				else
				{
					//��
					return F_OLD_SURFACE::down;
				}
			}

			//�u���b�N���獶��̔���
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				if (vertual_velocity_angle > RightDown_angle)
				{
					//��
					return F_OLD_SURFACE::left;
				}
				else
				{
					//��
					return F_OLD_SURFACE::up;
				}
			}

			//�u���b�N���獶���̔���
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				if (vertual_velocity_angle > RightUp_angle)
				{
					//��
					return F_OLD_SURFACE::down;
				}
				else
				{
					//��
					return F_OLD_SURFACE::left;
				}
			}
		}
	}
	return F_OLD_SURFACE::no_hit;

}

//========================================================================================
// �u���b�N��X��Y�̒l�����s�ȂƂ��u���b�N�ƃ{�[���̗\����_���W���瓖�����Ă��邩���肷��
//========================================================================================
bool CollisionPIS_UP(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W(x)
	float predict_ball_to_inter_section_x;

	//�u���b�N
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_up_y = block_pos.y - (block_size.y / 2);

	//�{�[��
	float ball_old_down = ball_old_pos.y + (ball_size.y / 2);
	float ball_down = ball_pos.y + (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Y�̍��W�̕ω���
	S = block_up_y - ball_down;
	//Y�̍��W�̕ω�������݂�X�̗\�z��_���W
	predict_ball_to_inter_section_x = ball_old_pos.x + (ball_velocity.x * S);
	//�\�z��_���W���u���b�N�̍��[����E�[�̓����ɂ��鎞
	if ((predict_ball_to_inter_section_x < x_max) || (predict_ball_to_inter_section_x > x_min))
	{
		//�{�[����old_pos��pos���q�������ƃu���b�N�̏�ʂ��������Ă���Ƃ�
		if (block_up_y > ball_old_down && block_up_y < ball_down)
		{
			return true;
		}
	}
	return false;
}

bool CollisionPIS_DOWN(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W(x)
	float predict_ball_to_inter_section_x;

	//�u���b�N
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_down_y = block_pos.y + (block_size.y / 2);

	//�{�[��
	float ball_up = ball_pos.y - (ball_size.y / 2);
	float ball_old_up = ball_old_pos.y - (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;


	//Y�̍��W�̕ω���
	S = block_down_y - ball_up;
	//Y�̍��W�̕ω�������݂�X�̗\�z��_���W
	predict_ball_to_inter_section_x = ball_old_pos.x + (ball_velocity.x * S);
	//�\�z��_���W���u���b�N�̍��[����E�[�̓����ɂ��鎞
	if ((predict_ball_to_inter_section_x< x_max) || (predict_ball_to_inter_section_x > x_min))
	{
		//�{�[����old_pos��pos���q�������ƃu���b�N�̉��ʂ��������Ă���Ƃ�
		if (block_down_y < ball_old_up && block_down_y > ball_up)
		{
			return true;
		}
	}
	return false;
}

bool CollisionPIS_RIGHT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W(y)
	float predict_ball_to_inter_section_y;

	//�u���b�N
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_right_x = block_pos.x + (block_size.x / 2);

	//�{�[��
	float ball_old_left = ball_old_pos.x - (ball_size.x / 2);
	float ball_left = ball_pos.x - (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//X�̍��W�̕ω���
	S = block_right_x - ball_left;
	//X�̍��W�̕ω�������݂�Y�̗\�z��_���W
	predict_ball_to_inter_section_y = ball_old_pos.y + (ball_velocity.y * S);
	//�\�z��_���W���u���b�N�̏�[���牺�[�̓����ɂ��鎞
	if ((predict_ball_to_inter_section_y > y_max) || (predict_ball_to_inter_section_y < y_min))
	{
		//�{�[����old_pos��pos���q�������ƃu���b�N�̉E�ʂ��������Ă���Ƃ�
		if (block_right_x < ball_old_left && block_right_x > ball_left)
		{
			return true;
		}
	}

	return false;
}

bool CollisionPIS_LEFT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W(y)
	float predict_ball_to_inter_section_y;

	//�u���b�N
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_left_x = block_pos.x - (block_size.x / 2);

	//�{�[��
	float ball_old_right = ball_old_pos.x + (ball_size.x / 2);
	float ball_right = ball_pos.x + (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//X�̍��W�̕ω���
	S = block_left_x - ball_right;
	//X�̍��W�̕ω�������݂�Y�̗\�z��_���W
	predict_ball_to_inter_section_y = ball_old_pos.y + (ball_velocity.y * S);
	//�\�z��_���W���u���b�N�̏�[���牺�[�̓����ɂ��鎞
	if ((predict_ball_to_inter_section_y < y_max) || (predict_ball_to_inter_section_y > y_min))
	{
		//�{�[����old_pos��pos���q�������ƃu���b�N�̍��ʂ��������Ă���Ƃ�
		if (block_left_x > ball_old_right && block_left_x < ball_right)
		{
			return true;
		}
	}
	return false;
}


//=========================================================================================
// �u���b�N��X��Y�̒l�����s�ȂƂ��u���b�N�ƃ{�[���̗\����_���W���瓖�����Ă�����W�����߂�
//=========================================================================================
D3DXVECTOR2 CollisionPIS_UP_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W
	D3DXVECTOR2 predict_ball_to_inter_section;

	//�u���b�N
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_up_y = block_pos.y - (block_size.y / 2);

	//�{�[��
	float ball_old_down = ball_old_pos.y + (ball_size.y / 2);
	float ball_down = ball_pos.y + (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Y�̍��W�̕ω���
	S = block_up_y - ball_down;
	//Y�̍��W�̕ω�������݂�X�̗\�z��_���W
	predict_ball_to_inter_section.x = ball_old_pos.x + (ball_velocity.x * S);
	//��_��Y���W
	predict_ball_to_inter_section.y = block_up_y;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_DOWN_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W
	D3DXVECTOR2 predict_ball_to_inter_section;

	//�u���b�N
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_down_y = block_pos.y + (block_size.y / 2);

	//�{�[��
	float ball_up = ball_pos.y - (ball_size.y / 2);
	float ball_old_up = ball_old_pos.y - (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;


	//Y�̍��W�̕ω���
	S = block_down_y - ball_up;
	//Y�̍��W�̕ω�������݂�X�̗\�z��_���W
	predict_ball_to_inter_section.x = ball_old_pos.x + (ball_velocity.x * S);
	//��_��Y���W
	predict_ball_to_inter_section.y = block_down_y;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_RIGHT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W
	D3DXVECTOR2 predict_ball_to_inter_section;

	//�u���b�N
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_right_x = block_pos.x + (block_size.x / 2);

	//�{�[��
	float ball_old_left = ball_old_pos.x - (ball_size.x / 2);
	float ball_left = ball_pos.x - (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//X�̍��W�̕ω���
	S = block_right_x - ball_left;
	//X�̍��W�̕ω�������݂�Y�̗\�z��_���W
	predict_ball_to_inter_section.y = ball_old_pos.y + (ball_velocity.y * S);
	//��_��X���W
	predict_ball_to_inter_section.y = block_right_x;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_LEFT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//�}��ϐ�
	float S;
	//�{�[���ƃu���b�N�̗\�z��_���W
	D3DXVECTOR2 predict_ball_to_inter_section;

	//�u���b�N
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_left_x = block_pos.x - (block_size.x / 2);

	//�{�[��
	float ball_old_right = ball_old_pos.x + (ball_size.x / 2);
	float ball_right = ball_pos.x + (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//X�̍��W�̕ω���
	S = block_left_x - ball_right;
	//X�̍��W�̕ω�������݂�Y�̗\�z��_���W
	predict_ball_to_inter_section.y = ball_old_pos.y + (ball_velocity.y * S);
	//��_��X���W
	predict_ball_to_inter_section.y = block_left_x;

	return (predict_ball_to_inter_section);
}


//=============================================================================
//�u���b�N�̂ǂ̖ʂɓ����邩��\�����遖�S���̃u���b�N�Ɣ��肷��̂ŗv���P
//=============================================================================
F_OLD_SURFACE PREDICT_SURFACE(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size)
{

	D3DXVECTOR2 player_min, player_max;
	D3DXVECTOR2 block_min, block_max;
	D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;


	player_min.x = player_pos.x - player_size.x / 2;
	player_min.y = player_pos.y - player_size.y / 2;
	player_max.x = player_pos.x + player_size.x / 2;
	player_max.y = player_pos.y + player_size.y / 2;

	block_min.x = block_pos.x - block_size.x / 2;
	block_min.y = block_pos.y - block_size.y / 2;
	block_max.x = block_pos.x + block_size.x / 2;
	block_max.y = block_pos.y + block_size.y / 2;

	//�v���C���[�̉��z�����x
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;

	
	//�v���C���[���u���b�N�̏ォ�瓖�������Ƃ�
	if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
{
	return F_OLD_SURFACE::up;
}
	//�v���C���[���u���b�N�̉����瓖�������Ƃ�
	if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
{
	return F_OLD_SURFACE::down;
}
	//�v���C���[���u���b�N�̍����瓖�������Ƃ�
	if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
{
	return F_OLD_SURFACE::left;
}
	//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
	if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
{
	return F_OLD_SURFACE::right;
}
	
	//�v���C���[�̉����x�̉��z�p�x
	float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);
	
	//�v���C���[�̒��_����u���b�N�̒��_�����񂾒����̊p�x
	//�v���C���[���獶��
	float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
	//�v���C���[���獶��
	float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
	//�v���C���[����E��
	float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
	//�v���C���[����E��
	float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));
	
	//�u���b�N����E��̔���
	if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
{
	if (vertual_velocity_angle > LeftDown_angle)
	{
		//��
		return F_OLD_SURFACE::up;
	}
	else
	{
		//�E
		return F_OLD_SURFACE::right;
	}
}
	
	//�u���b�N����E���̔���
	if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
	{
		if (vertual_velocity_angle > LeftUp_angle)
	{
		//�E
		return F_OLD_SURFACE::right;
	}
		else
	{
		//��
		return F_OLD_SURFACE::down;
	}
	}
	
	//�u���b�N���獶��̔���
	if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
{
	if (vertual_velocity_angle > RightDown_angle)
	{
		//��
		return F_OLD_SURFACE::left;
	}
	else
	{
		//��
		return F_OLD_SURFACE::up;
	}
}
	
	//�u���b�N���獶���̔���
	if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
{
	if (vertual_velocity_angle > RightUp_angle)
	{
		//��
		return F_OLD_SURFACE::down;
	}
	else
	{
		//��
		return F_OLD_SURFACE::left;
	}
}
	
		return F_OLD_SURFACE::no_hit;

}

//=============================================================================
//�~�Ɖ�]���Ă���u���b�N�̓����蔻��
//=============================================================================
bool CollisionCRB(D3DXVECTOR2 circle_pos, D3DXVECTOR2 block_pos, float circle_radius, D3DXVECTOR2 block_size, float block_rot)
{
	//�{�[���ƃu���b�N�����񂾃x�N�g��
	D3DXVECTOR2 circle_block_vector = circle_pos - block_pos;
	//�{�[���ƃu���b�N�����񂾃x�N�g���̒���
	float circle_block_vector_length = sqrtf(LENGTH(circle_block_vector));
	//�{�[���̔��a�ƃu���b�N�̒��S�_���璸�_�܂ł̒����𑫂������2��
	float radius_plus_size_length = LENGTH(D3DXVECTOR2(block_size.x + circle_radius, block_size.y + circle_radius));

	//�{�[���ƃu���b�N�����񂾃x�N�g���̊p�x
	float circle_block_vector_angle = atan2f(circle_block_vector.y, circle_block_vector.x);
	//�{�[���̉��z�p�x
	float virtual_ball_angle = circle_block_vector_angle - block_rot;
	//�{�[���ƃu���b�N�����񂾉��z�x�N�g��
	D3DXVECTOR2 virtual_ball_vector;
	virtual_ball_vector.x = circle_block_vector_length * cosf(virtual_ball_angle);
	virtual_ball_vector.y = circle_block_vector_length * sinf(virtual_ball_angle);
	//�{�[���̉��z���W
	D3DXVECTOR2 virtual_ball_pos = block_pos + virtual_ball_vector;
	//�{�[���ƃu���b�N�����񂾉��z�x�N�g����2��
	float virtual_ball_vector_length = LENGTH(virtual_ball_vector);

	//�{�[���̔��a�ƃu���b�N�̒��S�_���璸�_�܂ł̒����𑫂������2����
	//�{�[���ƃu���b�N�����񂾉��z�x�N�g����2�悪�Z��������
	if (radius_plus_size_length >= virtual_ball_vector_length)
	{
		//���z�̈�̒��_���W
		float virtual_area_min_x = block_pos.x - powf((block_size.x / 2) + circle_radius, 2.0f);
		float virtual_area_min_y = block_pos.y - powf((block_size.y / 2) + circle_radius, 2.0f);
		float virtual_area_max_x = block_pos.x + powf((block_size.x / 2) + circle_radius, 2.0f);
		float virtual_area_max_y = block_pos.y + powf((block_size.y / 2) + circle_radius, 2.0f);
		//�u���b�N�̒��_���W
		float block_min_x = block_pos.x - block_size.x / 2;
		float block_min_y = block_pos.y - block_size.y / 2;
		float block_max_x = block_pos.x + block_size.x / 2;
		float block_max_y = block_pos.y + block_size.y / 2;

		//�c���̉��z�̈�
		if (block_min_x < virtual_ball_pos.x && virtual_ball_pos.x > block_max_x)
		{
			if (virtual_area_min_y < virtual_ball_pos.y && virtual_ball_pos.y > virtual_area_max_y)
			{
				return true;
			}
		}
		//�����̉��z�̈�
		if (virtual_area_min_x < virtual_ball_pos.x && virtual_ball_pos.x > virtual_area_max_x)
		{
			if (block_min_y < virtual_ball_pos.y && virtual_ball_pos.y > block_max_y)
			{
				return true;
			}
		}

		//�e���_����{�[���܂ł̒����Ɖ~�̔��a�𑫂������2��
		//����
		float left_up_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_min_x, virtual_ball_pos.y - block_max_y));
		//����
		float left_down_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_min_x, virtual_ball_pos.y - block_min_y));
		//�E��
		float right_up_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_max_x, virtual_ball_pos.y - block_min_y));
		//�E��
		float right_down_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_max_x, virtual_ball_pos.y - block_max_y));
		
		//���a��2��
		float radius_square = powf(circle_radius, 2.0f);

		// �e���_����{�[���܂ł̒����Ɖ~�̔��a�𑫂������2��Ɣ��a��2��̔�r
		//����
		if (radius_square > left_up_to_ball_length)
		{
			return true;
		 }
		//����
		if (radius_square > left_down_to_ball_length)
		{
			return true;
		}
		//�E��
		if (radius_square > right_up_to_ball_length)
		{
			return true;
		}
		//�E��
		if (radius_square > right_down_to_ball_length)
		{
			return true;
		}
	}

	return false;
}


//=============================================================================
//�l�p�`�̉�]��̒��_���W
//=============================================================================
SQUARE_VERTEX SquareVertexPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, float block_rot)
{
	SQUARE_VERTEX Square_Vertex_Pos;

	//�c�A���̒����̔���
	float half_width, half_height;
	half_width = block_size.x / 2;
	half_height = block_size.y / 2;

	// ���S�_���璸�_�ɑ΂���p�x
	float BaseAngle = atan2f(half_height, half_width);
	// ���S�_���璸�_�ɑ΂��鋗��
	float Radius = sqrtf(LENGTH(D3DXVECTOR2(half_width, half_height)));

	//����̍��W
	float x = block_pos.x - cosf(BaseAngle + block_rot) * Radius;
	float y = block_pos.y - sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.left_up = D3DXVECTOR2(x, y);
	//�E��̍��W
	x = block_pos.x + cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y - sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.right_up = D3DXVECTOR2(x, y);
	//�����̍��W
	x = block_pos.x - cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.left_down = D3DXVECTOR2(x, y);
	//�E���̍��W
	x = block_pos.x + cosf(BaseAngle + block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.right_down = D3DXVECTOR2(x, y);


	return(Square_Vertex_Pos);
}

//=============================================================================
//�v���C���[�̑傫���ɍ��킹�čL�����l�p�`�̉�]��̒��_���W
//=============================================================================
SQUARE_VERTEX SquareVertexPlusPlayerPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, D3DXVECTOR2 player_size, float block_rot)
{
	SQUARE_VERTEX Square_Vertex_Pos;

	//�c�A���̒����̔���
	float half_width, half_height;
	half_width = (player_size.x + block_size.x) / 2;
	half_height = (player_size.y + block_size.y) / 2;

	// ���S�_���璸�_�ɑ΂���p�x
	float BaseAngle = atan2f(half_height, half_width);
	// ���S�_���璸�_�ɑ΂��鋗��
	float Radius = sqrtf(LENGTH(D3DXVECTOR2(half_width, half_height)));

	//����̍��W
	float x = block_pos.x - cosf(BaseAngle + block_rot) * Radius;
	float y = block_pos.y - sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.left_up = D3DXVECTOR2(x, y);
	//�E��̍��W
	x = block_pos.x + cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y - sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.right_up = D3DXVECTOR2(x, y);
	//�����̍��W
	x = block_pos.x - cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.left_down = D3DXVECTOR2(x, y);
	//�E���̍��W
	x = block_pos.x + cosf(BaseAngle + block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.right_down = D3DXVECTOR2(x, y);


	return(Square_Vertex_Pos);
}

bool CollisionConvexPoint(D3DXVECTOR2* block_vertex_pos, D3DXVECTOR2 player_center_pos, int vertex_num)
{
	float unit = 1.0f / 360.0f;
	float result = 0.0f;

	D3DXVECTOR2 normal_vector = block_vertex_pos[0] - player_center_pos;

	for (int i = 0; i < vertex_num; i++)
	{
		D3DXVECTOR2 L1 = block_vertex_pos[i] - player_center_pos;
		D3DXVECTOR2 L2 = block_vertex_pos[(i + 1) % vertex_num] - player_center_pos;

		float angle = atan2f(L1.y, L2.x);

		float cross = CROSS_PRODUCT(L1, L2);

		if (INNER_PRODUCT(D3DXVECTOR2(cross, 0.0f), normal_vector) < 0)
		{
			angle *= -1;
		}

		result += angle;
	}

	result *= unit;

	return (fabs(result) >= 0.01f);
}
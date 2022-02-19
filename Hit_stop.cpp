#include "main.h"
#include "collision.h"

//============================================================================================================================
//�q�b�g�X�g�b�v(�b���Ǘ�)
// �����F���݂̎���,�q�b�g�X�g�b�v���n�܂鎞��,�q�b�g�X�g�b�v���I��鎞��,�ǂ̂��炢�̒x���ɂȂ邩�̕ω���(0.0�`1.0),��������
//============================================================================================================================
float HitStop(float now_time, float start_time, float finish_time, float rate_of_change,float total_time)
{
    if (now_time < start_time) { return now_time; }

    if (start_time <= now_time && now_time <= finish_time)
    {
        return rate_of_change * (now_time - start_time) + start_time; 
    }

    return ((total_time - rate_of_change * (finish_time - start_time) - start_time)
        / (total_time - finish_time)) * (now_time - finish_time) + (rate_of_change * (finish_time - start_time) + start_time);
}

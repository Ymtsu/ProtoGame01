#include "main.h"
#include "collision.h"

//=======================================================================================================================
//ヒットストップ(MHW参考)
// 引数：現在の時間,ヒットストップが始まる時間,ヒットストップが終わる時間,どのくらいの遅さになるかの変化率(0.0～1.0)
//=======================================================================================================================
float HitStop(float now_time, float start_time, float finish_time, float rate_of_change) 
{
    if (now_time < start_time) { return now_time; }
    if (start_time <= now_time && now_time <= finish_time) { return rate_of_change * (now_time - start_time) + start_time; }
    return ((1.0f - rate_of_change * (finish_time - start_time) - start_time) 
        / (1.0f - finish_time)) * (now_time - finish_time) + (rate_of_change * (finish_time - start_time) + start_time);
}
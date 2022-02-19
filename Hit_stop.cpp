#include "main.h"
#include "collision.h"

//============================================================================================================================
//ヒットストップ(秒数管理)
// 引数：現在の時間,ヒットストップが始まる時間,ヒットストップが終わる時間,どのくらいの遅さになるかの変化率(0.0～1.0),処理時間
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

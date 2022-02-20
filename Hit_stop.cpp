#include "main.h"
#include "collision.h"

//============================================================================================================================
//ヒットストップ(秒数管理)
// 引数：現在の時間,ヒットストップが始まる時間,ヒットストップが終わる時間,どのくらいの遅さになるかの変化率(0～10),処理時間
//============================================================================================================================
int HitStop(int now_time, int start_time, int finish_time, int rate_of_change)
{
    if (now_time < start_time) 
    { 
        return now_time;
    }

    if (start_time <= now_time && now_time <= finish_time)
    {
        return rate_of_change * (now_time - start_time) + start_time; 
    }

    return ((60 - rate_of_change * (finish_time - start_time) - start_time)
        / (60 - finish_time)) * (now_time - finish_time) + (rate_of_change * (finish_time - start_time) + start_time);
}

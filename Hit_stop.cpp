#include "main.h"
#include "collision.h"
#include "Hit_stop.h"

static int g_frame;
static bool g_flag = false;

//============================================================================================================================
//ヒットストップ(フレーム管理)　(変更しないと使えません)
// 引数：現在の時間,ヒットストップが始まる時間,ヒットストップが終わる時間,どのくらいの遅さになるかの変化率(0～10)
//戻り値：現在のアニメーション（60枚アニメーション前提）
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

//============================================================================================================================
//ヒットストップ(ラジアン管理)
// 引数：現在の角度,ヒットストップが始まる角度,ヒットストップが終わる角度,どのくらいの遅さになるかの変化率(0～1)
//戻り値：現在の角度
//============================================================================================================================
float HitStop_angle(float now_angle, float start_angle, float finish_angle, float rate_of_change)
{
    if (now_angle < start_angle)
    {
        return now_angle;
    }

    if (start_angle <= now_angle && now_angle <= finish_angle)
    {
        return rate_of_change * (now_angle - start_angle) + start_angle;
    }

    return ((PI - rate_of_change * (finish_angle - start_angle) - start_angle)
        / (PI - finish_angle)) * (now_angle - finish_angle) + (rate_of_change * (finish_angle - start_angle) + start_angle);
}

float Hitstop_test(float add_angle, float now_angle, float finish_angle, float rate_of_change)
{
    float result_add_angle = 0.0f;

    if (now_angle <= finish_angle && !g_flag)
    {
        result_add_angle = add_angle * rate_of_change;
        g_frame++;
    }

    if (g_frame >= 10 || g_flag)
    {
        result_add_angle = (add_angle - result_add_angle) + add_angle;
        g_frame = 0;
        g_flag = true;
    }

    return result_add_angle;
}

void SetFlag()
{
    g_flag = false;
}

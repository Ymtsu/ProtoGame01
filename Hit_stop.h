#pragma once
#include "main.h"
#include "collision.h"

//引数：現在の時間, ヒットストップが始まる時間(基本0。内部の硬さが違う場合使用), 
// 　　 ヒットストップが終わる時間, どのくらいの遅さになるかの変化率(0～10)
//戻り値：現在のアニメーション（60枚アニメーション前提）
int HitStop(int now_time, int start_time, int finish_time, int rate_of_change);
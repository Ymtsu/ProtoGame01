#pragma once

float Gravity(float y_vector);//アップデートのコードの末尾に記入。戻り値：重力加算済みの速度(yのみ)
D3DXVECTOR2 AirResistance(float air_resistance, D3DXVECTOR2 vector);//先頭近くに記入。戻り値：空気抵抗処理済みの速度(x,y)
D3DXVECTOR2 SingleBounce(float Coefficient_restitution, D3DXVECTOR2 vector);//反転処理込み
float Pulley(int weight, int quantity, int power);//引数：重さ、滑車の数、引く強さ（チェーンソーの強さ）　戻り値：持ち上がる高さ

//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//ぼくは呪術高専でHAPPYENDの呪いを解きます。
//=============================================================================
#include "main.h"
#include "collision.h"
//#include "math.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 当たり判定処理
//=============================================================================
//void UpdateCollision(void)
//{
//
//}

//=============================================================================
//こばの便利ツール
//=============================================================================
//ベクトルの長さの二乗を出す
float LENGTH(D3DXVECTOR2 vector)
{
	float length;
	length = (vector.x * vector.x) + (vector.y * vector.y);
	return(length);
}

//ベクトルの正規化
D3DXVECTOR2 VECTOR_NORMALIZE(D3DXVECTOR2 vector)
{
	D3DXVECTOR2 vector_normalize;

	vector_normalize.x = (vector.x * vector.x) / LENGTH(vector);
	vector_normalize.y = (vector.y * vector.y) / LENGTH(vector);

	return(vector_normalize);
}

//内積の2乗を出す(cosθ)^2
float INNER_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B)
{
	float InnerProduct;
	InnerProduct = (vector_A.x * vector_B.x) + (vector_A.y * vector_B.y);
	return(InnerProduct);
}

//外積の2乗を出す(sinθ)^2	(A.x * B.y) - (A.y * B.x)
float CROSS_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B)
{
	float Cross_Product;

	Cross_Product = (vector_A.x * vector_B.y) - (vector_A.y * vector_B.x);

	return(Cross_Product);
}
//=============================================================================


//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
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

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}

//=============================================================================
// 円と円の当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionCC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float radius1, float radius2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長を得る
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	float size = (radius1 + radius2) * (radius1 + radius2);

	//1と2の半径を足して判定する
	//差分のベクトル長の方が小さければ
	//ヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// 線分と円の当たり判定
//=============================================================================
bool CollisionCL(D3DXVECTOR2 circle_pos, D3DXVECTOR2 line_min_pos, D3DXVECTOR2 line_max_pos, float circle_radius)
{
	//線分の最小点から円の中心点までのベクトル
	D3DXVECTOR2 min_to_circle = circle_pos - line_min_pos;
	//線分の最大点から円の中心点までのベクトル
	D3DXVECTOR2 max_to_circle = circle_pos - line_max_pos;
	//線分の最小点から最大点までのベクトル
	D3DXVECTOR2 line_vector = line_max_pos - line_min_pos;

	//線分の最小点から最大点までのベクトルを正規化する
	line_vector = VECTOR_NORMALIZE(line_vector);

	//線分の最小点から円の中心点までのベクトルと線分の最小点から最大点までのベクトルの外積
	float Cross_Product = CROSS_PRODUCT(min_to_circle, line_vector);

	// 線分と円の最短の長さが半径よりも小さい時、当たっている可能性あり
	if (fabsf(Cross_Product) < circle_radius)
	{
		//線分の最小点から円のベクトルと線分の内積
		float min_inner_product = INNER_PRODUCT(min_to_circle, line_vector);
		//線分の最大点から円のベクトルと線分の内積
		float max_inner_product = INNER_PRODUCT(max_to_circle, line_vector);

		// 二つの内積の掛け算結果が0以下なら当たり
		if (min_inner_product * max_inner_product <= 0.0f)
		{
			return true;
		}
		//始点から円の中心の長さの二乗か、終点から円の中心の長さの二乗が、円の半径の二乗よりも短かったら当たり
		if (LENGTH(min_to_circle) < powf(circle_radius,2.0f) || LENGTH(max_to_circle) < powf(circle_radius, 2.0f))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// BBによる当たり判定処理
//ブロックから見た衝突した面を返す
// 引数のold_posはブロックが動かなければposでOK
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

	//プレイヤーの仮想加速度
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;




	//X軸の判定
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y軸の判定
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//プレイヤーがブロックの上から当たったとき
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::up;
			}
			//プレイヤーがブロックの下から当たったとき
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//プレイヤーがブロックの左から当たったとき
			if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::left;
			}
			//プレイヤーがブロックの右から当たったとき
			if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::right;
			}

			//プレイヤーの加速度の仮想角度
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);

			//プレイヤーの頂点からブロックの頂点を結んだ直線の角度
			//プレイヤーから左下
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//プレイヤーから左上
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//プレイヤーから右下
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//プレイヤーから右上
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//ブロックから右上の判定
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
				if (vertual_velocity_angle > LeftDown_angle)
				{
					//上
					return F_OLD_SURFACE::up;
				}
				else
				{
					//右
					return F_OLD_SURFACE::right;
				}
			}

			//ブロックから右下の判定
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (vertual_velocity_angle > LeftUp_angle)
				{
					//右
					return F_OLD_SURFACE::right;
				}
				else
				{
					//下
					return F_OLD_SURFACE::down;
				}
			}

			//ブロックから左上の判定
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				if (vertual_velocity_angle > RightDown_angle)
				{
					//左
					return F_OLD_SURFACE::left;
				}
				else
				{
					//上
					return F_OLD_SURFACE::up;
				}
			}

			//ブロックから左下の判定
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				if (vertual_velocity_angle > RightUp_angle)
				{
					//下
					return F_OLD_SURFACE::down;
				}
				else
				{
					//左
					return F_OLD_SURFACE::left;
				}
			}
		}
	}
	return F_OLD_SURFACE::no_hit;

}

//========================================================================================
// ブロックのXかYの値が平行なときブロックとボールの予測交点座標から当たっているか判定する
//========================================================================================
bool CollisionPIS_UP(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標(x)
	float predict_ball_to_inter_section_x;

	//ブロック
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_up_y = block_pos.y - (block_size.y / 2);

	//ボール
	float ball_old_down = ball_old_pos.y + (ball_size.y / 2);
	float ball_down = ball_pos.y + (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Yの座標の変化率
	S = block_up_y - ball_down;
	//Yの座標の変化率からみたXの予想交点座標
	predict_ball_to_inter_section_x = ball_old_pos.x + (ball_velocity.x * S);
	//予想交点座標がブロックの左端から右端の内側にある時
	if ((predict_ball_to_inter_section_x < x_max) || (predict_ball_to_inter_section_x > x_min))
	{
		//ボールのold_posとposを繋いだ線とブロックの上面が交差しているとき
		if (block_up_y > ball_old_down && block_up_y < ball_down)
		{
			return true;
		}
	}
	return false;
}

bool CollisionPIS_DOWN(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標(x)
	float predict_ball_to_inter_section_x;

	//ブロック
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_down_y = block_pos.y + (block_size.y / 2);

	//ボール
	float ball_up = ball_pos.y - (ball_size.y / 2);
	float ball_old_up = ball_old_pos.y - (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;


	//Yの座標の変化率
	S = block_down_y - ball_up;
	//Yの座標の変化率からみたXの予想交点座標
	predict_ball_to_inter_section_x = ball_old_pos.x + (ball_velocity.x * S);
	//予想交点座標がブロックの左端から右端の内側にある時
	if ((predict_ball_to_inter_section_x< x_max) || (predict_ball_to_inter_section_x > x_min))
	{
		//ボールのold_posとposを繋いだ線とブロックの下面が交差しているとき
		if (block_down_y < ball_old_up && block_down_y > ball_up)
		{
			return true;
		}
	}
	return false;
}

bool CollisionPIS_RIGHT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標(y)
	float predict_ball_to_inter_section_y;

	//ブロック
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_right_x = block_pos.x + (block_size.x / 2);

	//ボール
	float ball_old_left = ball_old_pos.x - (ball_size.x / 2);
	float ball_left = ball_pos.x - (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Xの座標の変化率
	S = block_right_x - ball_left;
	//Xの座標の変化率からみたYの予想交点座標
	predict_ball_to_inter_section_y = ball_old_pos.y + (ball_velocity.y * S);
	//予想交点座標がブロックの上端から下端の内側にある時
	if ((predict_ball_to_inter_section_y > y_max) || (predict_ball_to_inter_section_y < y_min))
	{
		//ボールのold_posとposを繋いだ線とブロックの右面が交差しているとき
		if (block_right_x < ball_old_left && block_right_x > ball_left)
		{
			return true;
		}
	}

	return false;
}

bool CollisionPIS_LEFT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標(y)
	float predict_ball_to_inter_section_y;

	//ブロック
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_left_x = block_pos.x - (block_size.x / 2);

	//ボール
	float ball_old_right = ball_old_pos.x + (ball_size.x / 2);
	float ball_right = ball_pos.x + (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Xの座標の変化率
	S = block_left_x - ball_right;
	//Xの座標の変化率からみたYの予想交点座標
	predict_ball_to_inter_section_y = ball_old_pos.y + (ball_velocity.y * S);
	//予想交点座標がブロックの上端から下端の内側にある時
	if ((predict_ball_to_inter_section_y < y_max) || (predict_ball_to_inter_section_y > y_min))
	{
		//ボールのold_posとposを繋いだ線とブロックの左面が交差しているとき
		if (block_left_x > ball_old_right && block_left_x < ball_right)
		{
			return true;
		}
	}
	return false;
}


//=========================================================================================
// ブロックのXかYの値が平行なときブロックとボールの予測交点座標から当たっている座標を求める
//=========================================================================================
D3DXVECTOR2 CollisionPIS_UP_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標
	D3DXVECTOR2 predict_ball_to_inter_section;

	//ブロック
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_up_y = block_pos.y - (block_size.y / 2);

	//ボール
	float ball_old_down = ball_old_pos.y + (ball_size.y / 2);
	float ball_down = ball_pos.y + (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Yの座標の変化率
	S = block_up_y - ball_down;
	//Yの座標の変化率からみたXの予想交点座標
	predict_ball_to_inter_section.x = ball_old_pos.x + (ball_velocity.x * S);
	//交点のY座標
	predict_ball_to_inter_section.y = block_up_y;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_DOWN_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標
	D3DXVECTOR2 predict_ball_to_inter_section;

	//ブロック
	float x_min = block_pos.x - (block_size.x / 2);
	float x_max = block_pos.x + (block_size.x / 2);
	float block_down_y = block_pos.y + (block_size.y / 2);

	//ボール
	float ball_up = ball_pos.y - (ball_size.y / 2);
	float ball_old_up = ball_old_pos.y - (ball_size.y / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;


	//Yの座標の変化率
	S = block_down_y - ball_up;
	//Yの座標の変化率からみたXの予想交点座標
	predict_ball_to_inter_section.x = ball_old_pos.x + (ball_velocity.x * S);
	//交点のY座標
	predict_ball_to_inter_section.y = block_down_y;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_RIGHT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標
	D3DXVECTOR2 predict_ball_to_inter_section;

	//ブロック
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_right_x = block_pos.x + (block_size.x / 2);

	//ボール
	float ball_old_left = ball_old_pos.x - (ball_size.x / 2);
	float ball_left = ball_pos.x - (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Xの座標の変化率
	S = block_right_x - ball_left;
	//Xの座標の変化率からみたYの予想交点座標
	predict_ball_to_inter_section.y = ball_old_pos.y + (ball_velocity.y * S);
	//交点のX座標
	predict_ball_to_inter_section.y = block_right_x;

	return (predict_ball_to_inter_section);
}

D3DXVECTOR2 CollisionPIS_LEFT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size)
{
	//媒介変数
	float S;
	//ボールとブロックの予想交点座標
	D3DXVECTOR2 predict_ball_to_inter_section;

	//ブロック
	float y_min = block_pos.y - (block_size.y / 2);
	float y_max = block_pos.y + (block_size.y / 2);
	float block_left_x = block_pos.x - (block_size.x / 2);

	//ボール
	float ball_old_right = ball_old_pos.x + (ball_size.x / 2);
	float ball_right = ball_pos.x + (ball_size.x / 2);
	D3DXVECTOR2 ball_velocity = ball_pos - ball_old_pos;

	//Xの座標の変化率
	S = block_left_x - ball_right;
	//Xの座標の変化率からみたYの予想交点座標
	predict_ball_to_inter_section.y = ball_old_pos.y + (ball_velocity.y * S);
	//交点のX座標
	predict_ball_to_inter_section.y = block_left_x;

	return (predict_ball_to_inter_section);
}


//=============================================================================
//ブロックのどの面に当たるかを予測する＊全部のブロックと判定するので要改善
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

	//プレイヤーの仮想加速度
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;

	
	//プレイヤーがブロックの上から当たったとき
	if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
{
	return F_OLD_SURFACE::up;
}
	//プレイヤーがブロックの下から当たったとき
	if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
{
	return F_OLD_SURFACE::down;
}
	//プレイヤーがブロックの左から当たったとき
	if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
{
	return F_OLD_SURFACE::left;
}
	//プレイヤーがブロックの右から当たったとき
	if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
{
	return F_OLD_SURFACE::right;
}
	
	//プレイヤーの加速度の仮想角度
	float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);
	
	//プレイヤーの頂点からブロックの頂点を結んだ直線の角度
	//プレイヤーから左下
	float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
	//プレイヤーから左上
	float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
	//プレイヤーから右下
	float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
	//プレイヤーから右上
	float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));
	
	//ブロックから右上の判定
	if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
{
	if (vertual_velocity_angle > LeftDown_angle)
	{
		//上
		return F_OLD_SURFACE::up;
	}
	else
	{
		//右
		return F_OLD_SURFACE::right;
	}
}
	
	//ブロックから右下の判定
	if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
	{
		if (vertual_velocity_angle > LeftUp_angle)
	{
		//右
		return F_OLD_SURFACE::right;
	}
		else
	{
		//下
		return F_OLD_SURFACE::down;
	}
	}
	
	//ブロックから左上の判定
	if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
{
	if (vertual_velocity_angle > RightDown_angle)
	{
		//左
		return F_OLD_SURFACE::left;
	}
	else
	{
		//上
		return F_OLD_SURFACE::up;
	}
}
	
	//ブロックから左下の判定
	if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
{
	if (vertual_velocity_angle > RightUp_angle)
	{
		//下
		return F_OLD_SURFACE::down;
	}
	else
	{
		//左
		return F_OLD_SURFACE::left;
	}
}
	
		return F_OLD_SURFACE::no_hit;

}

//=============================================================================
//円と回転しているブロックの当たり判定
//=============================================================================
bool CollisionCRB(D3DXVECTOR2 circle_pos, D3DXVECTOR2 block_pos, float circle_radius, D3DXVECTOR2 block_size, float block_rot)
{
	//ボールとブロックを結んだベクトル
	D3DXVECTOR2 circle_block_vector = circle_pos - block_pos;
	//ボールとブロックを結んだベクトルの長さ
	float circle_block_vector_length = sqrtf(LENGTH(circle_block_vector));
	//ボールの半径とブロックの中心点から頂点までの長さを足したやつの2乗
	float radius_plus_size_length = LENGTH(D3DXVECTOR2(block_size.x + circle_radius, block_size.y + circle_radius));

	//ボールとブロックを結んだベクトルの角度
	float circle_block_vector_angle = atan2f(circle_block_vector.y, circle_block_vector.x);
	//ボールの仮想角度
	float virtual_ball_angle = circle_block_vector_angle - block_rot;
	//ボールとブロックを結んだ仮想ベクトル
	D3DXVECTOR2 virtual_ball_vector;
	virtual_ball_vector.x = circle_block_vector_length * cosf(virtual_ball_angle);
	virtual_ball_vector.y = circle_block_vector_length * sinf(virtual_ball_angle);
	//ボールの仮想座標
	D3DXVECTOR2 virtual_ball_pos = block_pos + virtual_ball_vector;
	//ボールとブロックを結んだ仮想ベクトルの2乗
	float virtual_ball_vector_length = LENGTH(virtual_ball_vector);

	//ボールの半径とブロックの中心点から頂点までの長さを足したやつの2乗より
	//ボールとブロックを結んだ仮想ベクトルの2乗が短かったら
	if (radius_plus_size_length >= virtual_ball_vector_length)
	{
		//仮想領域の頂点座標
		float virtual_area_min_x = block_pos.x - powf((block_size.x / 2) + circle_radius, 2.0f);
		float virtual_area_min_y = block_pos.y - powf((block_size.y / 2) + circle_radius, 2.0f);
		float virtual_area_max_x = block_pos.x + powf((block_size.x / 2) + circle_radius, 2.0f);
		float virtual_area_max_y = block_pos.y + powf((block_size.y / 2) + circle_radius, 2.0f);
		//ブロックの頂点座標
		float block_min_x = block_pos.x - block_size.x / 2;
		float block_min_y = block_pos.y - block_size.y / 2;
		float block_max_x = block_pos.x + block_size.x / 2;
		float block_max_y = block_pos.y + block_size.y / 2;

		//縦長の仮想領域
		if (block_min_x < virtual_ball_pos.x && virtual_ball_pos.x > block_max_x)
		{
			if (virtual_area_min_y < virtual_ball_pos.y && virtual_ball_pos.y > virtual_area_max_y)
			{
				return true;
			}
		}
		//横長の仮想領域
		if (virtual_area_min_x < virtual_ball_pos.x && virtual_ball_pos.x > virtual_area_max_x)
		{
			if (block_min_y < virtual_ball_pos.y && virtual_ball_pos.y > block_max_y)
			{
				return true;
			}
		}

		//各頂点からボールまでの長さと円の半径を足したやつの2乗
		//左上
		float left_up_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_min_x, virtual_ball_pos.y - block_max_y));
		//左下
		float left_down_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_min_x, virtual_ball_pos.y - block_min_y));
		//右上
		float right_up_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_max_x, virtual_ball_pos.y - block_min_y));
		//右下
		float right_down_to_ball_length = LENGTH(D3DXVECTOR2(virtual_ball_pos.x - block_max_x, virtual_ball_pos.y - block_max_y));
		
		//半径の2乗
		float radius_square = powf(circle_radius, 2.0f);

		// 各頂点からボールまでの長さと円の半径を足したやつの2乗と半径の2乗の比較
		//左上
		if (radius_square > left_up_to_ball_length)
		{
			return true;
		 }
		//左下
		if (radius_square > left_down_to_ball_length)
		{
			return true;
		}
		//右上
		if (radius_square > right_up_to_ball_length)
		{
			return true;
		}
		//右下
		if (radius_square > right_down_to_ball_length)
		{
			return true;
		}
	}

	return false;
}


//=============================================================================
//四角形の回転後の頂点座標
//=============================================================================
SQUARE_VERTEX SquareVertexPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, float block_rot)
{
	SQUARE_VERTEX Square_Vertex_Pos;

	//縦、横の長さの半分
	float half_width, half_height;
	half_width = block_size.x / 2;
	half_height = block_size.y / 2;

	// 中心点から頂点に対する角度
	float BaseAngle = atan2f(half_height, half_width);
	// 中心点から頂点に対する距離
	float Radius = sqrtf(LENGTH(D3DXVECTOR2(half_width, half_height)));

	//左上の座標
	float x = block_pos.x - cosf(BaseAngle + block_rot) * Radius;
	float y = block_pos.y - sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.left_up = D3DXVECTOR2(x, y);
	//右上の座標
	x = block_pos.x + cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y - sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.right_up = D3DXVECTOR2(x, y);
	//左下の座標
	x = block_pos.x - cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.left_down = D3DXVECTOR2(x, y);
	//右下の座標
	x = block_pos.x + cosf(BaseAngle + block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.right_down = D3DXVECTOR2(x, y);


	return(Square_Vertex_Pos);
}

//=============================================================================
//プレイヤーの大きさに合わせて広げた四角形の回転後の頂点座標
//=============================================================================
SQUARE_VERTEX SquareVertexPlusPlayerPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, D3DXVECTOR2 player_size, float block_rot)
{
	SQUARE_VERTEX Square_Vertex_Pos;

	//縦、横の長さの半分
	float half_width, half_height;
	half_width = (player_size.x + block_size.x) / 2;
	half_height = (player_size.y + block_size.y) / 2;

	// 中心点から頂点に対する角度
	float BaseAngle = atan2f(half_height, half_width);
	// 中心点から頂点に対する距離
	float Radius = sqrtf(LENGTH(D3DXVECTOR2(half_width, half_height)));

	//左上の座標
	float x = block_pos.x - cosf(BaseAngle + block_rot) * Radius;
	float y = block_pos.y - sinf(BaseAngle + block_rot) * Radius;
	Square_Vertex_Pos.left_up = D3DXVECTOR2(x, y);
	//右上の座標
	x = block_pos.x + cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y - sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.right_up = D3DXVECTOR2(x, y);
	//左下の座標
	x = block_pos.x - cosf(BaseAngle - block_rot) * Radius;
	y = block_pos.y + sinf(BaseAngle - block_rot) * Radius;
	Square_Vertex_Pos.left_down = D3DXVECTOR2(x, y);
	//右下の座標
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
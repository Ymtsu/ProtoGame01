//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PI 3.14159265f // 円周率

//*****************************************************************************
// 構造体定義
//*****************************************************************************

enum class F_OLD_SURFACE : const char
{
	min_error = -1,
	no_hit,
	up,
	right,
	left,
	down
};

struct INTERSECTION_POS 
{
	D3DXVECTOR2 up;
	D3DXVECTOR2 down;
	D3DXVECTOR2 left;
	D3DXVECTOR2 right;
};

struct  SQUARE_VERTEX 
{
	D3DXVECTOR2 left_up;
	D3DXVECTOR2 right_up;
	D3DXVECTOR2 right_down;
	D3DXVECTOR2 left_down;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void UpdateCollision(void);

//=============================================================================
//こばの便利ツール
//=============================================================================
float LENGTH(D3DXVECTOR2 vector);
D3DXVECTOR2 VECTOR_NORMALIZE(D3DXVECTOR2 vector);
float INNER_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B);
float CROSS_PRODUCT(D3DXVECTOR2 vector_A, D3DXVECTOR2 vector_B);

//=============================================================================

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionCC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


F_OLD_SURFACE CollisionBB_SURFACE(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);
F_OLD_SURFACE PREDICT_SURFACE(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);

bool CollisionPIS_UP(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
bool CollisionPIS_DOWN(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
bool CollisionPIS_RIGHT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
bool CollisionPIS_LEFT(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);

D3DXVECTOR2 CollisionPIS_UP_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
D3DXVECTOR2 CollisionPIS_DOWN_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
D3DXVECTOR2 CollisionPIS_RIGHT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);
D3DXVECTOR2 CollisionPIS_LEFT_POS(D3DXVECTOR2 ball_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 ball_size, D3DXVECTOR2 block_size);

bool CollisionCL(D3DXVECTOR2 circle_pos, D3DXVECTOR2 line_min_pos, D3DXVECTOR2 line_max_pos, float circle_radius);
bool CollisionCRB(D3DXVECTOR2 circle_pos, D3DXVECTOR2 block_pos, float circle_radius, D3DXVECTOR2 block_size, float block_rot);

SQUARE_VERTEX SquareVertexPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, float block_rot);
SQUARE_VERTEX SquareVertexPlusPlayerPos(D3DXVECTOR2 block_pos, D3DXVECTOR2 block_size, D3DXVECTOR2 player_size, float block_rot);

bool CollisionConvexPoint(D3DXVECTOR2* block_vertex_pos, D3DXVECTOR2 player_center_pos, int vertex_num);
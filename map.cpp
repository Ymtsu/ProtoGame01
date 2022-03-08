#include "main.h"
#include "map.h"

MAP	map[MAP_Y][MAP_X];

int SetMap(int mapnum) {

	switch (mapnum)//開くテキストを決定
	{
	case 0:
	{
		char fname0[] = "1-1.txt";//開くファイルの名前//cppファイルと同じ所に.txtを入れる
		FILE* fp;
		fp = fopen(fname0, "r"); // ファイルを開く。失敗するとNULLを返す。
		if (fp == NULL) {
			printf("%s file not open!\n", fname0);
			return -1;
		}
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				(void)fscanf(fp, "%d", &map[i][j].num);
			}
		}
		fclose(fp);
	}
	break;
	return 0;
	}
}

void InitMap(void)
{
	//マップどうりにステージ作成
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x].pos = D3DXVECTOR2(((BLOCK_SIZE * x) + (BLOCK_SIZE / 2)), ((BLOCK_SIZE * y) + (BLOCK_SIZE / 2)));//位置を初期化
			switch (map[y][x].num)
			{																//ここにギミックやブロックのSetを入れる
			case 0:
				break;

			}
		}
	}
}
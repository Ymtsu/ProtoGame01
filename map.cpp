#include "main.h"
#include "map.h"

MAP	map[MAP_Y][MAP_X];

int SetMap(int mapnum) {

	switch (mapnum)//�J���e�L�X�g������
	{
	case 0:
	{
		char fname0[] = "1-1.txt";//�J���t�@�C���̖��O//cpp�t�@�C���Ɠ�������.txt������
		FILE* fp;
		fp = fopen(fname0, "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
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
	//�}�b�v�ǂ���ɃX�e�[�W�쐬
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x].pos = D3DXVECTOR2(((BLOCK_SIZE * x) + (BLOCK_SIZE / 2)), ((BLOCK_SIZE * y) + (BLOCK_SIZE / 2)));//�ʒu��������
			switch (map[y][x].num)
			{																//�����ɃM�~�b�N��u���b�N��Set������
			case 0:
				break;

			}
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX 10000
#define SIZE 200
int off_lamp(int EE[SIZE][SIZE][3], int D[SIZE], int ws[SIZE],int L, int R, int point, int size);
int main()
{
	FILE* fp;
	FILE* fp2;
	char file[20];
	int size, i, j, start, d[SIZE], w[SIZE], EE[SIZE][SIZE][3], PP[SIZE][SIZE][3], ws[SIZE],visit[SIZE];
	int L, R ,result;
	printf("input file name? ");
	scanf("%s", file);

	if ((fp = fopen(file, "r")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}

	fscanf(fp, "%d %d", &size, &start);

	for (i = 1; i <= size; i++)
	{
		fscanf(fp, "%d %d", &d[i], &w[i]);
	}

	for (i = 1; i <= size; i++)
	{
		EE[i][i][1] = MAX;
		EE[i][i][2] = MAX;
		PP[i][i][0] = 0;
		PP[i][i][1] = 0;
		visit[i] = 0;
	}
	for (i = 1; i <= size; i++)
	{
		ws[i] = 0;
		for (j = 1; j <= i; j++)
		{
			ws[i] = ws[i]+w[j];
		}
	}
	visit[start] = 1;
	L = start;
	R = start;
	EE[start][start][1] = 0;
	EE[start][start][2] = 0;
	for (i = 1; i <= size; i++)
	{
		printf("%d %d\n", d[i], w[i]);
	}
	result=off_lamp(EE, d, ws, L, R, 1, size);
	printf("%d", result);
	if ((fp2 = fopen("output.txt", "w")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}

	fclose(fp);
	fclose(fp2);
	return 0;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int off_lamp(int EE[SIZE][SIZE][3], int D[SIZE], int ws[SIZE], int L, int R, int point, int size)
{
	int temp=0;
	
	if (L == 1 && R == SIZE)
		return 0;

	if (1 < L)
	{
		if (point == 1)
			temp = off_lamp(EE, D, ws, L - 1, R, 1, size) + (D[L] - D[L - 1])*(ws[size] - (ws[R] - ws[L]));
		if (point == 2)
			temp = off_lamp(EE, D, ws, L - 1, R, 1, size) + (D[R] - D[L - 1])*(ws[size] - (ws[R] - ws[L]));
	}
	//printf("%d \n", temp);
	if (R < size)
	{
		if(point == 1)
			temp = min(temp, off_lamp(EE, D, ws, L, R + 1, 2, size) + (D[R + 1] - D[L] * (ws[size] - (ws[R] - ws[L]))));
		if(point == 2)
			temp = min(temp, off_lamp(EE, D, ws, L, R + 1, 2, size) + (D[R + 1] - D[R] * (ws[size] - (ws[R] - ws[L]))));
	}
	return EE[L][R][point]=temp;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX 10000
#define SIZE 500
int off_lamp(int D[SIZE], int ws[SIZE], int L, int R, int point, int size);
int main()
{
	FILE* fp;
	FILE* fp2;
	char file[20];
	int size, i, j, start, d[SIZE], w[SIZE], ws[SIZE];
	int L, R, result, p = 0;
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
	w[start] = 0;
	for (i = 1; i <= size; i++)
	{
		ws[i] = 0;
		for (j = 1; j <= i; j++)
		{
			ws[i] = ws[i] + w[j];
		}
	}

	L = start;
	R = start;

	result = off_lamp(d, ws, L, R, 2, size);

	if ((fp2 = fopen("output.txt", "w")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}

	fprintf(fp2, "%d", result);
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

int off_lamp(int D[SIZE], int ws[SIZE], int L, int R, int point, int size)
{
	int temp = 0, min = 0;

	if (L == 1 && R == SIZE)
		return 0;

	if (1 < L)
	{
		if (point == 1)
		{
			min = off_lamp(D, ws, L - 1, R, 1, size) + (D[L] - D[L - 1])*(ws[size] - (ws[R] - ws[L - 1]));
		}
		else if (point == 2)
		{
			min = off_lamp(D, ws, L - 1, R, 1, size) + (D[R] - D[L - 1])*(ws[size] - (ws[R] - ws[L - 1]));
		}
	}

	if (R < size)
	{
		if (point == 1)
		{
			temp = off_lamp(D, ws, L, R + 1, 2, size) + (D[R + 1] - D[L]) * (ws[size] - (ws[R] - ws[L - 1]));
			if (min > temp)
			{
				min = temp;
			}
		}
		else if (point == 2)
		{
			temp = off_lamp(D, ws, L, R + 1, 2, size) + (D[R + 1] - D[R]) * (ws[size] - (ws[R] - ws[L - 1]));
			if (min > temp)
			{
				min = temp;
			}
		}
	}
	return min;
}
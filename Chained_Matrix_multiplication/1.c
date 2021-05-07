#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX 10000
char result[1000] = {0};
char temp[20] = { 0 };
void minmult(int M[100][100], int n, int d[], int p[100][100]);
void print_order(int i, int k, int  p[100][100]);
int main()
{
	FILE* fp;
	FILE* fp2;
	char file[20];
	int i,j, size, d[100],p[100][100],M[100][100];
	printf("input file name? ");
	scanf("%s", file);

	if ((fp = fopen(file, "r")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}

	fscanf(fp, "%d", &size);

	for (i = 1; i <=size; i++)
	{
		fscanf(fp, "%d", &d[i]);
	}

	printf("\n");
	minmult(M, size, d, p);

	print_order(1, size, p);
	if ((fp2 = fopen("output.txt", "w")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}
	fprintf(fp2, "%s", result);
	fclose(fp2);
	fclose(fp);
	return 0;
}
void minmult(int M[100][100], int n, int d[], int p[100][100])
{
	int i, j, k, dia;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			M[i][j] = MAX;
			p[i][j] = -1;
		}
	}

	for (i = 1; i <=n; i++)
		M[i][i] = 0;
	
	for (dia = 1; dia <=n-1; dia++)
	{
		for (i = 1; i <= n - dia; i++)
		{
			j = i + dia;
			for (k = i; k <= j - 1; k++)
			{
				if (M[i][j] > M[i][k] + M[k + 1][j] + d[i] * d[k] * d[j])
				{
					p[i][j] = k;
					M[i][j] = M[i][k] + M[k + 1][j] + d[i] * d[k] * d[j];
				}
			}
		}
	}
}

void print_order(int i, int j, int  p[100][100])
{
	if (i == j)
	{
		sprintf(temp, "%d", i);
		strcat(result, temp);
	}
	else
	{
		strcat(result,"(");
		print_order(i, p[i][j], p);
		print_order(p[i][j] + 1, j, p);
		strcpy(temp, ")");
		strcat(result, temp);
	}
}
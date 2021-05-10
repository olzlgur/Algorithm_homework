#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX 10000

int main()
{
	FILE* fp;
	FILE* fp2;
	char file[20];
	int size,i,j;
	char miro[200][200], p[200][200];
	int d[200][200],visit[200][200];
	int minx, miny,count;
	int answer[200][2];
	printf("input file name? ");
	scanf("%s", file);
	

	if ((fp = fopen(file, "r")) == NULL)
		{
			printf("파일 열기에 실패하였습니다.\n");
		}

	fscanf(fp, "%d", &size);

	for (i = 1; i <= size; i++)
	{
		fscanf(fp, "%s", miro[i]);
	}
	for (i = 1; i <=size; i++)
	{
		for (j = size - 1; j >= 0; j--)
		{
			miro[i][j + 1] = miro[i][j];
		}
	}

	for (i = 1; i <= size; i++)
	{
		for (j = 1; j <= size; j++)
		{
			d[i][j] = MAX;
			visit[i][j] = -1;
		}
	}
	d[1][1] = 0;
	p[1][1] = '1';
	visit[1][1] = 1;
	minx = 1;
	miny = 1;
	while (1)
	{
		if (minx != 1)
		{
			if (miro[minx - 1][miny] == '1' && d[minx][miny] < d[minx - 1][miny])
			{
				d[minx - 1][miny] = d[minx][miny];
				p[minx - 1][miny] = 'D';
			}
			else if (miro[minx - 1][miny] == '0' && d[minx][miny] + 1 < d[minx - 1][miny])
			{
				d[minx - 1][miny] = d[minx][miny] + 1;
				p[minx - 1][miny] = 'D';
			}
		}
		if (minx != size)
		{
			if (miro[minx + 1][miny] == '1' && d[minx][miny] < d[minx + 1][miny])
			{
				d[minx + 1][miny] = d[minx][miny];
				p[minx + 1][miny] = 'U';
			}
			if (miro[minx + 1][miny] == '0' && d[minx][miny] + 1 < d[minx + 1][miny])
			{
				d[minx + 1][miny] = d[minx][miny] + 1;
				p[minx + 1][miny] = 'U';
			}
		}
		if (miny != 1)
		{
			if (miro[minx][miny - 1] == '1' && d[minx][miny] < d[minx][miny - 1])
			{
				d[minx][miny - 1] = d[minx][miny];
				p[minx][miny - 1] = 'R';
			}
			if (miro[minx][miny - 1] == '0' && d[minx][miny] + 1 < d[minx][miny - 1])
			{
				d[minx][miny - 1] = d[minx][miny] + 1;
				p[minx][miny - 1] = 'R';
			}
		}
		if (miny != size)
		{

			if (miro[minx][miny + 1] == '1' && d[minx][miny] < d[minx][miny + 1])
			{
				d[minx][miny + 1] = d[minx][miny];
				p[minx][miny + 1] = 'L';
			}
			if (miro[minx][miny + 1] == '0' && d[minx][miny] + 1 < d[minx][miny + 1])
			{
				d[minx][miny + 1] = d[minx][miny] + 1;
				p[minx][miny + 1] = 'L';
			}
		}
		count = 0;
		for (i = 1; i <= size; i++)
		{
			for (j = 1; j <= size; j++)
			{
				if (visit[i][j] != 1)
				{
					minx = i;
					miny = j;
					count = 1;
				}
			}
		}
		if (count == 0)
		{
			break;
		}
		for (i = 1; i <= size; i++)
		{
			for (j = 1; j <= size; j++)
			{
				if (visit[i][j] != 1 && d[i][j] <= d[minx][miny])
				{
					minx = i;
					miny = j;
				}
			}
		}
		visit[minx][miny] = 1;
	}

	i = size;
	j = size;
	count= 0;
	while (1)
	{
		if (p[i][j] == 'R')
		{
			answer[count][0] = i;
			answer[count][1] = j;
			count++;
			j++;
		}
		if (p[i][j] == 'L')
		{
			answer[count][0] = i;
			answer[count][1] = j;
			j--;
			count++;
		}
		if (p[i][j] == 'U')
		{
			answer[count][0] = i;
			answer[count][1] = j;
			i--;
			count++;
		}
		if (p[i][j] == 'D')
		{
			answer[count][0] = i;
			answer[count][1] = j;
			i++;
			count++;
		}
		if (i == 1 && j == 1)
		{
			answer[count][0] = i;
			answer[count][1] = j;
			break;
		}
	}

	if ((fp2 = fopen("output.txt", "w")) == NULL)
	{
		printf("파일 열기에 실패하였습니다.\n");
	}
	fprintf(fp2, "%d\n", d[size][size]);
	for (i = count; i >= 0; i--)
	{
		fprintf(fp2, "%d %d\n", answer[i][0], answer[i][1]);
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}
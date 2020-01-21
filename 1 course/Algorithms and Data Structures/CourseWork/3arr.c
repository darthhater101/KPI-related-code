#include "3arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int*** create_arr()
{
	int i, k;
    int ***arr;
    arr = (int***)malloc(P*sizeof(int**));
    for(k = 0;k < P;k++)
	{
        arr[k] = (int**)malloc(N*sizeof(int*));
        for(i = 0;i < N;i++)
		{
            arr[k][i] = (int*)malloc(N*sizeof(int));
        }
    }
    return arr;
}

void fill_sort(int ***arr)
{
	int k, i, j;
    for(k = 0;k < P;k++)
	{
        for(i = 0;i < N;i++)
		{
            for(j = 0;j < N;j++)
			{
                arr[k][i][j] = i;
            }
        }
    }
}

void fill_rev_sort(int ***arr)
{
	int k, i, j;
    for(k = 0;k < P;k++)
	{
        for(i = 0;i < N;i++)
		{
            for(j = 0;j < N;j++)
			{
                arr[k][i][j] = N - i;
            }
        }
    }
}

void fill_random(int ***arr)
{
	srand(time(0));
	int k, i, j;
    for(k = 0;k < P;k++)
	{
        for(i = 0;i < N;i++)
		{
            for(j = 0;j < N;j++)
			{
                arr[k][i][j] = rand()%100;
            }
        }
    }
}

void free_arr(int ***arr)
{
	int k, i;
    for(k = 0;k < P;k++)
	{
        for(i = 0;i < N; i++)
		{
            free(arr[k][i]);
        }
        free(arr[k]);
    }
    free(arr);
}

void print_arr(int ***arr)
{
    int k, i, j;
    for(k = 0;k < P;k++)
    {
        printf("Розріз %d:\n", k+1);
        for(i = 0;i < N;i++)
        {
            for(j = 0;j < N;j++)
            {
                printf("%3d ", arr[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

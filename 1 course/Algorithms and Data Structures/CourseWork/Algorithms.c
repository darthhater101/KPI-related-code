#include "Algorithms.h"
#include <stdio.h>
#include "3arr.h"

void Cocktail_Sort(int ***A)
{
	int k, i, j = 1;
	for(k = 0;k < P;k++)
	{
		int buff;
        int left = 0;
        int right = N - 1;
        do
        {
            for (i = left;i < right;i++)
            {
                if (A[k][i][i] > A[k][i+1][i+1])
                {
                    buff = A[k][i][i];
                    A[k][i][i] = A[k][i+1][i+1];
                    A[k][i+1][i+1] = buff;
                    j = i;
                }
            }
            right = j;
            for (i = right - 1;i >= left;i--)
            {
                if (A[k][i][i] > A[k][i+1][i+1])
                {
                    buff = A[k][i][i];
                    A[k][i][i] = A[k][i+1][i+1];
                    A[k][i+1][i+1] = buff;
                    j = i;
                }
            }
            left = j + 1;
        } while (left < right);

        right = 0;
        left = N - 1;
        j = 1;
        do
        {
            for (i = right;i < left;i++)
            {
                if (A[k][i][N-1-i] > A[k][i+1][N-2-i])
                {
                    buff = A[k][i][N-1-i];
                    A[k][i][N-1-i] = A[k][i+1][N-2-i];
                    A[k][i+1][N-2-i] = buff;
                    j = i;
                }
            }
            left = j;
            for (i = left - 1;i >= right;i--)
            {
                if (A[k][i][N-1-i] > A[k][i+1][N-2-i])
                {
                    buff = A[k][i][N-1-i];
                    A[k][i][N-1-i] = A[k][i+1][N-2-i];
                    A[k][i+1][N-2-i] = buff;
                    j = i;
                }
            }
            right = j + 1;
        } while (right < left);
	}
}

void Shell_Sort(int ***A)
{
	int i, j, k;
	int tmp, step;
	for(k = 0;k < P;k++)
	{
		for(step = N/2; step >= 1; step /= 2)
		{
			for(i = step; i < N; i++)
			{
				for(j = i; j >= step && A[k][j-step][j-step] > A[k][j][j]; j -= step)
				{
					tmp = A[k][j-step][j-step];
					A[k][j-step][j-step] = A[k][j][j];
					A[k][j][j] = tmp;
				}
			}
		}

		for(step = N/2;step >= 1;step /= 2)
		{
			for(i = step;i < N;i++)
			{
				for(j = i;j >= step && A[k][j-step][N-1-(j-step)] > A[k][j][N-1-j];j -= step)
				{
					tmp = A[k][j-step][N-1-(j-step)];
					A[k][j-step][N-1-(j-step)] = A[k][j][N-1-j];
					A[k][j][N-1-j] = tmp;
				}
			}
		}
	}
}

void Insertion_Sort(int ***A)
{
	int i, j, k;
	for(k = 0;k < P;k++)
	{
		for(i = 1;i < N;i++)
		{
			int buff = A[k][i][i];
			j = i;
			while(j > 0 && buff < A[k][j-1][j-1])
			{
				A[k][j][j] = A[k][j-1][j-1];
				j--;
			}
			A[k][j][j] = buff;
		}

		for(i = 1;i < N;i++)
		{
			int buff = A[k][i][N-1-i];
			j = i;
			while(j > 0 && buff < A[k][j-1][N-j])
			{
				A[k][j][N-1-j] = A[k][j-1][N-j];
				j--;
			}
			A[k][j][N-1-j] = buff;
		}
	}
}

void Selection_Sort(int ***A)
{
	int i, j, k;
	for(k = 0;k < P;k++)
	{
		for(i = 0;i < N - 1;i++)
		{
			int min = i;
			for(j = i + 1;j < N;j++)
			{
				if(A[k][j][j] < A[k][min][min])
				{
					min = j;
				}
			}
            int buff = A[k][i][i];
            A[k][i][i] = A[k][min][min];
            A[k][min][min] = buff;
		}

		for(i = 0;i < N - 1;i++)
		{
			int min = i;
			for(j = i + 1;j < N;j++)
			{
				if(A[k][j][N-1-j] < A[k][min][N-1-min])
				{
					min = j;
				}
			}
			if(min > i)
            {
                int buff = A[k][i][N-1-i];
                A[k][i][N-1-i] = A[k][min][N-1-min];
                A[k][min][N-1-min] = buff;
            }
		}
	}
}

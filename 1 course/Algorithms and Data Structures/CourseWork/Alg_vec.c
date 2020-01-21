#include "Alg_vec.h"
#include "Vec.h"

void Selection_Sort_Vec(int *arr)
{
	int i, j;
	for(i = 0;i < N - 1;i++)
	{
		int min = i;
		for(j = i + 1;j < N;j++)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
        int buff = arr[i];
        arr[i] = arr[min];
        arr[min] = buff;
	}
}

void Cocktail_Sort_Vec(int *arr)
{
	int buff, i, k = 1;
	int left = 0;
    int right = N - 1;
    do {
        for (i = left;i < right;i++)
		{
            if (arr[i] > arr[i+1])
			{
                buff = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = buff;
                k = i;
            }
        }
        right = k;
        for (i = right-1;i >= left; i--)
		{
            if (arr[i] > arr[i+1])
			{
                buff = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = buff;
                k = i;
            }
        }
        left = k+1;
    } while (left < right);
}

void Shell_Sort_Vec(int *arr)
{
	int i, j, step, tmp;
	for(step = N/2; step >= 1; step /= 2)
    {
        for(i = step; i < N; i++)
        {
            for(j = i; j >= step && arr[j-step] > arr[j]; j -= step)
            {
                tmp = arr[j-step];
                arr[j-step] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void Insertion_Sort_Vec(int *arr)
{
	int i, j, buff;
	for(i = 1;i < N;i++)
	{
		int buff = arr[i];
		j = i;
		while(j > 0 && buff < arr[j-1])
		{
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = buff;
	}
}

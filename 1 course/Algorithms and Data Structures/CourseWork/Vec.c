#include "Vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int* create_vec()
{
	int *vec;
    vec = (int*)malloc(N*sizeof(int));
    return vec;
}

void fill_sort_vec(int *vec)
{
	int i;
	for(i = 0;i < N;i++)
	{
        vec[i] = i;
    }
}

void fill_rev_sort_vec(int *vec)
{
	int i;
	for(i = 0;i < N;i++)
	{
        vec[i] = N - i;
    }
}

void fill_random_vec(int *vec)
{
	srand(time(0));
	int i;
	for(i = 0;i < N;i++)
	{
        vec[i] = rand()%100;
    }
}

void print_vec(int *vec)
{
    int i;
    for(i = 0;i < N;i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

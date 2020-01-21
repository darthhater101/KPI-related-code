#ifndef __3ARR_H__
#define __3ARR_H__

#define P 32
#define N 625

int*** create_arr();

void fill_sort(int***);

void fill_rev_sort(int***);

void fill_random(int***);

void free_arr(int***);

void print_arr(int***);

#endif

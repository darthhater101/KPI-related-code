#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <iomanip>

void _exp(double x, double eps, int& len)
{
	double U1 = 1;
	double multiplier_1 = 1;
	double multiplier_2 = 1;
	int k = 1;
	double R = 0;

	int whole_part = (int)x;
	double fractional_part = x - whole_part;

	multiplier_1 = (whole_part == 0) ? 1 : pow(M_E, whole_part);
	
	if (fractional_part == 0)
	{
		multiplier_2 = 1;
	}
	else
	{
		while (abs(U1) > eps)
		{
			U1 = abs(fractional_part) / k * U1;
			multiplier_2 += U1;
			k++;
		}
		if (eps == 1e-8) len = k - 1;
		R = abs(fractional_part) /  k * U1;

		if (fractional_part < 0) multiplier_2 = 1 / multiplier_2;
	}

	double result = multiplier_1 * multiplier_2;


	printf("|%15E |%5d |%20E |%20E |\n", eps, k - 1, abs(result - exp(x)), R);
}

void _exp(double x, int series_length)
{
	double U1 = 1;
	double multiplier_1 = 1;
	double multiplier_2 = 1;
	double R = 0;

	int whole_part = (int)x;
	double fractional_part = x - whole_part;

	multiplier_1 = (whole_part == 0) ? 1 : pow(M_E, whole_part);

	if (fractional_part == 0)
	{
		multiplier_2 = 1;
	}
	else
	{
		for (int i = 1; i <= series_length; i++)
		{
			U1 = abs(fractional_part) / i * U1;
			multiplier_2 += U1;
		}
		R = abs(fractional_part) / (series_length + 1) * U1;

		if (fractional_part < 0) multiplier_2 = 1 / multiplier_2;
	}

	double result = multiplier_1 * multiplier_2;

	printf("|%10f |%20E |%20E |\n", x, abs(result - exp(x)), R);
}

int main()
{
	double a = -17.1;
	double b = 2.5;
	double x = (a + b) / 2;
	double eps = 1e-2;
	double h = (b - a) / 10;
	int len;

	printf("Task 1\n");
	printf("---------------------------------------------------------------------\n");
	printf("|%15s |%5s |%20s |%20s |\n", "Eps", "N", "Abs_delta", "R");
	printf("---------------------------------------------------------------------\n");

	while (eps >= 1e-14)
	{
		_exp(-7.3, eps, len);
		eps /= 1000;
	}
	printf("---------------------------------------------------------------------\n");

	printf("Task 2 (N == %d)\n", len);
	printf("---------------------------------------------------------\n");
	printf("|%10s |%20s |%20s |\n", "X", "Abs_delta", "R");
	printf("---------------------------------------------------------\n");

	for (int i = 0; i <= 10; i++) {
		x = a + h * i;
		_exp(x, len);
	}
	printf("---------------------------------------------------------\n");

	system("pause");
	return 0;
}
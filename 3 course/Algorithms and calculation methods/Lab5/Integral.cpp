#include "Integral.h"
#include <iostream>

double simpsonMethod(int power, int left, int right)
{
	double sigma1 = 0.0;
	double sigma2 = 0.0;

	int n = (int)((double)(b - a) / sqrt(sqrt(EPS)));

	double h = (b - a) / (double)n;

	for (int i = 1; i < n; i += 2) { 
		sigma1 = sigma1 + phi(a + i * h, power, left, right); 
	}
	for (int i = 2; i < n; i += 2) {
		sigma2 = sigma2 + phi(a + i * h, power, left, right);
	}

	return h / 3 * (phi(a, power, left, right) + phi(b, power, left, right) + 4 * sigma1 + 2 * sigma2);
}



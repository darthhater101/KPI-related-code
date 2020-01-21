#include "Misc.h"

double Legandr(int n, double x) {
	double L;
	double Ln = x, L1 = 1;

	if (n == 0) return L1;
	if (n == 1) return Ln;

	int i = 1;
	while (i < n) {
		L = (1.0 * (2 * i + 1) / (i + 1)) * x * Ln - (1.0 * i / (i + 1)) * L1;
		L1 = Ln;
		Ln = L;
		i++;
	}
	return Ln;
}

double func(double x) {
	return 1.2 * tanh(x) * cos(10 * x) * x;
}

double phi(double x, double n, int left, int right) {
	if (n == right) return func(x) * Legandr(left, x);
	return Legandr(left, x) * Legandr(right, x);
}
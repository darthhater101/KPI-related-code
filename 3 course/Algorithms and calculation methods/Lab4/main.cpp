#include <cmath>
#include <iostream>
#include <iomanip>

double F(double x)
{
	return sqrt(exp(2 * x)) / x;
}

double func(double x)
{
	return sqrt(exp(2 * x)) / x - sqrt(exp(2 * x)) / (x * x);
}

double newtonLeibniz(double a, double b)
{
	return F(b) - F(a);
}

double calcH(double eps, double a, double b)
{
	const double M2 = 1660.7955;
	return sqrt(12 * eps / ((b - a) * M2));
}

double calcDelta(double a, double b)
{
	return fabs(a - b);
}

double trapezoid(double eps, double a, double b, double& step, bool second = false)
{
	step = calcH(eps, a, b);
	int n = second ? eps : (b - a) / step;
	step = (b - a) / n;
	double result = func(a) / 2;
	double x;
	for (int i = 1; i < n ; i++)
	{
		x = a + step * i;
		result = result + func(x);
	}

	result = result + func(b) / 2;
	result = result * step;

	return result;
}

double doubleRecalculation(double eps, double a, double b, double& step)
{
	int n = (b - a) / sqrt(eps);

	double In = trapezoid(n, a, b, step, true);
	n = n * 2;
	double I2n = trapezoid(n, a, b, step, true);

	while (calcDelta(In, I2n) > 3 * eps)
	{
		In = I2n;
		n = n * 2;
		I2n = trapezoid(n, a, b, step, true);
	}

	return I2n;
}

void printTask1(double eps, double newton, double step, double error)
{
	std::cout << "-----------------------------------------------------\n";
	std::cout << "|   Eps|            Step| By Newton|           Error|\n";
	std::cout << "-----------------------------------------------------\n";

	std::cout << "|" << std::setw(6) << eps << "|"
		<< std::setw(16) << std::setprecision(10) << step << "|"
		<< std::setw(10) << std::setprecision(6) << newton << "|"
		<< std::setw(16) << std::setprecision(10) << error << "|" << std::endl;
}

void printTask2(double delta, double step, double error)
{
	std::cout << "-----------------------------------------------------\n";
	std::cout << "|           Delta|             Step|          Error|\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "|" << std::setw(16) << std::setprecision(10) << delta << "|"
		<< std::setw(16) << std::setprecision(10) << step << "|"
		<< std::setw(16) << std::setprecision(10) << error << "|" << std::endl;
	std::cout << "----------------------------------------------------\n\n";
}

int main()
{
	int a, b;
	a = 1; 
	b = 10;

	double eps = 1e-1;
	double step;
	double newton;
	double trapez;
	double delta1;
	double delta2;

	while (eps >= 1e-7)
	{
		newton = newtonLeibniz(a, b);
		trapez = trapezoid(eps, a, b, step);
		delta1 = calcDelta(newton, trapez);

		printTask1(eps, newton, step, delta1);

		delta2 = calcDelta(newton, doubleRecalculation(delta1, a, b, step));

		printTask2(delta1, step, delta2);

		eps = eps / 10;
	}

	system("pause");
	return 0;
}
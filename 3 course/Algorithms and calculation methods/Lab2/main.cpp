#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

typedef struct
{
	double eps;
	double root;
	double accuracy;
	int iterations;
} result;

double func(double x)
{
	return sin(x + M_PI / 4) + sin(3 * x) + sin(5 * x) - x + 0.3;
}

double first_der_func(double x)
{
	return 3 * cos(3 * x) + 5 * cos(5 * x) + cos(x + M_PI / 4) - 1;
}

double bisection(double a, double b, double eps, int& iterations, double& accuracy)
{
	iterations = 1;

	double c;

	while (fabs(b - a) >= 2 * eps)
	{
		iterations++;
		c = (a + b) / 2;
		if (func(a)*func(c) < 0)
			b = c;
		else
			a = c;
	}

	accuracy = fabs(b - a) / 2;

	return (a + b) / 2;
}

double iteration(double a, double b, double eps, int& iterations, double& accuracy, int maxit, bool& done)
{
	done = true;
	double M, m, q, lambda;
	double x, x_next;
	iterations = 1;

	if (fabs(first_der_func(a)) > fabs(first_der_func(b))) 
	{
		M = first_der_func(a);
		m = first_der_func(b);
	}
	else 
	{
		M = first_der_func(b);
		m = first_der_func(a);
	}


	lambda = 1 / M;
	q = 1 - fabs(m / M);

	x = (a + b) / 2;
	x_next = x;
	do
	{
		if (iterations > maxit)
		{
			printf("With %E, the root calculation accuracy was not achieved\n", eps);
			done = false;
			return x_next;
		}
		x = x_next;
		x_next = x - lambda * func(x);
		iterations++;
	} while (fabs(x_next - x) > ((1 - q) / q) * eps);

	accuracy = fabs(x_next - x) * q / (1 - q);

	return x_next;
}

void search_roots(double right, double left, double step, std::vector<result>& bis_res, std::vector<result>& it_res)
{
	double eps;
	int iterations_it;
	int iterations_bis;
	double accuracy_it;
	double accuracy_bis;
	bool done;

	result res;

	for (double i = right; i <= left; i += step)
	{
		if (func(i) * func(i + step) < 0)
		{
			eps = 1e-2;
			for(int j = 1; j <= 4; j++)
			{
				res.eps = eps;

				res.root = bisection(i, i + step, eps, iterations_bis, accuracy_bis);
				res.iterations = iterations_bis;
				res.accuracy = accuracy_bis;
				bis_res.push_back(res);

				res.root = iteration(i, i + step, eps, iterations_it, accuracy_it, 200, done);
				res.iterations = iterations_it;
				res.accuracy = accuracy_it;
				it_res.push_back(res);

				eps = eps / 1000;
			}
		}
	}
}

void print_results(std::vector<result> bis_res, std::vector<result> it_res)
{
	printf("Bisection\n");
	printf("-------------------------------------------------\n");
	printf("|%13s|%16s|%16s|\n", "Eps", "Root", "Accuracy");
	printf("-------------------------------------------------\n");
	for (int i = 1; i <= bis_res.size(); i++)
	{
		printf("|%13E|%16.11f|%16E|\n", bis_res[i - 1].eps, bis_res[i - 1].root, bis_res[i - 1].accuracy);
		if(i % 4 == 0 && i != 0 && i != bis_res.size()) 
			printf("-------------------------------------------------\n");
	}
	printf("-------------------------------------------------\n\n");

	printf("Iteration\n");
	printf("-------------------------------------------------\n");
	printf("|%13s|%16s|%16s|\n", "Eps", "Root", "Accuracy");
	printf("-------------------------------------------------\n");
	for (int i = 1; i <= it_res.size(); i++)
	{
		printf("|%13E|%16.11f|%16E|\n", it_res[i - 1].eps, it_res[i - 1].root, it_res[i - 1].accuracy);
		if (i % 4 == 0 && i != 0 && i != bis_res.size()) 
			printf("-------------------------------------------------\n");
	}
	printf("-------------------------------------------------\n\n");

	printf("Iterations count\n");
	printf("---------------------------------------------------\n");
	printf("|%13s|%17s|%17s|\n", "Eps", "Iteration Method", "Bisection Method");
	printf("---------------------------------------------------\n");
	for (int i = 1; i <= it_res.size(); i++)
	{
		printf("|%13E|%17d|%17d|\n", it_res[i - 1].eps, it_res[i - 1].iterations, bis_res[i - 1].iterations);
		if (i % 4 == 0 && i != 0 && i != bis_res.size())
			printf("---------------------------------------------------\n");
	}
	printf("---------------------------------------------------\n\n");

}

int main()
{
	std::vector<result> bisection_res;
	std::vector<result> iteration_res;

	search_roots(-10, 10, 0.1, bisection_res, iteration_res);//use methods in this function
	print_results(bisection_res, iteration_res);

	system("pause");
	return 0;
}
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>

//ДР: xy'' + y' = ln(x)
//Точний розв'язок: y = x * ln(x) - 2x + ln(x)
//ПУ: y(1) = -2, y'(1) = 0
//[a, b]: [1, 2]

const double a = 1, b = 2;

double func(double x) {
	return x * log(x) - 2 * x + log(x);
}

double right_side_eval(double x, double y1) {
	return (log(x) - y1) / x;
}


double runge_kutta_method(double eps, std::vector<double>& vec_x, std::vector<double>& vec_y, std::vector<double>& vec_der_y, double& step) { // TODO: rewrite method for double recalculation
	step = 0;
	int n = 10;
	std::vector<double> k(4);

	double Yk = -2, Yk_1 = 0;
	double x;

	do {
		step = (b - a) / n;
		Yk = -2;
		Yk_1 = 0;
		vec_x.clear();
		vec_y.clear();
		vec_der_y.clear();
		for (int i = 0; i <= n; i++) {
			x = a + i * step;
			vec_x.push_back(x);

			k[0] = step * right_side_eval(x, Yk_1);
			k[1] = step * right_side_eval(x + step / 2, Yk_1 + k[0] / 2);
			k[2] = step * right_side_eval(x + step / 2, Yk_1 + k[1] / 2);
			k[3] = step * right_side_eval(x + step, Yk_1 + k[2]);

			vec_y.push_back(Yk);
			vec_der_y.push_back(Yk_1);

			Yk = Yk + step * Yk_1 + (k[0] + k[1] + k[2]) / 6 * step;
			Yk_1 = Yk_1 + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
		}
		n++;
	} while (fabs(func(b) - Yk) >= eps);
	return fabs(func(b) - Yk);
}

double runge_kutta_double_rec(double x, double y, double& der_y, double step) {
	std::vector<double> k(4);

	k[0] = step * right_side_eval(x, der_y);
	k[1] = step * right_side_eval(x + step / 2, der_y + k[0] / 2);
	k[2] = step * right_side_eval(x + step / 2, der_y + k[1] / 2);
	k[3] = step * right_side_eval(x + step, der_y + k[2]);

	y = y + step * der_y + (k[0] + k[1] + k[2]) / 6 * step;
	der_y = der_y + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
	return y;
}

double double_recalculation(double acc, std::vector<double> vec_x, std::vector<double>& vec_y, std::vector<double> vec_der_y) {
	int n = (b - a) / sqrt(sqrt(acc));
	double final_step = 0;
	for (int i = 1; i < vec_x.size(); i++) {
		double step = (vec_x[i] - vec_x[i - 1]) / n;
		double current_x = vec_x[i - 1];
		double current_y = vec_y[i - 1];
		double current_der_y = vec_der_y[i - 1];

		for (int j = 0; j < n; j++) {
			current_y = runge_kutta_double_rec(current_x, current_y, current_der_y, step);
			current_x = current_x + step;
		}

		double y = current_y;

		current_x = vec_x[i - 1];
		n = n * 2;
		step = (vec_x[i] - vec_x[i - 1]) / n;
		current_y = vec_y[i - 1];
		current_der_y = vec_der_y[i - 1];

		for (int j = 0; j < n; j++) {
			current_y = runge_kutta_double_rec(current_x, current_y, current_der_y, step);
			current_x = current_x + step;
		}

		while (fabs(current_y - y) > (pow(2, 4) - 1) * acc) {
			y = current_y;
			n = n * 2;
			step = (vec_x[i] - vec_x[i - 1]) / n;
			current_x = vec_x[i - 1];
			current_y = vec_y[i - 1];
			current_der_y = vec_der_y[i - 1];
			for (int j = 0; j < n; j++) {
				current_y = runge_kutta_double_rec(current_x, current_y, current_der_y, step);
				current_x = current_x + step;
			}
		}
		vec_y[i] = current_y;
		final_step = step;
	}
	return final_step;
}

void task_3() {
	double step = (b - a) / 10;
	double Yk = -2, Yk_1 = 0;
	double x;
	std::cout << "Task 3 table (step = (b - a) / 10)" << std::endl;
	std::cout << "-----------------\n";
	std::cout << "|   X|         Y|\n";
	std::cout << "-----------------\n";
	for (int i = 0; i <= 10; i++) {
		x = a + i * step;
		std::cout << "|" << std::setw(4) << x << "|" << std::setw(10) << Yk << "|" << std::endl;
		Yk = runge_kutta_double_rec(x, Yk, Yk_1, step);
	}
	std::cout << "-----------------\n";
}

int main() {
	
	const double eps = 10e-2;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> der_y;
	double step;

	double accuracy = runge_kutta_method(eps, x, y, der_y, step);

	std::cout << "Runge method" << std::endl;
	std::cout << "---------------------------------\n";
	std::cout << "|   X|         Y|          Error|\n";
	std::cout << "---------------------------------\n";
	for (int i = 0; i < x.size(); i++) {
		std::cout << "|" << std::setw(4) << x[i] << "|" << std::setw(10) << y[i] << "|" << std::setw(15) << fabs(func(x[i]) - y[i]) << "|" << std::endl;
	}
	std::cout << "---------------------------------\n";
	std::cout << "Final step(runge method) = " << step << std::endl << std::endl;

	double step2 =  double_recalculation(accuracy, x, y, der_y);
	std::cout << "Double recalculation" << std::endl;
	std::cout << "---------------------------------\n";
	std::cout << "|   X|         Y|          Error|\n";
	std::cout << "---------------------------------\n";
	for (int i = 0; i < x.size(); i++) {
		std::cout << "|" << std::setw(4) << x[i] << "|" << std::setw(10) << y[i] << "|" << std::setw(15) << fabs(func(x[i]) - y[i]) << "|" << std::endl;
	}
	std::cout << "---------------------------------\n";
	std::cout << "Final step(double recalculation) = " << step2 << std::endl << std::endl;

	task_3();

	system("pause");
	return 0;
}
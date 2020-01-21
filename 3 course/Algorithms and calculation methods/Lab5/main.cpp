#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "solveMatrix.h"
#include "Misc.h"
#include "Integral.h"

//[1,3]
//X = 0 Ц многочлени Ћежандра,
//Y = 0 Ц схема Їдиного под≥лу,
//Z = 0 Ц ≥нтегруванн€ коеф≥ц≥Їнт≥в нормальноњ системи за узагальненою формулою —≥мпсона,

double getResult(double current_x, line sol, int polinom_power) {
	double y = 0;
	for (int i = 0; i < polinom_power; i++) {
		y = y + sol[i] * Legandr(i, current_x);
	}
	return y;
}

line getPol(int polinom_power) {
	matrix mat = matrix(polinom_power, line(polinom_power + 1));
	for(int i = 0; i < mat.size(); i++) {
		for (int j = 0; j <= i; j++) {
			double value = simpsonMethod(polinom_power, i, j);
			mat[i][j] = value;
			mat[j][i] = value;
		}

		mat[i][polinom_power] = simpsonMethod(polinom_power, i, polinom_power);
	}
	return singleDivision(mat);
}

int main() {
	double eps = 10e-2;
	int steps_amount = 10;
	double step = (b - a) / (double)steps_amount;
	int polinom_power = 2;
    double deviation;
	double tmp, current_x;

	do {
		polinom_power++;
		deviation = 0;

		line polinom = getPol(polinom_power);

		current_x = a;
		for (int i = 0; i <= steps_amount; i++) {
			tmp = func(current_x) - getResult(current_x, polinom, polinom_power);
			deviation = deviation + tmp * tmp;
			current_x = current_x + step;
		}
		deviation = sqrt(deviation / (steps_amount + 1));
		std::cout << "Current deviation: " << deviation << std::endl;
	} while (deviation > eps);

	std::cout << "---------------------------------\n";

	std::cout << "Final deviation = " << deviation << std::endl;
	std::cout << "Final polinomial power = " << polinom_power << std::endl << std::endl;

	std::ofstream file;
	file.open("res.txt");

	current_x = a;
	std::cout << "X and Y for graph\n";
	std::cout << "----------------\n";
	for (int i = 1; i <= steps_amount + 1; i++) {
		double res = getResult((double)current_x, getPol(polinom_power), polinom_power);
		file << current_x << ";" << res << "\n\r";
		std::cout << "X: " << std::setw(3) << current_x << "  Y: " << res << std::endl;
		current_x = current_x + step;
	}
	std::cout << "----------------\n";

	file.close();

	system("pause");
	return 0;
} 
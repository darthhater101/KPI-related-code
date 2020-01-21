#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <algorithm>

typedef std::vector<std::vector<double>> matrix;
typedef std::vector<double> line;

void printMatrix(matrix mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			std::cout << std::setw(2) << mat[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printLine(line line)
{
	int k = 1;
	for (auto i : line)
	{
		std::cout << "x[" << k << "] = " << i << std::endl;
		k++;
	}
	std::cout << std::endl;
}

void divideLine(matrix& mat, int line, double elem)
{
	for (auto& i : mat[line])
	{
		i = i / elem;
	}
}

void substructLines(matrix& mat, int line1, int line2)
{
	double coef = mat[line1][line2];
	for (int i = 0; i < mat[line1].size(); i++)
	{
		mat[line1][i] = mat[line1][i] - mat[line2][i] * coef;
	}
}

line getResult(matrix mat)
{
	line result;
	double root;
	int s;

	int n = mat.size() - 1;
	int m = mat[n].size() - 1;

	result.push_back(mat[n][m] / mat[n][m - 1]);

	for (int i = mat.size() - 2; i >= 0; i--)
	{
		s = 0;
		root = mat[i][mat[i].size() - 1];
		for (int j = mat.size() - 1; j >= 0; j--)
		{
			if (s > result.size() - 1) break;
			root = root - mat[i][j] * result[s];
			s++;
		}
		result.push_back(root);
	}

	return result;
}

bool isValidForDivision(matrix mat) 
{
	for (int i = 0; i < mat.size(); i++) 
	{
		if (mat[i][i] == 0) return false;
	}
	return true;
}

bool singleDivision(matrix mat, line& results)
{
	if (!isValidForDivision(mat)) return false;

	divideLine(mat, 0, mat[0][0]);
	substructLines(mat, 1, 0);
	substructLines(mat, 2, 0);
	substructLines(mat, 3, 0);

	divideLine(mat, 1, mat[1][1]);
	substructLines(mat, 2, 1);
	substructLines(mat, 3, 1);

	divideLine(mat, 2, mat[2][2]);
	substructLines(mat, 3, 2);

	divideLine(mat, 3, mat[3][3]);

	results = getResult(mat);

	return true;
}


bool diagonalDominating(matrix mat)
{
	double sum = 0;
	bool flag = true;

	for (int i = 0; i < mat.size(); i++) 
	{
		sum = 0;
		for (int j = 0; j < mat[i].size() - 1; j++) 
		{
			if (i != j) {
				sum += fabs(mat[i][j]);
			}
		}
		if (sum > mat[i][i]) return false;
	}

	return flag;
}

bool seidelMethod(matrix mat, double eps, int maxit, bool& done, line& results)
{
	if (!diagonalDominating(mat))
	{
		return false;
	}

	results = { 0.0, 0.0, 0.0, 0.0 };
	line prev = { 0.0, 0.0, 0.0, 0.0 };
	line beta = { 0.0, 0.0, 0.0, 0.0 };
	matrix newMat = { {}, {}, {}, {} };

	for (int i = 0; i < beta.size(); i++)
	{
		beta[i] = mat[i][mat[i].size() - 1] / mat[i][i];
	}

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size() - 1; j++)
		{
			if (i != j)
			{
				newMat[i].push_back(-mat[i][j] / mat[i][i]);
			}
			else newMat[i].push_back(0);
		}
	}

	double q = 0.0;
	for (int i = 0; i < newMat.size(); i++)
	{
		double max = 0.0;
		for (int j = 0; j < newMat[i].size(); j++)
		{
			max = fabs(newMat[i][j]) + max;
		}
		if (max > q)
		{
			q = max;
		}
	}

	double sum1, sum2, temp, norma;

	int iters = 1;

	do
	{
		prev = results;

		for (int i = 0; i < newMat.size(); i++)
		{
			sum1 = 0.0;
			sum2 = 0.0;
			for (int j = i; j < newMat[i].size(); j++)
			{
				sum1 = sum1 + newMat[i][j] * results[j];
			}
			for (int j = 0; j < i; j++)
			{
				sum2 = sum2 + newMat[i][j] * results[j];
			}
			results[i] = beta[i] + sum1 + sum2;
		}

		temp = 0.0;
		norma = 0.0;
		for (int i = 0; i < prev.size(); i++)
		{
			temp = fabs(prev[i] - results[i]);
			if (temp > norma)
			{
				norma = temp;
			}
		}

		iters++;
		if (iters == maxit)
		{
			done = false;
			return true;
		}

	} while (norma > (1 - q) * eps / q);

	return true;
}

int main()
{
	matrix slar = {
		{20, 20, 20, 0, 180},
		{16, 37, 14, 6, 163},
		{18, 6, 33, 8, 218},
		{16, 9, 14, 13, 142}
	};

	matrix slarIteration = { //4 строка была изменена путем отнимания от 4 строки 3-ей умноженой на 2
		{20, 10, 5, 0, 180}, //1 строка была изменена вручную, так как было не очень удобно приводить ее к виду
		{16, 37, 14, 6, 163},//готовому к итерационному методу
		{18, 6, 33, 8, 218},
		{6, -1, 4, 13, 52}
	};

	line divisionResults;
	std::cout << "Single division method" << std::endl;
	if(singleDivision(slar, divisionResults))
	{
		std::reverse(begin(divisionResults), end(divisionResults));
		printLine(divisionResults);
	}
	else
	{
		std::cout << "Matrix has 0 on main diagonal" << std::endl;
	}

	std::cout << "Matrixes is different so roots are different" << std::endl;

	bool done = true;
	line iterationResults;
	std::cout << "Seidel method" << std::endl;
	if (seidelMethod(slarIteration, 1e-5, 200, done, iterationResults))
	{
		if (done == false)
		{
			std::cout << "Accuracy not achieved" << std::endl;
		}
		printLine(iterationResults);
	}
	else
	{
		std::cout << "Matrix has no diagonally dominant" << std::endl;
	}


	system("pause");

	return 0;
}
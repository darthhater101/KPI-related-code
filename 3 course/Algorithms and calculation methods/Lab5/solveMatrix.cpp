#include "solveMatrix.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

void printMatrix(matrix mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			std::cout << std::setw(7) << mat[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

line singleDivision(matrix mat)
{
	for (int i = 0; i < mat.size(); i++) {
		divideLine(mat, i, mat[i][i]);
		for (int j = i + 1; j < mat.size(); j++) {
			substructLines(mat, j, i);
		}
	}
	return getResult(mat);
}

void substructLines(matrix & mat, int line1, int line2)
{
	double coef = mat[line1][line2];
	for (int i = 0; i < mat[line1].size(); i++)
	{
		mat[line1][i] = mat[line1][i] - mat[line2][i] * coef;
	}

}

void divideLine(matrix & mat, int line, double elem)
{
	for (auto& i : mat[line])
	{
		i = i / elem;
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
	std::reverse(std::begin(result), std::end(result));
	return result;
}

#pragma once
#include <vector>

typedef std::vector<std::vector<double>> matrix;
typedef std::vector<double> line;

void printMatrix(matrix mat);
line singleDivision(matrix mat);
void substructLines(matrix& mat, int line1, int line2);
void divideLine(matrix& mat, int line, double elem);
line getResult(matrix mat);
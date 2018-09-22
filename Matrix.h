#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include "RandomGeneratorFloat.h"

class Matrix
{
private:
	std::vector<std::vector<float>> data;
public:
	int rows;
	int cols;
	Matrix(int i, int j);
	static Matrix fromArray(std::vector<float> arr);
	Matrix map(std::function<float(float, int, int)>);
	static Matrix map(Matrix matrix, std::function<float(float, int, int)>);
	static Matrix subtract(Matrix a, Matrix b);
	std::vector<float> toArray();
	Matrix randomize();
	Matrix add(Matrix n);
	Matrix add(float n);
	static Matrix tranpose(Matrix a);
	static Matrix multiply(Matrix a, Matrix b);
	Matrix multiply(Matrix a);
	Matrix multiply(float a);
	friend std::ostream& operator<<(std::ostream& out, Matrix a);
};


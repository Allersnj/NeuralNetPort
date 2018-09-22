#include "Matrix.h"

Matrix::Matrix(int i, int j) : rows{ i }, cols{ j }
{
	for (int k = 0; k < rows; ++k)
	{
		std::vector<float> a;
		a.resize(cols);
		data.push_back(a);
	}
}

Matrix Matrix::fromArray(std::vector<float> arr)
{
	return Matrix(arr.size(), 1).map([arr](float e, int i, int j) -> float { return arr[i]; });
}

Matrix Matrix::map(std::function<float(float, int, int)> func)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			float val = data[i][j];
			data[i][j] = func(val, i, j);
		}
	}
	return *this;
}

Matrix Matrix::map(Matrix matrix, std::function<float(float, int, int)> func)
{
	return matrix.map(func);
}

Matrix Matrix::subtract(Matrix a, Matrix b)
{
	if (a.rows != b.rows || a.cols != b.cols)
	{
		std::cout << "Both matrices must be same size when subtracting.\n";
		return Matrix(0, 0);
	}
	return Matrix(a.rows, a.cols).map([a, b](float e, int i, int j) -> float { return a.data[i][j] - b.data[i][j]; });
}

std::vector<float> Matrix::toArray()
{
	std::vector<float> arr;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			arr.push_back(data[i][j]);
	}
	return arr;
}

Matrix Matrix::randomize()
{
	RandomGenerator random(0.0f, 1.0f);
	return map([&random](float, int, int) -> float {return random.get() * 2 - 1; });
}
Matrix Matrix::add(Matrix n)
{
	if (n.rows != rows || n.cols != cols)
	{
		std::cout << "Both matrices must be the same size when adding.\n";
		return *this;
	}
	return map([n](float e, int i, int j) -> float { return e + n.data[i][j]; });
}

Matrix Matrix::add(float n)
{
	return map([n](float e, int i, int j) -> float { return e + n; });
}

Matrix Matrix::tranpose(Matrix a)
{
	return Matrix(a.cols, a.rows).map([a](float e, int i, int j) -> float { return a.data[j][i]; });
}

Matrix Matrix::multiply(Matrix a, Matrix b)
{
	if (a.cols != b.rows)
	{
		std::cout << "Columns of Matrix A must match rows of Matrix B.\n";
		std::cout << a.cols << " " << b.rows << '\n';
		return a;
	}

	return Matrix(a.rows, b.cols).map([a, b](float e, int i, int j) -> float { float sum = 0; for (int k = 0; k < a.cols; ++k) { sum += a.data[i][k] * b.data[k][j]; } return sum; });
}

Matrix Matrix::multiply(Matrix a)
{
	if (a.rows != rows || a.cols != cols)
	{
		std::cout << "Columns and rows of A must match columns and rows of B.\n";
		return *this;
	}

	return map([a](float e, int i, int j) -> float { return e * a.data[i][j]; });
}

Matrix Matrix::multiply(float a)
{
	return map([a](float e, int i, int j) -> float { return e * a; });
}

std::ostream& operator<<(std::ostream& out, Matrix a)
{
	for (int i = 0; i < a.rows; ++i)
	{
		for (int j = 0; j < a.cols; ++j)
		{
			out << a.data[i][j];
			if (j == a.cols - 1)
			{
				if (i == a.rows - 1)
				{
					out << "\n\n";
				}
				else
					out << ",\n";
			}
			else
				out << ", ";
		}
	}
	return out;
}
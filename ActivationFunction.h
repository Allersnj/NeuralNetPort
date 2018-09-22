#pragma once
#include <functional>

class ActivationFunction
{
public:
	std::function<float(float e, int i, int j)> func, dfunc;
	ActivationFunction(std::function<float(float e, int i, int j)> x, std::function<float(float e, int i, int j)> y);
};


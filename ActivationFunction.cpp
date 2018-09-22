#include "ActivationFunction.h"

ActivationFunction::ActivationFunction(std::function<float(float e, int i, int j)> x, std::function<float(float e, int i, int j)> y) : func{ x }, dfunc{ y }
{
}


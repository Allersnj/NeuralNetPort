#include "RandomGeneratorFloat.h"

RandomGenerator::RandomGenerator(float min, float max) : dis{ std::uniform_real_distribution<float>(min, max) }
{
	f.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

float RandomGenerator::get()
{
	return dis(f);
}


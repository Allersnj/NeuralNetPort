#pragma once
#include <random>
#include <chrono>

class RandomGenerator
{
private:
	std::default_random_engine f;
	std::uniform_real_distribution<float> dis;
public:
	RandomGenerator(float min = 0.0f, float max = 10.0f);
	float get();
};


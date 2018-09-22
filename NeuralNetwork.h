#pragma once
#include <iostream>
#include "Matrix.h"
#include "ActivationFunction.h"

class NeuralNetwork
{
private:
	int input_nodes;
	int hidden_nodes;
	int output_nodes;
	ActivationFunction sigmoid;
	ActivationFunction tangenth;
	ActivationFunction activation_func;
	Matrix weights_ih;
	Matrix weights_ho;
	Matrix bias_h;
	Matrix bias_o;
	float learning_rate = 0.1f;
public:
	NeuralNetwork(int a, int b, int c);
	void setActivationFunction(ActivationFunction func);
	void setLearningRate(float rate);
	std::vector<float> predict(std::vector<float> input_array);
	void train(std::vector<float> input_array, std::vector<float> target_array);
	void mutate(std::function<float(float, int, int)> func);

};


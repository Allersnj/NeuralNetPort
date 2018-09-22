#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int a, int b, int c) : input_nodes{ a }, hidden_nodes{ b }, output_nodes{ c }, sigmoid { ActivationFunction([](float e, int i, int j) -> float { return 1 / (1 + powf(2.718281828, -e)); }, [](float e, int i, int j) -> float { return e * (1 - e); }) }, tangenth{ ActivationFunction([](float e, int i, int j) -> float { return tanh(e); }, [](float e, int i, int j) -> float { return 1 - (e * e); }) }, activation_func{ sigmoid }, weights_ih{ Matrix(hidden_nodes, input_nodes) }, weights_ho{ Matrix(output_nodes, hidden_nodes) }, bias_h{ Matrix(hidden_nodes, 1) }, bias_o{ Matrix(output_nodes, 1) }
{
	weights_ih.randomize();
	weights_ho.randomize();
	bias_h.randomize();
	bias_o.randomize();
}

void NeuralNetwork::setActivationFunction(ActivationFunction func)
{
	activation_func = func;
}

void NeuralNetwork::setLearningRate(float rate)
{
	learning_rate = rate;
}

std::vector<float> NeuralNetwork::predict(std::vector<float> input_array)
{
	Matrix inputs = Matrix::fromArray(input_array);
	Matrix hidden = Matrix::multiply(weights_ih, inputs);
	hidden.add(bias_h);
	hidden.map(activation_func.func);
	Matrix output = Matrix::multiply(weights_ho, hidden);
	output.add(bias_o);
	output.map(activation_func.func);
	return output.toArray();
}

void NeuralNetwork::train(std::vector<float> input_array, std::vector<float> target_array)
{
	Matrix inputs = Matrix::fromArray(input_array);
	Matrix hidden = Matrix::multiply(weights_ih, inputs);
	hidden.add(bias_h);
	hidden.map(activation_func.func);

	Matrix outputs = Matrix::multiply(weights_ho, hidden);
	outputs.add(bias_o);
	outputs.map(activation_func.func);

	Matrix targets = Matrix::fromArray(target_array);

	Matrix output_errors = Matrix::subtract(targets, outputs);

	Matrix gradients = Matrix::map(outputs, activation_func.dfunc);
	gradients.multiply(output_errors);
	gradients.multiply(learning_rate);
	

	Matrix hidden_T = Matrix::tranpose(hidden);
	Matrix weight_ho_deltas = Matrix::multiply(gradients, hidden_T);

	weights_ho.add(weight_ho_deltas);
	bias_o.add(gradients);

	Matrix who_t = Matrix::tranpose(weights_ho);
	Matrix hidden_errors = Matrix::multiply(who_t, output_errors);

	Matrix hidden_gradient = Matrix::map(hidden, activation_func.dfunc);
	hidden_gradient.multiply(hidden_errors);
	hidden_gradient.multiply(learning_rate);

	Matrix inputs_T = Matrix::tranpose(inputs);
	Matrix weight_ih_deltas = Matrix::multiply(hidden_gradient, inputs_T);

	weights_ih.add(weight_ih_deltas);
	bias_h.add(hidden_gradient);
}

void NeuralNetwork::mutate(std::function<float(float, int, int)> func)
{
	weights_ih.map(func);
	weights_ho.map(func);
	bias_h.map(func);
	bias_o.map(func);
}
#include <iostream>
#include "Matrix.h"
#include "NeuralNetwork.h"

struct trainingData
{
	std::vector<float> inputs;
	std::vector<float> outputs;
};

int main()
{
	trainingData data1;
	trainingData data2;
	trainingData data3;
	trainingData data4;
	data1.inputs = std::vector<float>{ 1.0f, 0.0f };
	data1.outputs = std::vector<float>{ 1.0f };
	data2.inputs = std::vector<float>{ 0.0f, 1.0f };
	data2.outputs = std::vector<float>{ 1.0f };
	data3.inputs = std::vector<float>{ 1.0f, 1.0f };
	data3.outputs = std::vector<float>{ 0.0f };
	data4.inputs = std::vector<float>{ 0.0f, 0.0f };
	data4.outputs = std::vector<float>{ 0.0f };
	std::vector<trainingData> training;
	training.push_back(data1);
	training.push_back(data2);
	training.push_back(data3);
	training.push_back(data4);
	NeuralNetwork brain(2, 2, 1);
	RandomGenerator random(0, 4);
	
	
	for (int i = 0; i < 1000; ++i)
	{
		int index = floorf(random.get());
		brain.train(training[index].inputs, training[index].outputs);
	}

	std::vector<float> shouldBeTrue = brain.predict(std::vector<float>{0.0f, 1.0f});
	std::cout << shouldBeTrue[0] << '\n';
	system("pause");

}

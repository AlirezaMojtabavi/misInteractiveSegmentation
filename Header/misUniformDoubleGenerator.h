#pragma once

#include <random>

class misUniformDoubleGenerator
{
	double MinNumber;
	double MaxNumber;

	//std::default_random_engine generator;
	std::uniform_real_distribution<double> * distribution;

public:
	misUniformDoubleGenerator(double Min,double Max);
	~misUniformDoubleGenerator(void);

	double GenerateNewDoubleRandom();

	double GetMin();
	double GetMax();
	
	/*void SetMin(double val);
	void SetMax(double val);*/
};


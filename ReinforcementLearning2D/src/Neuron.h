#ifndef NeuronHPP
#define NeuronHPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

struct Connection
{
	double weight;
	double detlaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val);
	double getOutputVal(void) const;
	void feedForward(const Layer &prevLayer);
	void calcOutpuGradients(double targetVal);
	void calcHiddenGradients(const Layer &nextlayer);
	void updateInputWeights(Layer &prevLayer);


private:
	static double eta;
	static double alpha;
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	double sumOOW(const Layer &nextLayer) const;
	double m_outputVal;
	std::vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};

#endif

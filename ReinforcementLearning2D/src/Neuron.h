#ifndef NeuronHPP
#define NeuronHPP

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

struct Connection
	//Represent the connexion beween two neurons
{
	double weight;			//the current weight
	double deltaWeight;		//weight variation (requisite for backpropagation)
	double oldWeight;		//used in gradientStochastic
};

class Neuron;
typedef vector<Neuron> Layer; //Layer[Neuron]

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);					//Compute the output of a neuron
	void calcOutputGradients(double targetVals);				//Compute gradient for backpropagation
	void calcHiddenGradients(const Layer &nextLayer);			//Same thing on hidden layers
	void updateInputWeights(Layer &prevLayer);					//Update weight using backpropagation method
	void gradientStochastic(double leearningRate);				//Random gradient descent function 
	void keepOldWeights();										//Return of the network in the previous state
private:
	static double eta;											//[0.0...1.0] overall net training rate
	static double alpha;										//[0.0...n] multiplier of last weight change [momentum]
	static double transferFunction(double x);					//Threshold function
	static double transferFunctionDerivative(double x);			//Derived threshold function (requisite for backpropagation)
	static double randomWeight(void) { return rand() / double(RAND_MAX); }	// randomWeight: 0 - 1
	double sumDOW(const Layer &nextLayer) const;				//An error function (resuisite for backpropagation)
	double m_outputVal;
	vector<Connection> m_outputWeights;							//All the connexion with the following layer
	unsigned m_myIndex;											//Number of the neuron in the layer 
	double m_gradient;											
};

#endif
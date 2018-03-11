#ifndef NetworkHPP
#define NetworkHPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
using namespace std;

#include "Neuron.h"

typedef vector<Neuron> Layer;

class Net
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);							//Compute the output of the network
	void backProp(const vector<double> &targetVals);							//Backpropagation algorithm
	void getResults(vector<double> &resultVals) const;							//Stock the output of the network in resultVals
	double getRecentAverageError(void) const { return m_recentAverageError; }
	void gradientStochastic(double learningRate);								//Random gradient descent function 
	void keepOldWeights();														//return of the network in the previous state


private:
	vector<Layer> m_layers;														//m_layers[layerNum][neuronNum]
	double m_error;																//Error function
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
};


#endif // NETWORKFPP


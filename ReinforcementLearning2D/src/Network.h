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
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; }
	void gradientStochastic(double fitness);

private:
	vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
};


#endif // NETWORKFPP


#ifndef NetworkHPP
#define NetworkHPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Neuron.h"

typedef std::vector<Neuron> Layer;

class Net
{
public:
	Net(const std::vector<unsigned> &topology);
	void feedForward(const std::vector<double> &inputVals);
	void backProp(const std::vector<double> &targetVals);
	void getResults(std::vector<double> &resultVals) const;
	int getReward(float state);
private:
	std::vector<Layer> m_layers; // m_layers[layerNum][neuronneNum]
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

#endif
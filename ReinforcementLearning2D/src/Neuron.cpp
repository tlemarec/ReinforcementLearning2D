// Neuron.cpp : define the neuron class wich is use to build the network
//

#include "Neuron.h"

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	unsigned m_myIndex = myIndex;
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

void Neuron::setOutputVal(double val)
{
	m_outputVal = val;
}

double Neuron::getOutputVal(void) const
{
	return m_outputVal;
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
	//Les poids que l'on veut changer sont dans le conteneur Connection des neuronnes de la couche précédente

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].detlaWeight;
		double newDeltaWeight =
			eta
			* neuron.getOutputVal()
			* m_gradient
			+ alpha
			* oldDeltaWeight;
		neuron.m_outputWeights[m_myIndex].detlaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}


double Neuron::sumOOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	//Somme des contribution à l'erreur du neuronne que l'on considère

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumOOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutpuGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}



double Neuron::transferFunction(double x)
{
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	return 1.0 - x * x;;
}



void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal()*prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}
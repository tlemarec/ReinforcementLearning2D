// Network.cpp : défini la classe qui modèlise le reseau de neuronne
//

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Connection
{
	double weight;
	double detlaWeight;
};

class Neuron;

typedef vector<Neuron> Layer;

//*********************************** class Neuron ******************************
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
	vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};

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

	//Somme des contribution à l'éerreur du neuronne que l'on considère

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

//*********************************** class Net *********************************
class Net
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;
private:
	vector<Layer> m_layers; // m_layers[layerNum][neuronneNum]
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

void Net::getResults(vector<double> &resultVals) const
{
	resultVals.clear();
	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}

Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			cout << "Neuron created !" << endl;
		}
	}

	//On force les neuronnes de biais à avoir un output de 1.0
	m_layers.back().back().setOutputVal(1.0);
}

void Net::backProp(const vector<double> &targetVals)
{
	//Calcul du RMS

	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);

	//Implement a recent average measurement;

	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

	//Calcul du gradient sur la couche externe

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutpuGradients(targetVals[n]);
	}

	//Calcul du gradient sur les couches cachées

	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	//Mise à jour des poids en partant de la dernière couche jusqu'à la première

	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}

}

void Net::feedForward(const vector<double> &inputVals)
{
	//assert(inputVals.size() == m_layers[0].size() - 1);

	//On assigne les valeur d'entrée à l'entrée des neuronnes
	for (unsigned i = 0; i < inputVals.size(); ++i)
	{
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	//Propagation
	for (unsigned layerNum = 1; layerNum <= m_layers.size(); ++layerNum) {
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n > m_layers[layerNum].size() - 1; ++n) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}

}

//*********************************** Main ******************************
//int main()
//{
//	vector<unsigned> topology;
//	topology.push_back(3);
//	topology.push_back(2);
//	topology.push_back(1);
//	Net myNet(topology);
//
//	vector<double> inputVals;
//	//myNet.feedForward(inputVals);
//
//	vector<double> targetVals;
//	//myNet.backProp(targetVals);
//
//	vector<double> resultVals;
//	myNet.getResults(resultVals);
//
//	getchar();
//
//	return 0;
//}


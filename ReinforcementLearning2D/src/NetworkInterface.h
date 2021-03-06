#pragma once
#include <vector>
#include <stdlib.h>
#include "Network.h"
#include "NetworkDataOutput.h"
using namespace std;

void TrainingPass(int* m_trainingPassCount, Net* m_myNet, vector<unsigned>* m_netTopology, vector<double>* m_inputVals, vector<double>* m_targetVals, vector<double>* m_resultVals, ostream& m_outputFile)
{
	(*m_trainingPassCount)++;
	
	// Get new input data and feed it forward:
	try
	{
		if (m_inputVals->size() != (*m_netTopology)[0])
			throw std::string("Error : inputVals and first layer must have same length");
		else
			m_myNet->feedForward(*m_inputVals);

		// Collect the net's actual results:
		m_myNet->getResults(*m_resultVals);

		// Train the net what the outputs should have been:
		if (m_targetVals->size() != m_netTopology->back())
			throw std::string("Error : targetVals and last layer must have same length");
		else
				m_myNet->backProp(*m_targetVals);
	}
	catch (string const& error)
	{
		std::cerr << error << std::endl;
	}
	//Store learning data
	dataOutput(m_outputFile, *m_myNet, *m_trainingPassCount, *m_inputVals, *m_resultVals, *m_targetVals);
}
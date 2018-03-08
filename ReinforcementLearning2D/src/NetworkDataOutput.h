#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Network.h"

void vectorValsOutput(ostream& m_Stream, std::string label, std::vector<double> &v)
{
	m_Stream << label << " ";
	for (unsigned i = 0; i < v.size(); ++i)
	{
		m_Stream << v[i] << " ";
	}
	m_Stream << std::endl;
}


void dataOutput(ostream& m_Stream, Net m_Net, int m_trainingPass, std::vector<double> m_inputVals, std::vector<double> m_resultVals, std::vector<double> m_targetVals)
{
	m_Stream << endl << "Pass : " << m_trainingPass << endl;
	vectorValsOutput(m_Stream, ": Inputs :", m_inputVals);
	vectorValsOutput(m_Stream,"Outputs:", m_resultVals);
	vectorValsOutput(m_Stream,"Targets:", m_targetVals);
	m_Stream << "Net recent average error: " << m_Net.getRecentAverageError() << endl; // Report how well the training is working, average over recent
}


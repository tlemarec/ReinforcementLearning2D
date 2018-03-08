#pragma once

#include <vector>
#include <iostream>
#include <sstream>

void showVectorVals( std::string label, std::vector<double> &v)
{
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << std::endl;
}

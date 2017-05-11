/*
 * Net.h
 *
 *  Created on: May 10, 2017
 *      Author: mateus
 */

#ifndef NET_H_
#define NET_H_

#include <vector>
#include "Neuron.h"
#include <limits>

using namespace std;

class Net {
public:
	Net(const vector<unsigned> &topology);
	virtual ~Net();

	void feedForward (const vector<double> &inputVals);
	void backPropagation (const vector<double> &targetVals);
	void getResults (vector<double> &resultVals);

	double m_error, m_recentAverageError, m_recentAverageSmoothingFactor;
private:
	vector<Layer> m_layers; // m_layers[numLayer][numNeuron]
};

#endif /* NET_H_ */

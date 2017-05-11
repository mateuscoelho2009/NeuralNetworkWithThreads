/*
 * Neuron.h
 *
 *  Created on: May 10, 2017
 *      Author: mateus
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <vector>
#include "Connection.h"
#include <cstdlib>
#include <cmath>

using namespace std;

class Neuron {
public:
	typedef vector<Neuron> Layer;

	Neuron(unsigned numOutputs, unsigned myIndex);
	virtual ~Neuron();

	void feedForward (const Layer &prevLayer);
	void setOutputVal (double outputVal) {
		m_outputVal = outputVal;
	};
	double getOutputVal () const {
		return m_outputVal;
	};
	double getGradient () const {
		return m_gradient;
	};
	void calcOutputGradients (double targetVal) {
		double delta = targetVal - m_outputVal;
		m_gradient = delta * Neuron::tranferFunctionDerivative(m_outputVal);
	}
	void calcHiddenGradients (const Layer &nextLayer);
	void updateInputWeights (Layer &prevLayer);

private:
	static double eta, // [0.0..1.0]
				  alpha; //[0.0..n]

	static double transferFunction (double x) {
		// tanh - range [-1.0..1.0]
		return tanh(x);
	}
	static double tranferFunctionDerivative (double x) {
		// para tanh
		return 1.0 - x * x;
	}
	double sumDOW (const Layer &nextLayer) const;
	static double randomWeight () {
		return rand() / double(RAND_MAX);
	}

	double m_outputVal, m_gradient;
	unsigned m_myIndex;
	vector<Connection> m_outputWeights;

};

typedef vector<Neuron> Layer;

#endif /* NEURON_H_ */

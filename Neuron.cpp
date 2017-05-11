/*
 * Neuron.cpp
 *
 *  Created on: May 10, 2017
 *      Author: mateus
 */

#include "Neuron.h"

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned numOutputs, unsigned myIndex) {
	for (unsigned i = 0; i < numOutputs; i++) {
		m_outputWeights.push_back (Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

void Neuron::feedForward(const Layer &prevLayer) {
	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); n++) {
		double aux = prevLayer[n].getOutputVal();
		sum += aux * prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {
	double dow = sumDOW (nextLayer);
	m_gradient = dow * Neuron::tranferFunctionDerivative(m_outputVal);
}

double Neuron::sumDOW (const Layer &nextLayer) const {
	double sum = 0.0;

	// soma das contribuições aos nós alimentados
	for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
		sum += m_outputWeights[n].weight * nextLayer[n].getGradient();
	}

	return sum;
};

void Neuron::updateInputWeights(Layer &prevLayer) {
	for (unsigned n = 0; n < prevLayer.size(); n++) {
		Neuron &neuron = prevLayer[n];

		/*
		 * eta = 0.0 (aprendizado lento)
		 * 		 0.2 (aprendizado médio)
		 * 		 1.0 (aprendizado "maluco")
		 *
		 * alpha = 0.0 (sem momentum)
		 * 		   0.5 (momentum moderado)
		 */
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
		double newDeltaWeight = eta // Overrall Learning Rate
								* neuron.getOutputVal()
								* m_gradient
								// momentum
								+ alpha
								* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

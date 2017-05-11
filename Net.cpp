/*
 * Net.cpp
 *
 *  Created on: May 10, 2017
 *      Author: mateus
 */

#include "Net.h"
#include <iostream>
#include <cassert>
#include "Neuron.h"

Net::Net(const vector<unsigned> &topology) {
	unsigned numLayers = topology.size();

	cout << "Creating Neural Network" << endl;

	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++) {
		m_layers.push_back(Layer());
		unsigned numOutputs = 0;

		if (layerNum < numLayers - 1)
			numOutputs = topology[layerNum + 1];

		// <= pelo bias
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			cout << "Made a Neuron" << endl;
		}
	}

	cout << "Neural Network Created" << endl;

	m_layers.back().back().setOutputVal(1.0);

	m_error = 0.0;
	m_recentAverageError = 0.0;
	m_recentAverageSmoothingFactor = 0.0;
}

Net::~Net() {
	// TODO Auto-generated destructor stub
}

void Net::feedForward(const vector<double> &inputVals) {
	assert (inputVals.size() == m_layers[0].size() - 1);

	// Assign the input values into the input Neurons
	for (unsigned i = 0; i < inputVals.size(); i++) {
		m_layers[0][i].setOutputVal (inputVals[i]);
	}

	for (unsigned layerNum = 1; layerNum < m_layers.size(); layerNum++) {
		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; n++) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

void Net::backPropagation (const vector<double> &targetVals) {
	// calculate the overall net error
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt (m_error); // RMS

	// Implementar uma medida de média de erro recente
	m_recentAverageError = (m_recentAverageError * m_recentAverageError + m_error)
			/ (m_recentAverageSmoothingFactor + 1.0);

	// Calcular os gradientes da camada externa
	for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
		outputLayer[n].calcOutputGradients (targetVals[n]);
	}

	// Calcular os gradientes das camadas "escondidas"
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; layerNum--) {
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		// TODO:  verificar aqui
		for (unsigned n = 0; n < hiddenLayer.size() - 1; n++) {
			hiddenLayer[n].calcHiddenGradients (nextLayer);
		}
	}

	// Atualizar pesos das conexões (Devido a isso aqui, provavelmente terá problema com threads)
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; layerNum--) {
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		// TODO:  verificar aqui
		for (unsigned n = 0; n < layer.size(); n++) {
			layer[n].updateInputWeights (prevLayer);
		}
	}
}

void Net::getResults(vector<double> &resultVals) {
	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size(); n++) {
		double aux = m_layers.back()[n].getOutputVal();
		resultVals.push_back(aux);
	}
}


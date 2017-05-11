/*
 * Main.cpp
 *
 *  Created on: May 10, 2017
 *      Author: mateus
 */

#include <vector>
#include "Net.h"
#include <iostream>

using namespace std;

double step05 (double x) {
	if (x > 0.5) return 1;
	else return 0;
}

int main () {
	vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(1);


	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;

	double error = 10;
	int iter = 0;
	// Exemplo com XOR
	while (error > 0.05) { // Pode só colocar aqui tb pra garantir && iter < 2000) {
		error = 0;
		iter++;

		// 00 = 0
		inputVals.clear();
		targetVals.clear();

		inputVals.push_back(0);
		inputVals.push_back(0);

		targetVals.push_back(0);

		myNet.feedForward(inputVals);
		myNet.backPropagation(targetVals);

		error += myNet.m_error;

		// 01=1
		inputVals.clear();
		targetVals.clear();

		inputVals.push_back(0);
		inputVals.push_back(1);

		targetVals.push_back(1);

		myNet.feedForward(inputVals);
		myNet.backPropagation(targetVals);

		error += myNet.m_error;

		//10 = 1
		inputVals.clear();
		targetVals.clear();

		inputVals.push_back(1);
		inputVals.push_back(0);

		targetVals.push_back(1);

		myNet.feedForward(inputVals);
		myNet.backPropagation(targetVals);

		error += myNet.m_error;

		// 11 = 0
		inputVals.clear();
		targetVals.clear();

		inputVals.push_back(1);
		inputVals.push_back(1);

		targetVals.push_back(0);

		myNet.feedForward(inputVals);
		myNet.backPropagation(targetVals);

		error += myNet.m_error;

		cout << "iteração " << iter << ": " << "Erro: " << error << endl;
	}

	// 00 = 0
	inputVals.clear();

	inputVals.push_back(0);
	inputVals.push_back(0);

	myNet.feedForward(inputVals);
	myNet.getResults(resultVals);

	cout << "\n\nNeural Net Training Complete\nHere Are The Results" << endl;

	cout << "=======================\n" << "Entry: 0 0" << endl << "Output: " << resultVals[0]
			<< "\nAfter TransferFunction: "  << step05(resultVals[0]) << endl;

	// 01=1
	inputVals.clear();

	inputVals.push_back(0);
	inputVals.push_back(1);

	myNet.feedForward(inputVals);
	myNet.getResults(resultVals);

	cout << "=======================\n" << "Entry: 0 1" << endl << "Output: " << resultVals[0]
			<< "\nAfter TransferFunction: "  << step05(resultVals[0]) << endl;
	//10 = 1
	inputVals.clear();

	inputVals.push_back(1);
	inputVals.push_back(0);

	myNet.feedForward(inputVals);
	myNet.getResults(resultVals);

	cout << "=======================\n" << "Entry: 1 0" << endl << "Output: " << resultVals[0]
			<< "\nAfter TransferFunction: "  << step05(resultVals[0]) << endl;

	// 11 = 0
	inputVals.clear();

	inputVals.push_back(1);
	inputVals.push_back(1);

	myNet.feedForward(inputVals);
	myNet.getResults(resultVals);

	cout << "=======================\n" << "Entry: 1 1" << endl << "Output: " << resultVals[0]
			<< "\nAfter TransferFunction: "  << step05(resultVals[0]) << endl;;
}



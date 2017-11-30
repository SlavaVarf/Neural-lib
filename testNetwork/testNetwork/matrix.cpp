#include "stdafx.h"
#include "matrix.h"

/*void fileOpen(string path) {
	ofstream file(path);
}
*/

void fileWrite(string path, const char str[]) {
	ofstream file;
	file.open(path);
	file << str;
}

/*void file() {
	ofstream file("sas.txt");
	file << "sas";
}
*/
/*
void matrixCreation(int* neuronsPerLayer, int layersNum) {
	ofstream weightsFile("weights.txt");
	srand((unsigned)time(NULL));
	int *layerStart;
	int neuronsNum = 0;
	double **weights;
	layerStart = new int[layersNum];														//избавиться от дин массивов
	for (int i = 0; i < layersNum; i++) {
		layerStart[i] = neuronsNum;
		neuronsNum += neuronsPerLayer[i];
		cout << "layer " << i + 1 << " starting is " << layerStart[i] << " index" << endl;
	}
	weights = new double*[neuronsNum];
	for (int i = 0; i < neuronsNum; i++) {
		weights[i] = new double[i + 1];
		for (int j = 0; j < i + 1; j++) {
			weights[i][j] = 0;
			cout << weights[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < layersNum - 1; i++)
		for (int k = layerStart[i]; k < layerStart[i] + neuronsPerLayer[i]; k++) {
			for (int j = layerStart[i + 1]; j < layerStart[i + 1] + neuronsPerLayer[i + 1]; j++) {
				weights[j][k] = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
				cout << "[" << j << "][" << k << "]=" << weights[j][k] << endl;
			}
		}
	cout << endl;
	for (int i = 0; i < neuronsNum; i++) {
		for (int j = 0; j < i + 1; j++) {
			cout << weights[i][j] << "\t";
			weightsFile << weights[i][j] << "\t";
		}
		weightsFile << endl;
		cout << endl;
	}
	cout << endl;
	cout << weights[0][0];
}

void forwardWay(int* inputLayer, int* neuronsPerLayer, int layersNum) {
	for (int i = 0; i < layerStart[1]; i++) {
		cout << weights[0][0];
		weights[i][i] = inputLayer[i];
	}
	for (int i = 2; i <= layersNum; i++)
		for (int j = layerStart[i - 1]; j < layerStart[i - 1] + neuronsPerLayer[i - 1]; j++)
			for (int k = layerStart[i - 2]; k < layerStart[i - 2] + neuronsPerLayer[i - 2]; k++) {
				weights[j][j] = weights[j][j] + weights[j][j - 1] * weights[j - 1][j - 1];
				cout << "[" << j << "][" << j << "]=" << weights[j][j] << endl;
			}
}

double getWeight(int fNeuron, int tneuron) {						// from/to neuron
	return weights[tneuron][fNeuron];
}

void setWeight(int fNeuron, int tNeuron, double value) {			// from/to neuron
	weights[tNeuron][fNeuron] = value;
}
*/
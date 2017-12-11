#include "stdafx.h"
#include "matrix.h"

double ** matrixCreation(int* neuronsPerLayer, int layersNum) {
	srand((unsigned)time(NULL));
	int *layerStart;
	int neuronsNum = 0;
	double **weights;
	layerStart = new int[layersNum];
	for (int i = 0; i < layersNum; i++) {
		layerStart[i] = neuronsNum;
		neuronsNum += neuronsPerLayer[i];
	}
	weights = new double*[neuronsNum];
	for (int i = 0; i < neuronsNum; i++) {
		weights[i] = new double[i + 1];
		for (int j = 0; j < i + 1; j++)
			weights[i][j] = 0;
	}
	for (int i = 0; i < layersNum - 1; i++)
		for (int k = layerStart[i]; k < layerStart[i] + neuronsPerLayer[i]; k++)
			for (int j = layerStart[i + 1]; j < layerStart[i + 1] + neuronsPerLayer[i + 1]; j++)
				weights[j][k] = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
	writeToFile("weights.txt", weights, neuronsNum);
	return weights;

}

void writeToFile(string fileName, double **matrix, int neuronsNum) {
	ofstream file(fileName);
	for (int i = 0; i < neuronsNum; i++) {
		for (int j = 0; j < i + 1; j++)
			file << fixed << matrix[i][j] << "\t";
		file << "\n";
	}
	file.close();

};

int neuronsCounter(int* neuronsPerLayer, int layersNum) {
	int neuronsNum = 0;
	for (int i = 0; i < layersNum; i++) {
		neuronsNum += neuronsPerLayer[i];
	}
	return neuronsNum;
}															//продумать устройство forwardway
/*
void forwardWay(double** weights, int* inputLayer, int* neuronsPerLayer, int layersNum) {
	for (int i = 0; i < neuronsPerLayer[i]; i++) {
		weights[i][i] = inputLayer[i];
	}
	for (int i = 2; i <= layersNum; i++)
		for (int j = layerStart[i - 1]; j < layerStart[i - 1] + neuronsPerLayer[i - 1]; j++)
			for (int k = layerStart[i - 2]; k < layerStart[i - 2] + neuronsPerLayer[i - 2]; k++) {
				weights[j][j] = weights[j][j] + weights[j][j - 1] * weights[j - 1][j - 1];
				cout << "[" << j << "][" << j << "]=" << weights[j][j] << endl;
			}
}
*/
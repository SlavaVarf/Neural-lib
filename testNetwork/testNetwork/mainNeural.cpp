#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"
const int N = 4;
const int eduBase[N][3] = { { 1,0,1 },{ 1,1,1 },{ 0,1,1 },{ 0,0,0 } };
void main() {
	int expected;
	double **weights;
	int neuronsPerLayer[] = { 2,3,1 };
	int layersNum = 3, neuronsNum = 0;
	neuronsNum = neuronsCounter(neuronsPerLayer, layersNum);
	weights = matrixCreation(neuronsPerLayer, layersNum);
	for (int i = 0; i < N; i++) {
		cout << "epoch #" << i << "\t" << "Enter inputs" << "\n";
		for (int j = 0; j < neuronsPerLayer[0]; j++) {
			weights[j][j] = eduBase[i][j];
			expected = eduBase[i][j + 1];
		}
		weights = learning(weights, neuronsPerLayer, layersNum, expected);
		writeToFile("weights.txt", weights, neuronsNum);

	}
	exploitation(weights, neuronsPerLayer, layersNum);

	system("pause");
}
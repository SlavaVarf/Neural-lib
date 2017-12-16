#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"
void main() {
	int neuronsPerLayer[3] = { 2,3,1 };
	int eduBase[4][3] = { { 1,0,1 },{ 1,1,1 },{ 0,1,1 },{ 0,0,0 } };
	double expected;
	int layersNum = 3, neuronsNum = 0;
	double **weights;
	neuronsNum = neuronsCounter(neuronsPerLayer, layersNum);
	weights = matrixCreation(neuronsPerLayer, layersNum);
	for (int i = 0; i < 100; i++) {
		int k = rand() % 4 + 0;
		int j = 0;
		cout << "epoch #" << i << "\t" << "Enter inputs:" << "k = " << k << "\n";
		for (j = 0; j < neuronsPerLayer[0]; j++)				// сделать рандомно
			weights[j][j] = eduBase[k][j];
		expected = eduBase[k][j + 1];
		weights = cycle(weights, neuronsPerLayer, layersNum, expected);
	}
	exploitation(weights, neuronsPerLayer, layersNum);

	system("pause");
}
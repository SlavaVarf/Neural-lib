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
	for (int i = 0; i < 1000000; i++) {
		int k = rand() % 4 + 0;
		int j = 0;
	//	cout << "epoch #" << i << "\t" << "Enter inputs:" << "k = " << k << "\n";
		for (j = 0; j < neuronsPerLayer[0]; j++)				// сделать рандомно
			weights[j][j] = eduBase[k][j];
		expected = eduBase[k][j];
		weights = cycle(weights, neuronsPerLayer, layersNum, expected);
	}
	for(int k = 0; k < 4; k++)
	exploitation(weights, neuronsPerLayer, layersNum);

	system("pause");
}
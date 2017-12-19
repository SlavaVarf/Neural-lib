#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"
void main() {
	int epochNumber = 100000;
	bool complete = false;
	int neuronsPerLayer[3] = { 2,3,1 };
	int eduBase[4][3] = { { 1,0,1 },{ 1,1,0 },{ 0,1,1 },{ 0,0,0 } };
	double expected;
	int layersNum = 3, neuronsNum = 0;
	double **weights;
	neuronsNum = neuronsCounter(neuronsPerLayer, layersNum);
	while (!complete) {
		weights = matrixCreation(neuronsPerLayer, layersNum);
		for (int i = 0; i < epochNumber; i++) {
			for (int k = 0; k < 4; k++) {
				int j = 0;
				for (j = 0; j < neuronsPerLayer[0]; j++)
					weights[j][j] = eduBase[k][j];
				expected = eduBase[k][j];
				weights = cycle(weights, neuronsPerLayer, layersNum, expected);
				if (i % 50 == 0) {
					int counter = 0;
					for (int k = 0; k < 4; k++) {
						int j = 0;
						for (j = 0; j < neuronsPerLayer[0]; j++)
							weights[j][j] = eduBase[k][j];
						expected = eduBase[k][j];
						weights = cycle(weights, neuronsPerLayer, layersNum, expected);
						if (answer(weights[5][5]) == expected)
							counter++;
					}
					cout << counter << "\t";
					if (counter == 4){
						complete = true;
						i = epochNumber;
						cout << endl;
					}
				}
			}

		}

	}
	for (int k = 0; k < 4; k++)
		exploitation(weights, neuronsPerLayer, layersNum);

	system("pause");
}
#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"
void main() {
	bool switcher = true, confirm = true;
	int neuronsPerLayer[3] = { 2,3,1 };
	int eduBase[4][3] = { { 1,0,1 },{ 1,1,1 },{ 0,1,1 },{ 0,0,0 } }; //спросить про 000
	double expected;
	int layersNum = 3, neuronsNum = 0, pass;
	double **weights;
	neuronsNum = neuronsCounter(neuronsPerLayer, layersNum);
	while (confirm == true) {
		weights = matrixCreation(neuronsPerLayer, layersNum);
		for (int i = 0; i < 10000; i++) {
			pass = 0;
			//	int k = rand() % 4 + 0;
			int j = 0;
			for (int k = 0; k < 4; k++) {
				//	cout << "epoch #" << i << "\t" << "Enter inputs:" << "k = " << k << "\n";
				for (j = 0; j < neuronsPerLayer[0]; j++)				// сделать рандомно
					weights[j][j] = eduBase[k][j];
				expected = eduBase[k][j];
				weights = cycle(weights, neuronsPerLayer, layersNum, expected);
			}
		}
		int j = 0;
		for (int k = 0; k < 4; k++) {
			//	cout << "epoch #" << i << "\t" << "Enter inputs:" << "k = " << k << "\n";
			for (j = 0; j < neuronsPerLayer[0]; j++)				// сделать рандомно
				weights[j][j] = eduBase[k][j];
			expected = eduBase[k][j];
			weights = cycle(weights, neuronsPerLayer, layersNum, expected);
			if (weights[5][5] == expected)
				pass++;
		}
		if (pass == 3)
			confirm = false;
	}
			writeToFile("weights.txt", weights, neuronsNum);
			while (switcher == true) {
				string answer;
				exploitation(weights, neuronsPerLayer, layersNum);
				cout << endl << "Exit? Y/N ";
				cin >> answer;
				if (answer == "Y")
					switcher = false;
				else if (answer == "N")
					cout << "Continue" << endl;
				else {
					cout << "ERROR" << endl;
					switcher = false;
				}
			}
}
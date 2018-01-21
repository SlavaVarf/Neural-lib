/*��������� ���� ��� ������� ���������� �������� XOR, � ��������, �������� � �������� �����������������.*/

#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"



void main() {

	matrix mtrx;

	//mtrx.weights = new double*[6];
	int epochNumber = 5000;
	bool isComplete = false;
	//int neuronsPerLayer[3] = { 2,3,1 };
	int trainingSet[4][3] = { { 1,0,1 },{ 1,1,0 },{ 0,1,1 },{ 0,0,0 } };
	double expected;
	//int layersNumber = 3, neuronsNumber = 0;
	//double **weights;
	mtrx.neuronsNumber = neuronsCounter(mtrx);
	cout << "Below will display the number of passed tests. Begin?\n";
	system("pause");
	while (!isComplete) {
		mtrx.weights = matrixCreation(mtrx);
		for (int i = 0; i < epochNumber; i++) {									//�������� ��������� ����
			for (int k = 0; k < 4; k++) {										//������� ��������� �������
				int j = 0;
				for (j = 0; j < mtrx.neuronsPerLayer[0]; j++)						//���������� �������� ����
					mtrx.weights[j][j] = trainingSet[k][j];
				expected = trainingSet[k][j];
				mtrx.weights = training(mtrx, expected);
				if (i % 25 == 0) {												//�������� �� ����������������� 
					int counter = 0;											//�� ����� ��������
					for (int k = 0; k < 4; k++) {
						int j = 0;
						for (j = 0; j < mtrx.neuronsPerLayer[0]; j++)				//���������� �������� ����
							mtrx.weights[j][j] = trainingSet[k][j];
						expected = trainingSet[k][j];
						mtrx.weights = training(mtrx, expected);
						if (answer(mtrx.weights[5][5]) == expected)					//�������� �� ������������ �������� � �������
							counter++;
					}
					cout << counter << "\t";
					if (counter == 4) {											//���������� �������
						isComplete = true;
						i = epochNumber;
						cout << endl;
					}
				}
			}
		}
	}
	//writeToFile("weights.txt", weights, neuronsNum);
	cout << "\nTraining completed\n";
	for (int k = 0; k < 4; k++)													//������������ �������������
		test(mtrx);
	system("pause");
}
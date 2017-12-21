#include "stdafx.h"
#include "matrix.h"
#include "learningFunction.h"

double ** matrixCreation(int* neuronsPerLayer, int layersNum) {
	srand((unsigned)time(NULL));
	int *layerStart;							//номера нейронов,с которых начинается каждый слой
	int neuronsNum = 0;
	double **weights;
	layerStart = new int[layersNum];
	for (int i = 0; i < layersNum; i++) {
		layerStart[i] = neuronsNum;
		neuronsNum += neuronsPerLayer[i];
	}

	weights = new double*[neuronsNum];			//создание нижнетреугольной матрицы
	for (int i = 0; i < neuronsNum; i++) {
		weights[i] = new double[i + 1];
		for (int j = 0; j < i + 1; j++)
			weights[i][j] = 0;
	}

	for (int i = 0; i < layersNum - 1; i++)		 //задаем весам рандомные значения
		for (int k = layerStart[i]; k < layerStart[i] + neuronsPerLayer[i]; k++)
			for (int j = layerStart[i + 1]; j < layerStart[i + 1] + neuronsPerLayer[i + 1]; j++)
				weights[j][k] = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
	writeToFile("weights.txt", weights, neuronsNum);
	delete[]layerStart;
	return weights;
}

void writeToFile(string fileName, double **matrix, int neuronsNum) {  //запись матрицы в файл
	ofstream file(fileName);
	for (int i = 0; i < neuronsNum; i++) {
		for (int j = 0; j < i + 1; j++)
			file << fixed << matrix[i][j] << "\t";
		file << "\n";
	}
	file.close();

};

int neuronsCounter(int* neuronsPerLayer, int layersNum) {  //ф-ия,считающая и возвращающая общее кол-во нейронов.
	int neuronsNum = 0;
	for (int i = 0; i < layersNum; i++) {
		neuronsNum += neuronsPerLayer[i];
	}
	return neuronsNum;
}

double ** straightPass(double** weights, int* neuronsPerLayer, int layersNum) {     //прямой проход
	int *layerStart = new int[layersNum];
	layerStart[0] = 0;
	for (int i = 1; i < layersNum; i++) {
		layerStart[i] = layerStart[i - 1] + neuronsPerLayer[i - 1];
		for (int k = 0; k < neuronsPerLayer[i]; k++) {
			weights[layerStart[i] + k][layerStart[i] + k] = 0;
			for (int j = 0; j < neuronsPerLayer[i - 1]; j++)
				weights[layerStart[i] + k][layerStart[i] + k] += weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * weights[layerStart[i] + k][layerStart[i - 1] + j];//самый последний вес на месте ли?
			weights[layerStart[i] + k][layerStart[i] + k] = sigm(weights[layerStart[i] + k][layerStart[i] + k]);
		}
	}
	delete[]layerStart;
	return weights;
}

double ** training(double** weights, int* neuronsPerLayer, int layersNum, double expected) {     //прямой проход
	int *layerStart = new int[layersNum];
	layerStart[0] = 0;
	for (int i = 1; i < layersNum; i++) {
		layerStart[i] = layerStart[i - 1] + neuronsPerLayer[i - 1];
		for (int k = 0; k < neuronsPerLayer[i]; k++) {
			weights[layerStart[i] + k][layerStart[i] + k] = 0;
			for (int j = 0; j < neuronsPerLayer[i - 1]; j++)
				weights[layerStart[i] + k][layerStart[i] + k] += weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * weights[layerStart[i] + k][layerStart[i - 1] + j];//самый последний вес на месте ли?
			weights[layerStart[i] + k][layerStart[i] + k] = sigm(weights[layerStart[i] + k][layerStart[i] + k]);
		}
	}
	weights = backWay(weights, weights[layerStart[layersNum - 1]][layerStart[layersNum - 1]], expected, layersNum, layerStart);
	delete[]layerStart;
	return weights;
}

double **backWay(double**weights, double actual, double expected, int layersNum, int* layerStart) {
	wDeltaOfLastLayer(actual, expected);
	for (int i = layerStart[layersNum - 2]; i < layerStart[layersNum - 1]; i++) {
		weights[layerStart[layersNum - 1]][i] = newWeightOfLastLayer(weights[i][i], weights[layerStart[layersNum - 1]][i]); //можно загнать в цикл снизу?
	}

	double error;

	for (int i = layerStart[layersNum - 2]; i < layerStart[layersNum - 1]; i++) {
		error = errorOfNeuron(weights[layerStart[layersNum - 1]][i]);
		for (int k = layersNum - 2; k > 0; k--)
			for (int m = layerStart[k]; m < layerStart[k + 1]; m++)
				for (int j = layerStart[k - 1]; j < layerStart[k]; j++)
					weights[m][j] = newWeight(weights[m][m], weights[m][j], error);
	}
	return weights;

}

void exploitation(double** weights, int* neuronsPerLayer, int layersNum) {
	int value1;
	int value2;
	cout << "Enter 1 input value: ";
	cin >> value1;
	weights[0][0] = value1;
	cout << "Enter 2 input value: ";
	cin >> value2;
	weights[1][1] = value2;
	weights = straightPass(weights, neuronsPerLayer, layersNum);
	/*
	int expected = 0;
	if ((value1 == 1) || (value2 == 1)) {
		expected = 1;

	}
	cout << "Expexted answer: " << expected << endl;
	*/
	cout << "val: " << weights[5][5] << endl;
	cout << "Actual answer: " << answer(weights[5][5]) << endl;
}

double sigm(double x) {
	//cout << "prev " << x << "\n";
	double sigm = (1 / (1 + exp(-x)));
	//cout << "aft " << sigm << "\n";
	return sigm;
}

double answer(double x) {
	if (x > 0.5)
		return 1;
	else return 0;
}
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
}															
double ** forwardWay(double** weights, int* neuronsPerLayer, int layersNum, double expected) {
	int *layerStart = new int[layersNum];
	layerStart[0] = 0;
	for (int i = 1; i < layersNum; i++) {
		layerStart[i] = layerStart[i - 1] + neuronsPerLayer[i - 1];
		for (int k = 0; k < neuronsPerLayer[i]; k++) {
			weights[layerStart[i] + k][layerStart[i] + k] = 0;
			for (int j = 0; j < neuronsPerLayer[i - 1]; j++)
				weights[layerStart[i] + k][layerStart[i] + k] += weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * weights[neuronsPerLayer[i - 1] + k][layerStart[i - 1] + j];
			weights[layerStart[i] + k][layerStart[i] + k] = sigm(weights[layerStart[i] + k][layerStart[i] + k]);
		}

	}
	backWay(weights, neuronsPerLayer, layersNum, expected, layerStart, 0.1);
	return weights;
}
double ** backWay(double** weights, int* neuronsPerLayer, int layersNum, double expected, int* layerStart, double learningRate){
	double error = weights[layerStart[layersNum - 1]][layerStart[layersNum - 1]] - expected;			//берём ошибку последнего нейрона
	for (int i = layersNum - 1; i > 0; i--)																//начиная с последнего слоя спускаемся к первому
		for (int j = layerStart[i] + neuronsPerLayer[i]; j > layerStart[i]; j--) {						//для каждого нейрона в этом слое
			double weightsDelta = error*sigm(weights[j - 1][j - 1])*(1 - sigm(weights[j - 1][j - 1]));  //считаем ошибку
			for (int k = layerStart[i - 1] + neuronsPerLayer[i - 1]; k > layerStart[i - 1]; k--)		//в окне вывода видно, что все эти сигмоиды нормально считаются
				weights[k][k - 1] -= weights[k - 1][k - 1] * weightsDelta*learningRate;					//корректируем все веса, которые ведут к этому нейрону
		}
	return weights;																						//возвращаем матрицу в forwardWay
}

double sigm(double x) {
	cout << "prev " << x << "\n";
	double sigm = (1 / (1 + exp(-x)));
	cout << "aft " << sigm << "\n";
	return sigm;
}

double answer(double x) {
	if (x > 0.5)
		return true;
	else return false;
}
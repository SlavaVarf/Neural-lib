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

int neuronsCounter(int* neuronsPerLayer, int layersNum) {  //ф-ия,считающая и возвращающая общее кол-во нейронов
	int neuronsNum = 0;
	for (int i = 0; i < layersNum; i++) {
		neuronsNum += neuronsPerLayer[i];
	}
	return neuronsNum;
}

double ** FBWay(double** weights, int* neuronsPerLayer, int layersNum, double expected) {     //прямой проход
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
	//backWay(weights, neuronsPerLayer, layersNum, expected, layerStart, 0.1);
	backWay(weights, weights[layerStart[layersNum - 1]][layerStart[layersNum - 1]], expected, layersNum, layerStart);
	return weights;
}

double ** solution(double** weights, int* neuronsPerLayer, int layersNum) {     //прямой проход
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
	for (int i = layerStart[layersNum - 1]; i < layerStart[layersNum - 1] + neuronsPerLayer[layersNum - 1]; i++)
		cout << "weights[" << i << "][" << i << "]=" << answer(weights[i][i]);
	return weights;
}

double **backWay(double**weights, double actual, double expected, int layersNum, int* layerStart) {

	weights_delta_last(actual, expected);
	for (int i = layerStart[layersNum - 2]; i < layerStart[layersNum - 1]; i++) {
		weights[layerStart[layersNum - 1]][i] = new_weight_last(weights[i][i], weights[layerStart[layersNum - 1]][i]);
	}

	double error;

	for (int i = layerStart[layersNum - 2]; i < layerStart[layersNum - 1]; i++) {
		error = error_of_neu(weights[layerStart[layersNum - 1]][i]);
		for (int k = layersNum - 2; k > 0; k--)
			for (int m = layerStart[k]; m < layerStart[k + 1]; m++)
				for (int j = layerStart[k - 1]; j < layerStart[k]; j++)
					weights[m][j] = new_weight(weights[m][m], weights[m][j], error);
	}
	return weights;

}
/*double ** backWay(double** weights, int* neuronsPerLayer, int layersNum, double expected, int* layerStart, double learningRate){
double error = weights[layerStart[layersNum - 1]][layerStart[layersNum - 1]] - expected;			//берём ошибку последнего нейрона
for (int i = layersNum - 1; i > 0; i--)																//начиная с последнего слоя спускаемся к первому
for (int j = layerStart[i] + neuronsPerLayer[i]; j > layerStart[i]; j--) {						//для каждого нейрона в этом слое
double weightsDelta = error*sigm(weights[j - 1][j - 1])*(1 - sigm(weights[j - 1][j - 1]));  //считаем ошибку
for (int k = layerStart[i - 1] + neuronsPerLayer[i - 1]; k > layerStart[i - 1]; k--)		//в окне вывода видно, что все эти сигмоиды нормально считаются
weights[k][k - 1] -= weights[k - 1][k - 1] * weightsDelta*learningRate;					//корректируем все веса, которые ведут к этому нейрону
}
return weights;																						//возвращаем матрицу в forwardWay
}
*/

double sigm(double x) {
	double sigm = (1 / (1 + exp(-x)));
	return sigm;
}

double answer(double x) {
	if (x > 0.5)
		return 1;
	else return 0;
}
#include "stdafx.h"
#include "matrix.h"
#include "learningFunction.h"

/*создание матрицы весов нейронной сети*/
double ** matrixCreation(int* neuronsPerLayer, int layersNumber) {
	srand((unsigned)time(NULL));
	int *layerStart;
	int neuronsNumber = 0;
	double **weights;
	layerStart = new int[layersNumber];
	for (int i = 0; i < layersNumber; i++) {		//заполняет массив индексами нейронов, 
		layerStart[i] = neuronsNumber;				//с которых начинаются слои
		neuronsNumber += neuronsPerLayer[i];
	}

	weights = new double*[neuronsNumber];
	for (int i = 0; i < neuronsNumber; i++) {		//создание нижнетреугольной матрицы
		weights[i] = new double[i + 1];				//и обнуление её элементов
		for (int j = 0; j < i + 1; j++)
			weights[i][j] = 0;
	}

	/*присваивание случайных значений весам*/
	for (int i = 0; i < layersNumber - 1; i++)
		for (int k = layerStart[i]; k < layerStart[i] + neuronsPerLayer[i]; k++)
			for (int j = layerStart[i + 1]; j < layerStart[i + 1] + neuronsPerLayer[i + 1]; j++)
				weights[j][k] = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
	delete[]layerStart;
	return weights;
}
/*Запись матрицы в файл*/
void writeToFile(string fileName, double **matrix, int neuronsNumber) {
	ofstream file(fileName);
	for (int i = 0; i < neuronsNumber; i++) {		//поэлементная запись
		for (int j = 0; j < i + 1; j++)				//матрицы в файл
			file << fixed << matrix[i][j] << "\t";
		file << "\n";
	}
	file.close();

};

/*Подсчёт количества нейронов в нейронной сети*/
int neuronsCounter(int* neuronsPerLayer, int layersNumber) {
	int neuronsNumber = 0;
	for (int i = 0; i < layersNumber; i++) {		//суммирование нейронов
		neuronsNumber += neuronsPerLayer[i];		//всех слоёв
	}
	return neuronsNumber;
}

/*определение уровня активации нейронов*/
double ** straightPass(double** weights, int* neuronsPerLayer, int layersNumber) {
	int *layerStart = new int[layersNumber];
	layerStart[0] = 0;
	/*определение уровней активации нейронов каждого слоя*/
	for (int i = 1; i < layersNumber; i++) {
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

/*обучение нейронной сети*/
double ** training(double** weights, int* neuronsPerLayer, int layersNumber, double expected) {
	int *layerStart = new int[layersNumber];
	layerStart[0] = 0;
	/*определение уровней активации нейронов каждого слоя*/
	for (int i = 1; i < layersNumber; i++) {
		layerStart[i] = layerStart[i - 1] + neuronsPerLayer[i - 1];
		for (int k = 0; k < neuronsPerLayer[i]; k++) {
			weights[layerStart[i] + k][layerStart[i] + k] = 0;
			for (int j = 0; j < neuronsPerLayer[i - 1]; j++)
				weights[layerStart[i] + k][layerStart[i] + k] += weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * weights[layerStart[i] + k][layerStart[i - 1] + j];//самый последний вес на месте ли?
			weights[layerStart[i] + k][layerStart[i] + k] = sigm(weights[layerStart[i] + k][layerStart[i] + k]);
		}
	}
	weights = backWay(weights, weights[layerStart[layersNumber - 1]][layerStart[layersNumber - 1]], expected, layersNumber, layerStart);
	delete[]layerStart;
	return weights;
}

/*метод обратного распростронения ошибки*/
double **backWay(double**weights, double actual, double expected, int layersNumber, int* layerStart) {
	wDeltaOfLastLayer(actual, expected);
	/*переопределение весов, идущих к последнему слою*/
	for (int i = layerStart[layersNumber - 2]; i < layerStart[layersNumber - 1]; i++) {
		weights[layerStart[layersNumber - 1]][i] = newWeightOfLastLayer(weights[i][i], weights[layerStart[layersNumber - 1]][i]); //можно загнать в цикл снизу?
	}

	double error;
	/*вычисление ошибки каждого нейрона*/
	for (int i = layerStart[layersNumber - 2]; i < layerStart[layersNumber - 1]; i++) {
		error = errorOfNeuron(weights[layerStart[layersNumber - 1]][i]);
		/*переопределение весов данных нейронов*/
		for (int k = layersNumber - 2; k > 0; k--)
			for (int m = layerStart[k]; m < layerStart[k + 1]; m++)
				for (int j = layerStart[k - 1]; j < layerStart[k]; j++)
					weights[m][j] = newWeight(weights[m][m], weights[m][j], error);
	}
	return weights;

}

/*тестирование нейронной сети пользователем*/
void test(double** weights, int* neuronsPerLayer, int layersNumber) {
	int value1;
	int value2;
	cout << "Enter 1 input value: ";
	cin >> value1;
	weights[0][0] = value1;
	cout << "Enter 2 input value: ";
	cin >> value2;
	weights[1][1] = value2;
	weights = straightPass(weights, neuronsPerLayer, layersNumber);
	cout << "\nValue of output neuron: " << weights[5][5];
	cout << "\nAnswer: " << answer(weights[5][5]) << "\n\n";
}

/*пропуск нейрона через активационную функцию (бинарный сигмоид)*/
double sigm(double x) {
	double sigm = (1 / (1 + exp(-x)));
	return sigm;
}

/*вычисление выходного значения*/
double answer(double x) {
	if (x >= 0.5)				//проверка на условие активации нейрона
		return 1;
	else return 0;
}
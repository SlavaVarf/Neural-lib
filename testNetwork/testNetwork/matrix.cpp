#include "stdafx.h"
#include "matrix.h"
#include "learningFunction.h"

/*создание матрицы весов нейронной сети*/
double ** matrixCreation(struct matrix mtrx) {
	srand((unsigned)time(NULL));
	int *layerStart;
	int neuronsNumber = 0;
	double **weights;
	layerStart = new int[mtrx.layersNumber];
	for (int i = 0; i < mtrx.layersNumber; i++) {		//заполняет массив индексами нейронов, 
		layerStart[i] = neuronsNumber;					//с которых начинаются слои
		neuronsNumber += mtrx.neuronsPerLayer[i];
	}

	weights = new double*[neuronsNumber];
	for (int i = 0; i < neuronsNumber; i++) {			//создание нижнетреугольной матрицы
		weights[i] = new double[i + 1];
		for (int j = 0; j < i + 1; j++)					//обнуление матрицы
			weights[i][j] = 0;
	}

	/*присваивание случайных значений весам*/
	for (int i = 0; i < mtrx.layersNumber - 1; i++)		//перебор слоёв нейросети
		for (int k = layerStart[i]; k < layerStart[i] + mtrx.neuronsPerLayer[i]; k++)	//перебор элементов в данном слое
			for (int j = layerStart[i + 1]; j < layerStart[i + 1] + mtrx.neuronsPerLayer[i + 1]; j++)	//перебор элементов в следующем слое
				weights[j][k] = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0; //заполнение веса между нейроном даного слоя и нейроном следующего  
	delete[]layerStart;
	return weights;
}
/*Запись матрицы в файл*/
void writeToFile(string fileName, struct matrix mtrx) {
	ofstream file(fileName);
	for (int i = 0; i < mtrx.neuronsNumber; i++) {		//перебор строк матрицы
		for (int j = 0; j < i + 1; j++)				//перебор элементов строки 
			file << fixed << mtrx.weights[i][j] << "\t";	//копирование элемента в файл в фиксированном виде
		file << "\n";
	}
	file.close();

};

/*Подсчёт количества нейронов в нейронной сети*/
int neuronsCounter(struct matrix mtrx) {
	int neuronsNumber = 0;
	for (int i = 0; i < mtrx.layersNumber; i++) {		//перебор слоёв 
		neuronsNumber += mtrx.neuronsPerLayer[i];		//складывание нейронов каждого слоя
	}
	return neuronsNumber;
}

/*определение уровня активации нейронов*/
double ** straightPass(struct matrix mtrx) {
	int *layerStart = new int[mtrx.layersNumber];
	layerStart[0] = 0;
	/*определение уровней активации нейронов каждого слоя*/
	for (int i = 1; i < mtrx.layersNumber; i++) {			//перебор слоёв 
		layerStart[i] = layerStart[i - 1] + mtrx.neuronsPerLayer[i - 1]; //массив индексов первых элементов слоёв
		for (int k = 0; k < mtrx.neuronsPerLayer[i]; k++) { //перебор элементов в слое
			mtrx.weights[layerStart[i] + k][layerStart[i] + k] = 0; //обнуление значений нейронов
			for (int j = 0; j < mtrx.neuronsPerLayer[i - 1]; j++) //перебор элементов предыдущего слоя
				/*высчитывание значения в данном нейроне*/
				mtrx.weights[layerStart[i] + k][layerStart[i] + k] += mtrx.weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * mtrx.weights[layerStart[i] + k][layerStart[i - 1] + j];
			/*пропуск нейрона через активационную функцию*/
			mtrx.weights[layerStart[i] + k][layerStart[i] + k] = sigm(mtrx.weights[layerStart[i] + k][layerStart[i] + k]);
		}
	}
	delete[]layerStart;
	return mtrx.weights;
}

/*обучение нейронной сети*/
double ** training(struct matrix mtrx, double expected) {
	int *layerStart = new int[mtrx.layersNumber];
	layerStart[0] = 0;
	/*определение уровней активации нейронов каждого слоя*/
	for (int i = 1; i < mtrx.layersNumber; i++) {	//перебор слоёв
		layerStart[i] = layerStart[i - 1] + mtrx.neuronsPerLayer[i - 1];	//массив индексов первых элементов слоёв
		for (int k = 0; k < mtrx.neuronsPerLayer[i]; k++) {		//перебор элементов слоя
			mtrx.weights[layerStart[i] + k][layerStart[i] + k] = 0; //обнуление нейронов
			for (int j = 0; j < mtrx.neuronsPerLayer[i - 1]; j++)	//перебор элементов предыдущего слоя
				/*высчитывание значения в данном нейроне*/
				mtrx.weights[layerStart[i] + k][layerStart[i] + k] += mtrx.weights[layerStart[i - 1] + j][layerStart[i - 1] + j] * mtrx.weights[layerStart[i] + k][layerStart[i - 1] + j];
			/*пропуск нейрона через активационную функцию*/
			mtrx.weights[layerStart[i] + k][layerStart[i] + k] = sigm(mtrx.weights[layerStart[i] + k][layerStart[i] + k]);
		}
	}
	/*обучение методом обратного распространения ошибки*/
	mtrx.weights = backWay(mtrx, mtrx.weights[layerStart[mtrx.layersNumber - 1]][layerStart[mtrx.layersNumber - 1]], expected, layerStart);
	delete[]layerStart;
	return mtrx.weights;
}

/*метод обратного распростронения ошибки*/
double **backWay(struct matrix mtrx, double actual, double expected, int* layerStart) {
	wDeltaOfLastLayer(actual, expected);	//нахождение ошибки последнего слоя
	for (int i = layerStart[mtrx.layersNumber - 2]; i < layerStart[mtrx.layersNumber - 1]; i++) { //перебор индексов предыдущего слоя
	/*перерасчёт весов, идущих к последнему слою*/
		mtrx.weights[layerStart[mtrx.layersNumber - 1]][i] = newWeightOfLastLayer(mtrx.weights[i][i], mtrx.weights[layerStart[mtrx.layersNumber - 1]][i]);
	}

	double error;
	for (int i = layerStart[mtrx.layersNumber - 2]; i < layerStart[mtrx.layersNumber - 1]; i++) { //перебор индексов предыдущего слоя
		error = errorOfNeuron(mtrx.weights[layerStart[mtrx.layersNumber - 1]][i]);	//высчитывание значения ошибки для каждого нейрона
		for (int k = mtrx.layersNumber - 2; k > 0; k--)		//перебор слоёв сверху вниз
			for (int m = layerStart[k]; m < layerStart[k + 1]; m++)	//перебор индексов данного слоя
				for (int j = layerStart[k - 1]; j < layerStart[k]; j++) //перебор индексов предыдущего слоя
					mtrx.weights[m][j] = newWeight(mtrx.weights[m][m], mtrx.weights[m][j], error); //перерасчёт значения веса
	}
	return mtrx.weights;

}

/*тестирование нейронной сети пользователем*/
void test(struct matrix mtrx) {
	int value1;
	int value2;
	cout << "Enter 1 input value: ";
	cin >> value1;
	mtrx.weights[0][0] = value1;
	cout << "Enter 2 input value: ";
	cin >> value2;
	mtrx.weights[1][1] = value2;
	mtrx.weights = straightPass(mtrx); //пропуск входных значений через нейросеть
	cout << "\nValue of output neuron: " << mtrx.weights[5][5]; //вывод значения нейрона выходного слоя на печать
	cout << "\nAnswer: " << answer(mtrx.weights[5][5]) << "\n\n"; //пропуск нейрона выходного слоя через условие
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
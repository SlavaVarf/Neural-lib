/*Нейронная сеть для решения логической операции XOR, её создание, обучение и проверка работоспособности.*/

#include "stdafx.h"
#include "learningFunction.h"
#include "mainNeural.h"
#include "matrix.h"

void main() {
	matrix mtrx;
	int epochNumber = 5000;
	bool isComplete = false;
	int trainingSet[4][3] = { { 1,0,1 },{ 1,1,0 },{ 0,1,1 },{ 0,0,0 } };
	double expected;
	mtrx.neuronsNumber = neuronsCounter(mtrx);									//подсчёт количества нейронов нейросети
	cout << "Below will display the number of passed tests. Begin?\n";
	system("pause");
	while (!isComplete) {														//пока проверка не пройдена
		mtrx.weights = matrixCreation(mtrx);									//создание матрицы весов
		for (int i = 0; i < epochNumber; i++) {									//обучение нейронной сети
			for (int k = 0; k < 4; k++) {										//перебор элементов выборки
				int j = 0;
				for (j = 0; j < mtrx.neuronsPerLayer[0]; j++)					//заполнение входного слоя
					mtrx.weights[j][j] = trainingSet[k][j];
				expected = trainingSet[k][j];
				mtrx.weights = training(mtrx, expected);						//обучение
				if (i % 25 == 0) {												//проверка на работоспособность 
					int counter = 0;											//во время обучения
					for (int k = 0; k < 4; k++) {								//перебор наборов из обучающей базы
						int j = 0;
						for (j = 0; j < mtrx.neuronsPerLayer[0]; j++)			//заполнение входного слоя данными для обучения
							mtrx.weights[j][j] = trainingSet[k][j];
						expected = trainingSet[k][j];
						mtrx.weights = training(mtrx, expected);
						if (answer(mtrx.weights[5][5]) == expected)				//проверка на соответствие ожидаемого и полученного значения
							counter++;
					}
					cout << counter << "\t";
					if (counter == 4) {											//количество пройденных проверок
						isComplete = true;
						i = epochNumber;
						cout << endl;
					}
				}
			}
		}
	}
	writeToFile("weights.txt", mtrx);							//запись в файл
	cout << "\nTraining completed\n";
	for (int k = 0; k < 4; k++)													//тестирование пользователем
		test(mtrx);
	system("pause");
}
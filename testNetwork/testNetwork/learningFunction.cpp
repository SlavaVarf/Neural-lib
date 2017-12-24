#include "stdafx.h"
#include "learningFunction.h"

double wDelta;
double learningRate = 0.3;

/* дельта для весов,которые идут к последнему слою */
void wDeltaOfLastLayer(double actual, double expected) {
	double error = expected - actual;
	wDelta = error*actual*(1 - actual);
}

/*новое значение весов,которые идут к последнему слою*/
double newWeightOfLastLayer(double valueOfNeuron, double weightFrom) {
	double newWeight = weightFrom + valueOfNeuron*wDelta*learningRate;
	return newWeight;
}

/*вычисление ошибки нейрона*/
double errorOfNeuron(double weightFrom) {
	double error = weightFrom*wDelta;
	return error;
}

/*новое значение весов для предыдущих слоев*/
double newWeight(double valueOfNeuron, double weightTo, double error) {
	wDelta = error*valueOfNeuron*(1 - valueOfNeuron);
	double newWeight = weightTo + valueOfNeuron*wDelta*learningRate;
	return newWeight;
}

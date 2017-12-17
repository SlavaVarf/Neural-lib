#include "stdafx.h"
#include "learningFunction.h"

double wDelta;
double learningRate = 0.5;

//double ** learningEpoch(double ** weights, int * input layer)					//подумать про обучение
/* дельта для весов,которые идут к последнему слою */
void weights_delta_last(double actual, double expected) {
	double error = actual - expected;					//2.1				//2.2*
	wDelta = error*actual*(1 - actual);		//2.2
}

/*новое значение весов,которые идут к последнему слою*/
double new_weight_last(double valueOfNeu, double weightFrom) {      //valueOfNeu-значение нейрона,от которого идет вес weightFrom.
	double new_weight = weightFrom - valueOfNeu*wDelta*learningRate;
	return new_weight;
}

double error_of_neu(double weightFrom) {
	double error = weightFrom*wDelta;
	return error;
}

/*новое значение весов для предыдущих слоев*/
double new_weight(double valueOfNeu, double weightTo, double error) {
	wDelta = error*valueOfNeu*(1 - valueOfNeu);
	double new_weight = weightTo - valueOfNeu*wDelta*learningRate;
	return new_weight;
}

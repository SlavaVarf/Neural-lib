#include "stdafx.h"
#include "learningFunction.h"

double wDelta;
double learningRate;

/* дельта для весов,которые идут к последнему слою */
void weights_delta_last(double actual,double expected) {   
	double error = actual - expected;					//2.1
	double sigmoidDX = actual*(1 - actual);				//2.2*
     wDelta = error*sigmoidDX;							//2.2
}

/*новое значение весов,которые идут к последнему слою*/
double new_weight_last(double valueOfNeu, double weightTo) {      
	double new_weight = weightTo - valueOfNeu*wDelta*learningRate;
	return new_weight;
}

/*новое значение весов для предыдущих слоев*/
double new_weight(double valueOfNeu, double weightFrom) {
	double error = weightFrom*wDelta;
	double new_weight = weightFrom - valueOfNeu*wDelta*learningRate; 
	return new_weight;
}


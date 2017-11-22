#include "stdafx.h"
#include "learningFunction.h"

double wDelta;
double learningRate;
void weights_delta(double actual,double expected) {
	double error = actual - expected;					//2.1
	double sigmoidDX = actual*(1 - actual);				//2.2*
     wDelta = error*sigmoidDX;							//2.2
}

double new_weight(double valueOfThisNeu,double valueOfPrevNeu) {
	
	double new_weight = valueOfThisNeu - valueOfPrevNeu*wDelta*learningRate; //2.3
	return new_weight;
}

double new_valueOfNeu(double valueOfNeu,double weight) {
	
	double error = weight*wDelta;                                 //2.4
	double newValue = valueOfNeu - weight*wDelta*learningRate;    //2.5
	return newValue;
}
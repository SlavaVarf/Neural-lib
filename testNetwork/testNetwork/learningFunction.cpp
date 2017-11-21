#include "stdafx.h"
#include "learningFunction.h"

double gotWeights(double weight) {
	return weight;
}
double setWeigth(double weight, double neuron,double delta, double lr) {
double a = (weight - neuron*delta*lr);
return a;
}

/*

double weigts_delta(double actual,double expected) {
double error = actual - expected;                 //2.1
double weights_delta = error*sweights.weights[CountOfNeurons - 1][CountOfNeurons - 1];
return weigts_delta;
}
*/

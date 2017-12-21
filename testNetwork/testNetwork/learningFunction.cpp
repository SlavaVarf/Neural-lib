#include "stdafx.h"
#include "learningFunction.h"

double wDelta;
double learningRate = 0.25;

//double ** learningEpoch(double ** weights, int * input layer)					//�������� ��� ��������
/* ������ ��� �����,������� ���� � ���������� ���� */
void wDeltaOfLastLayer(double actual, double expected) {
	double error = expected - actual;  					//2.1				//2.2*
	wDelta = error*actual*(1 - actual);		//2.2
}

/*����� �������� �����,������� ���� � ���������� ����*/
double newWeightOfLastLayer(double valueOfNeu, double weightFrom) {      //valueOfNeu-�������� �������,�� �������� ���� ��� weightFrom.
	double newWeight = weightFrom + valueOfNeu*wDelta*learningRate;
	return newWeight;
}

double errorOfNeuron(double weightFrom) {
	double error = weightFrom*wDelta;
	return error;
}

/*����� �������� ����� ��� ���������� �����*/
double newWeight(double valueOfNeuron, double weightTo, double error) {
	wDelta = error*valueOfNeuron*(1 - valueOfNeuron);
	double newWeight = weightTo + valueOfNeuron*wDelta*learningRate;
	return newWeight;
}

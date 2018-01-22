#pragma once
struct matrix {
	double **weights;
	int layersNumber = 3;
	int neuronsNumber = 0;
	int neuronsPerLayer[3] = { 2,3,1 };
};
int neuronsCounter(struct matrix mtrx);
double ** matrixCreation(struct matrix mtrx);
void writeToFile(string fileName, struct matrix mtrx);
double ** training(struct matrix mtrx, double expected);
double ** straightPass(struct matrix mtrx);
double **backWay(struct matrix mtrx, double actual, double expected, int* layerStart);
void test(struct matrix mtrx);
double sigm(double x);
double answer(double x);
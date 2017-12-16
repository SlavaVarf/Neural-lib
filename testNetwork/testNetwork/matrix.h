#pragma once

int neuronsCounter(int* neuronsPerLayer, int layersNum);
double ** matrixCreation(int* neuronsPerLayer, int layersNum);
void writeToFile(string fileName, double **matrix, int neuronsNum);
double ** forwardWay(double** weights, int* neuronsPerLayer, int layersNum);
//double ** backWay(double** weights, int* neuronsPerLayer, int layersNum, double expected, int* layerStart, double learningRate);
double **backWay(double**weights, double actual, double expected, int layersNum, int* layerStart);
void exploitation(double** weights, int* neuronsPerLayer, int layersNum);
double** learning(double** weights, int* neuronsPerLayer, int layersNum, double expected);
double sigm(double x);
double answer(double x);
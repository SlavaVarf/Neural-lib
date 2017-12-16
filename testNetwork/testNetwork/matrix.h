#pragma once

int neuronsCounter(int* neuronsPerLayer, int layersNum);
double ** matrixCreation(int* neuronsPerLayer, int layersNum);
void writeToFile(string fileName, double **matrix, int neuronsNum);
double ** cycle(double** weights, int* neuronsPerLayer, int layersNum, double expected);
double ** cycle(double** weights, int* neuronsPerLayer, int layersNum);
double **backWay(double**weights, double actual, double expected, int layersNum, int* layerStart);
void exploitation(double** weights, int* neuronsPerLayer, int layersNum);
double sigm(double x);
double answer(double x);
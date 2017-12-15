#pragma once

int neuronsCounter(int* neuronsPerLayer, int layersNum);
double ** matrixCreation(int* neuronsPerLayer, int layersNum);
void writeToFile(string fileName, double **matrix, int neuronsNum);
double ** solution(double** weights, int* neuronsPerLayer, int layersNum);
double ** FBWay(double** weights, int* neuronsPerLayer, int layersNum, double expected);
double **backWay(double**weights, double actual, double expected, int layersNum, int* layerStart);
double sigm(double x);
double answer(double x);
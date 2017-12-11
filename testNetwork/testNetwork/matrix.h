#pragma once

int neuronsCounter(int* neuronsPerLayer, int layersNum);
double ** matrixCreation(int* neuronsPerLayer, int layersNum);
void writeToFile(string fileName, double **matrix, int neuronsNum);
void forwardWay(int* inputLayer, int* neuronsPerLayer, int layersNum);
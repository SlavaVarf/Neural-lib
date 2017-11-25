#pragma once

void matrixCreation(int* neuronsPerLayer, int layersNum);
double getWeight(int fNeuron, int tneuron);
void setWeight(int fNeuron, int tNeuron, double value);
void forwardWay(int* inputLayer, int* neuronsPerLayer, int layersNum);
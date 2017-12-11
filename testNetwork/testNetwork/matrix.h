#pragma once
#include <fstream>
#include <iostream>
#include <cstdio>


//void fileWrite(string path, const char str[]);
//void searchInFile(string name, int rows, int cols);
void matrixCreation(int* neuronsPerLayer, int layersNum);
void searchInFile(int row, int col);
/*
double getWeight(int fNeuron, int tneuron);
void setWeight(int fNeuron, int tNeuron, double value);
void forwardWay(int* inputLayer, int* neuronsPerLayer, int layersNum);
*/
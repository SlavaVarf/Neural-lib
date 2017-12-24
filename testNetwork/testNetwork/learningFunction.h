#pragma once

void wDeltaOfLastLayer(double actual, double expected);
double newWeightOfLastLayer(double valueOfNeuron, double weightFrom);
double errorOfNeuron(double weightFrom);
double newWeight(double valueOfNeu, double weightTo, double error);
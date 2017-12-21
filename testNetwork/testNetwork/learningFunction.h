#pragma once

void wDeltaOfLastLayer(double actual, double expected);
double newWeightOfLastLayer(double valueOfNeu, double weightFrom);
double errorOfNeuron(double weightFrom);
double newWeight(double valueOfNeu, double weightTo, double error);
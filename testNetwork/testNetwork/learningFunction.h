#pragma once

void weights_delta_last(double actual, double expected);
double new_weight_last(double valueOfNeu, double weightFrom);
double error_of_neu(double weightFrom);
double new_weight(double valueOfNeu, double weightTo, double error);
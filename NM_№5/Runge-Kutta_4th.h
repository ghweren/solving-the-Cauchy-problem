#pragma once
#include "SolvingMethod.h"
class Runge_Kutta_4th:public SolvingMethod
{
public:
	double Calculation(double Y0, double X0, double h, double(*function)(double,double)) const
	{
		double K1 = h*function(X0, Y0);
		double K2 = h*function(X0 + h / 3, Y0 + K1 / 3);
		double K3 = h*function(X0 + h * 2 / 3, Y0 - K1 / 3 + K2);
		double K4 = h*function(X0 + h, Y0 + K1 - K2 + K3);
		return Y0 + (K1 + 3 * K2 + 3 * K3 + K4) / 8;
	}
};

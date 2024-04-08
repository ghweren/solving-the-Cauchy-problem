#pragma once
#include "SolvingMethod.h"
/**
@brief A class implementing the Runge-Kutta method of the 3rd degree
*/
class Runge_Kutta_3rd:public SolvingMethod
{
public:
	/**
	@brief A function that performs the solution of the Cauchy problem at the point X0+h
	@param Y0 The value of y in X0
	@param X0 The value of the previous x
	@param h Step from X0
	@param function The function f(x,y), which is used in the Cauchy problem y'=f(x,y)
	*/
	double Calculation(double Y0, double X0, double h, double(*function)(double, double)) const
	{
		double K1 = h*function(X0,Y0);
		double K2 = h*function(X0 + h / 3,Y0+K1/3);
		double K3 = h*function(X0 + h * 2 / 3,Y0+K2*2/3);
		return Y0 + (K1 + 3 * K3) / 4;
	}
};
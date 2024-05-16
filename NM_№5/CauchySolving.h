#pragma once
#include "SolvingMethod.h"
#include <vector>
using namespace std;
///@brief A class that performs the solution of the Cauchy problem
class CauchySolving
{
private:
	/// @param function The function f(x,y), which is used in the Cauchy problem y'=f(x,y) 
	double(*function)(double,double);
	/// @param solvingMethod The method of solving the Cauchy problem
	SolvingMethod *solvingMethod;
	/// @param estimationMethod The method used to verify the rejection of the solution
	SolvingMethod *estimationMethod;

	/// @brief A function that calculates the k- order value of the absolute error
	double eps_order(double eps);
	/// @param HminNum The number of points calculated in minimum increments
	int HminNum = 0;
	/// @param numOfUnsolvablePoints The number of points for which the maximum absolute error value has not been reached
	int numOfUnsolvablePoints = 0;
public:
	CauchySolving(SolvingMethod *solvingMethod, SolvingMethod *estimationMethod,double(*function)(double,double))
	{
		this->solvingMethod = solvingMethod;
		this->estimationMethod = estimationMethod;
		this->function = function;
	}

	/**
	@brief The function that solves the Cauchy problem on a segment returns a table of values in the form of vector<vector<double>>. The function performs a calculation at a point using the "solvingMethod" solution method, then performs calculations for the same point using "estimationMethod", if the modulus of the absolute error value (the difference between two calculated values) is less than or equal to the maximum absolute error value (eps), then the calculation value is entered in the table, and the calculation continues for the next point, otherwise the step is divided into two and the calculation is repeated. Initially, the step is given by the formula (B - A) / 10. When moving to the next point, the possibility of reverse doubling of the step is calculated, if the value of the local absolute error divided by 2^k (the result of eps_order) is less than the absolute error, then the step is doubled. The step cannot be less than Hmin.
	@param eps The maximum absolute error value in modulus
	@param Hmin The minimum step value for calculating the next value of y'
	@param A The value of the beginning of the segment
	@param B The value of the end of the segment
	@param Yc The y value at the starting point
	@param C The starting point, which should be A or B
	*/
	vector<vector<double>> Solving(double A,double B, double C, double Yc,double Hmin,double eps,size_t order);


};

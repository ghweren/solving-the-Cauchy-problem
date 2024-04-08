#pragma once
#include <iostream>
#include <vector>
#include "CauchySolving.h"
#include "Runge-Kutta_3rd.h"
#include "Runge-Kutta_4th.h"
#define PI 3.14159265 
/**
 @brief The function f(x,y), which is used in the Cauchy problem y'=f(x,y)
 @param x The variable of the function f(x,y)
 @param y The variable of the function f(x,y)
*/
double function(double x, double y)
{

	return x*x - sin((2 * x)*PI/180);
}
/**
@param eps The maximum absolute error value in modulus
@param Hmin The minimum step value for calculating the next value of y'
@param A The value of the beginning of the segment
@param B The value of the end of the segment
@param Yc The y value at the starting point
@param C The starting point, which should be A or B
*/
double eps, Hmin, A, B, Yc, C;
using namespace std;
int main()
{
	cout << "Enter the eps\n";
	cin >> eps;
	cout << "Enter the Hmin\n";
	cin >> Hmin;
	cout << "Enter the A\n";
	cin >> A;
	cout << "Enter the B\n";
	cin >> B;
	cout << "Enter the C\n";
	cin >> C;
	cout << "Enter the Yc\n";
	cin >> Yc;
	try{
		vector<vector<double>> result = (new CauchySolving(new Runge_Kutta_3rd,new Runge_Kutta_4th,function))->Solving(A,B,C,Yc,Hmin,eps);
		for (int i = 0; i < result.size(); i++)
		{
			cout << result[i][0]<<"   ";
			cout << result[i][1] << "   ";
			cout << result[i][2] << "   \n";

		}
	}
	catch (invalid_argument e)
	{
		cout<<e.what();
	}
	cin >> C;
}
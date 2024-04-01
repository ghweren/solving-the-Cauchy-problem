#pragma once
#include <iostream>
#include <vector>
#include "CauchySolving.h"
#include "Runge-Kutta_3rd.h"
#include "Runge-Kutta_4th.h"
#define PI 3.14159265 
double function(double x, double y)
{

	return 2*x+y-x*x;
	//return x*x - sin((2 * x)*PI/180);
}
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
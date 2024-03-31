#include <iostream>
#include <vector>
#include "CauchySolving.h"
#define PI 3.14159265 

double function(double x)
{
	return x*x - sin((2 * x)*PI/180);
}
double eps, Hmin, A, B, Yc, C;
using namespace std;
int main()
{
	cout << function(45);
	cin >> C;
	/*vector<double[3]> result;
	cout << "Enter the eps/n";
	cin >> eps;
	cout << "Enter the Hmin/n";
	cin >> Hmin;
	cout << "Enter the A/n";
	cin >> A;
	cout << "Enter the B/n";
	cin >> B;
	cout << "Enter the C/n";
	cin >> C;
	cout << "Enter the Yc/n";
	cin >> Yc;

	try{
		vector<double[3]> result = new CauchySolving(new Runge_Kutta_3rd, new Runge_Kutta_4th)->Solving(A, B, C, Yc, Hmin, eps);
	}
	catch (invalid_argument e)
	{
		cout<<e.what();
	}*/
}
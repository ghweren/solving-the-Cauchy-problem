#include "SolvingMethod.h"
#include <vector>
using namespace std;
class CauchySolving
{
private:
	SolvingMethod *solvingMethod;
	SolvingMethod *estimationMethod;
	double eps_order(double eps);
	int HminNum = 0;
	int numOfUnsolvablePoints = 0;
public:
	CauchySolving(SolvingMethod *solvingMethod, SolvingMethod *estimationMethod)
	{
		this->solvingMethod = solvingMethod;
		this->estimationMethod = estimationMethod;
	}

	vector<vector<double>> Solving(double A,double B, double C, double Yc,double Hmin,double eps);

	~CauchySolving();

};

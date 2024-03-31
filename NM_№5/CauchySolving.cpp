#include "CauchySolving.h"


vector<vector<double>> CauchySolving::Solving(double A, double B, double C, double Yc, double Hmin, double eps)
{
	vector<vector<double>> result;
	HminNum = 0;
	if (A >= B || C <= A || C >= B || Hmin <= 0 || eps <= 0|| C!=A||C!=B)
		throw std::invalid_argument("Invalid argument");
	else if (C == A)
	{
		double solvingResult;
		double estimationResult;
		double h = (B - A) / 10;
		double k=pow(2,eps_order(eps));
		double current_point = A + h;
		while (B - (current_point + h) >= Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			while (abs(solvingResult - estimationResult) > eps&&h != Hmin)
			{
				if (h / 2 <= Hmin)
				{
					current_point -= (h - Hmin);
					h = Hmin;
					solvingResult = solvingMethod->Calculation();
					estimationResult = estimationMethod->Calculation();
					HminNum++;
				}
				else
				{
					h /= 2;
					current_point -= h;
					solvingResult = solvingMethod->Calculation();
					estimationResult = estimationMethod->Calculation();
				}
			}
			if (abs(solvingResult - estimationResult) > eps)
				numOfUnsolvablePoints++;
			if (abs(solvingResult - estimationResult) < eps / k)
				h *= 2;
			result.push_back({current_point, solvingResult, abs(solvingResult - estimationResult)});
			current_point += h;
		}
		if (B - current_point <= 2 * Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ B-Hmin, solvingResult, abs(solvingResult - estimationResult) });
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
		else if (B-current_point<=1.5*Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
		else
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ current_point+(B-current_point)/2, solvingResult, abs(solvingResult - estimationResult) });
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
	}
	else
	{
		double solvingResult;
		double estimationResult;
		double h = (B - A) / 10;
		double k = pow(2, eps_order(eps));
		double current_point = B-h;
		while ((current_point + h)-A >= Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			while (abs(solvingResult - estimationResult)>eps&&h != Hmin)
			{
				if (h / 2 <= Hmin)
				{
					current_point += (h - Hmin);
					h = Hmin;
					solvingResult = solvingMethod->Calculation();
					estimationResult = estimationMethod->Calculation();
					HminNum++;
				}
				else
				{
					h /= 2;
					current_point += h;
					solvingResult = solvingMethod->Calculation();
					estimationResult = estimationMethod->Calculation();
				}
			}
			if (abs(solvingResult - estimationResult) > eps)
				numOfUnsolvablePoints++;
			if (abs(solvingResult - estimationResult) < eps / k)
				h *= 2;
			result.push_back({ current_point, solvingResult, abs(solvingResult - estimationResult) });
			current_point -= h;
		}
		if (current_point-A <= 2 * Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ A + Hmin, solvingResult, abs(solvingResult - estimationResult) });
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ A, solvingResult, abs(solvingResult - estimationResult) });
		}
		else if (current_point-A <= 1.5*Hmin)
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ A, solvingResult, abs(solvingResult - estimationResult) });
		}
		else
		{
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ current_point - (current_point-A) / 2, solvingResult, abs(solvingResult - estimationResult) });
			solvingResult = solvingMethod->Calculation();
			estimationResult = estimationMethod->Calculation();
			result.push_back({ A, solvingResult, abs(solvingResult - estimationResult) });
		}
	}
	return result;
}
double CauchySolving::eps_order(double eps)
{
	if (eps < 1)
	{
		int order = 0;
		while (eps < 1)
		{
			eps *= 10;
			order--;
		}
		return order;
	}
	else
	{
		int order = 0;
		while (eps>1)
		{
			eps /= 10;
			order++;
		}
		return order;
	}
}
#include "CauchySolving.h"
#include <iostream>

vector<vector<double>> CauchySolving::Solving(double A, double B, double C, double Yc, double Hmin, double eps)
{
	vector<vector<double>> result;
	HminNum = 0;
	if (A >= B || Hmin <= 0 || eps <= 0|| (C!=A&&C!=B))
		throw std::invalid_argument("Invalid argument");
	else if (C == A)
	{
		result.push_back({ A, Yc, 0 });
		double solvingResult;
		double estimationResult;
		double prev_solvingResult = Yc;
		double h = (B - A) / 10;
		double k=pow(2,eps_order(eps));
		double current_point = A + h;
		double prev_point = A;
		while (B - (current_point + h) >= Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult,prev_point,h,function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, h, function);
			while (abs(solvingResult - estimationResult) > eps&&h != Hmin)
			{
				if (h / 2 <= Hmin)
				{
					current_point -= (h - Hmin);
					h = Hmin;
					solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, h, function);
					estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, h, function);
					HminNum++;
				}
				else
				{
					h /= 2;
					current_point -= h;
					solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, h, function);
					estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, h, function);
				}
			}
			if (abs(solvingResult - estimationResult) > eps)
				numOfUnsolvablePoints++;
			if (abs(solvingResult - estimationResult) < eps / k)
				h *= 2;
			result.push_back({current_point, solvingResult, abs(solvingResult - estimationResult)});
			prev_point = current_point;
			prev_solvingResult = solvingResult;
			current_point += h;
		}
		if (B - current_point <= 2 * Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, B-prev_point-Hmin, function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, B - prev_point - Hmin, function);
			result.push_back({ B-Hmin, solvingResult, abs(solvingResult - estimationResult) });
			estimationResult = estimationMethod->Calculation(solvingResult, B, Hmin, function);
			solvingResult = solvingMethod->Calculation(solvingResult, B-Hmin, Hmin, function);
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
		else if (B-current_point<=1.5*Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, B-prev_point, function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, B-prev_point, function);
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
		else
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, (B - prev_point) / 2, function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, (B - prev_point) / 2, function);
			result.push_back({ current_point+(B-current_point)/2, solvingResult, abs(solvingResult - estimationResult) });
			estimationResult = estimationMethod->Calculation(solvingResult, prev_point + (B - prev_point) / 2, (B - prev_point) / 2, function);
			solvingResult = solvingMethod->Calculation(solvingResult, prev_point + (B - prev_point) / 2, (B - prev_point) / 2, function);
			result.push_back({ B, solvingResult, abs(solvingResult - estimationResult) });
		}
	}
	else
	{
		result.push_back({ B, Yc, 0 });
		double solvingResult;
		double estimationResult;
		double h = (B - A) / 10;
		double k = pow(2, eps_order(eps));
		double current_point = B-h;
		double prev_point = B;
		double prev_solvingResult=Yc;
		while ((current_point + h)-A >= Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -h, function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -h, function);
			while (abs(solvingResult - estimationResult)>eps&&h != Hmin)
			{
				if (h / 2 <= Hmin)
				{
					current_point += (h - Hmin);
					h = Hmin;
					solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -h, function);
					estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -h, function);
					HminNum++;
				}
				else
				{
					h /= 2;
					current_point += h;
					solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -h, function);
					estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -h, function);
				}
			}
			if (abs(solvingResult - estimationResult) > eps)
				numOfUnsolvablePoints++;
			if (abs(solvingResult - estimationResult) < eps / k)
				h *= 2;
			result.push_back({ current_point, solvingResult, abs(solvingResult - estimationResult) });
			prev_point = current_point;
			prev_solvingResult = solvingResult;
			current_point -= h;
			
		}
		if (current_point-A <= 2 * Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -(prev_point-A-Hmin), function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -(prev_point - A - Hmin), function);
			result.push_back({ A + Hmin, solvingResult, abs(solvingResult - estimationResult) });
			estimationResult = estimationMethod->Calculation(solvingResult, A+Hmin,Hmin, function);
			solvingResult = solvingMethod->Calculation(solvingResult, A + Hmin, Hmin, function);
			result.push_back({ A, solvingResult, abs(solvingResult - estimationResult) });
		}
		else if (current_point-A <= 1.5*Hmin)
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -(prev_point-A) , function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -(prev_point - A), function);
			result.push_back({ A, solvingResult, abs(solvingResult - estimationResult) });
		}
		else
		{
			solvingResult = solvingMethod->Calculation(prev_solvingResult, prev_point, -((prev_point-A) / 2), function);
			estimationResult = estimationMethod->Calculation(prev_solvingResult, prev_point, -((prev_point - A) / 2), function);
			result.push_back({ prev_point - (prev_point-A) / 2, solvingResult, abs(solvingResult - estimationResult) });
			estimationResult = estimationMethod->Calculation(solvingResult, A + (prev_point - A) / 2, -((prev_point - A) / 2), function);
			solvingResult = solvingMethod->Calculation(solvingResult, A + (prev_point - A) / 2, -((prev_point - A) / 2), function);
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
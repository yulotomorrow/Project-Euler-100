#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
using namespace std;

//1, 2, 5, 10, 20, 50, 100, 200
//solve 10 and extend to 100 then 200
//combinations (n+r-1)!/r!(n-1)! n:pn

int Factorial(int n) 
{
	int f = 1;
	for (int i = 1; i <= n; ++i) 
	{
		f *= i;
	}
	return f;
}

long long FactorialReduce(int f1, int f2) 
{
	long long f = 1;
	for (int i = f2 + 1; i <= f1; ++i)
	{
		f *= i;
	}
	return f;
}

long long DivideCases(int num1, int num2, int caseNum)
{
	long long result = 0;
	if (caseNum % 3 == 1) 
	{
		result = FactorialReduce((num1 + 2 - 1), (num1 - 1))/ 2 + 1;
	}
	else if (caseNum % 3 == 2)
	{
		result = num2 * FactorialReduce((num1 + 2 - 1), (num1 - 1) )/ 2 + 1;
	}
	else 
	{
//		result = FactorialReduce((num1 + 2 - 1), (num1 - 1) )/2 + FactorialReduce((num2 + 5 - 1), (num2- 1)) / Factorial(5 ) + 1;
		result = FactorialReduce((num1 + 2 - 1), (num1 - 1)) / 2 + 1 + 1;
	}
	return result;
}

void CoinProblem() 
{
	int p1 = 1;
	//p2 = {2*p1, p2}
	int p2 = 1 + 1;
	//p5 = {p1+2*p2, p5}
	int p5 = 1 * 3 + 1;
	//p10 = {2*p5, 5*p2(one extra), p10}
//	int p10 = Factorial(p5 + 2 - 1) / Factorial(p5-1) /Factorial(2) + Factorial(p2 + 5 - 1) / Factorial(p2- 1) / Factorial(5 ) + 1;
	int p10 = Factorial(p5 + 2 - 1) / Factorial(p5 - 1) / Factorial(2) + 1 + 1;
	cout << p10 << "\n";
	vector<int> storage = { p1, p2 };
	long long result = 1;
	for (int caseNum = 2; caseNum <= 7; ++caseNum)
	{
		result = DivideCases(storage[caseNum -1], storage[caseNum - 2], caseNum);
		cout << result << "\n";
		storage.push_back(result);
	}
	cout << result << "\n";
}

// Dynamic programming >_<

int CoinRecursion()
{
	int max = 200;
	array<int, 8> coinValue = { 1, 2, 5, 10, 20, 50, 100, 200 };
	const int coinType = 8;
	array<array<int, 201>, 9> storage = {};
	for (int n = 0; n <= max; ++n)
	{
		if (n == 0)
		{
			for (int m = 0; m <= coinType; ++m)
				storage[m][0] = 1;
		}
		else {
			for (int m = 0; m <= coinType; ++m)
			{
				if (m == 0)
					storage[m][n] = 0;
				else
				{
					if (n - coinValue[m - 1] >= 0)
					{
						storage[m][n] = storage[m - 1][n] + storage[m][n - coinValue[m - 1]];
//						cout << storage[m][n] << "\n";
					}
					else
						storage[m][n] = storage[m - 1][n];
				}
			}
		}
	}
	return storage[coinType][max];
}

void CoinProblemV2() 
{
	vector<int> coinValue = { 1, 2, 5, 10, 20, 50, 100, 200 };
	int maxValue = 200;
	int coinType = 8;

}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << CoinRecursion() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
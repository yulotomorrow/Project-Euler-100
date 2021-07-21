#include <iostream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

//1, 2, 5, 10, 20, 50, 100, 200
//solve 10 and extend to 100 then 200
//combinations (n+r-1)!/r!(n-1)! n:pn

int Factorio(int n) 
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
		result = FactorialReduce((num1 + 2 - 1), (num1 - 1) )/2 + FactorialReduce((num2 + 5 - 1), (num2- 1)) / Factorio(5 ) + 1;
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
	int p10 = Factorio(p5 + 2 - 1) / Factorio(p5-1) /Factorio(2) + Factorio(p2 + 5 - 1) / Factorio(p2- 1) / Factorio(5 ) + 1;
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

int main()
{
	auto startTime = chrono::system_clock::now();

	CoinProblem();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
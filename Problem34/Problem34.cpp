#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
using namespace std;

array<int, 10> DigitFactorial() 
{
	array<int, 10> digitFactorial = {};
	digitFactorial[0] = 1;
	int factorio = 1;
	for (int i = 1; i <= 9; ++i) 
	{
		factorio *= i;
		digitFactorial[i] = factorio;
		cout << factorio << "\n";
	}
	return digitFactorial;
}

// Digits: 3-7, base on factorial results
// Results are very few, think about how to limit range further
void CheckCuriousFactorial(array<int, 10> factorio)
{
	int digitNum = 7;
	int factorialSum = 0;
	int sum = 0;
	vector<int> curious = {};
	
	for (int a = 10; a <= digitNum * factorio.back(); ++a)
	{
		int num = a;
		bool zeroDigitStart = true;
		factorialSum = 0;
		for (int i = digitNum; i > 0; --i)
		{
			int currentDigit = num / (int)pow(10, i - 1);
			if(currentDigit == 0 && zeroDigitStart)
			{
				factorialSum = 0;
			}
			else 
			{
				zeroDigitStart = false;
				factorialSum += factorio[currentDigit];
				num = num % (int)pow(10, i - 1);
			}
		}
		if (factorialSum == a)
		{
			curious.push_back(a);
			cout << a << "\n";
		}
	}
	for (auto& b : curious)
	{
		sum += b;
	}
	cout << sum << "\n";
}

// Actually there are only two such number, 145 and 40585, which will be used in later problems.
int main()
{
	auto startTime = chrono::system_clock::now();

	array<int, 10> factorio = DigitFactorial();
	CheckCuriousFactorial(factorio);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
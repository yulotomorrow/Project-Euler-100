#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <chrono>
using namespace std;

// The closer r to n/2, the larger the result is. We just increase r gradually until larger than 1 million
int CombinationFactorial(int n) 
{
	int factorial = 1;
	int limit = n / 2;
	int r = limit;
	for (int i = 1; i <= limit; ++i)
	{
		if (factorial <= 1000000)
		{
			factorial *= (n - i + 1);
			factorial /= i; // forgot integer division again...
//			cout << factorial << "\n";
		}
		else 
		{
			r = i - 1;
			break;
		}
	}
	return r;
}

void CombinationFactorialNum() 
{
	int count = 0;
	for (int n = 1; n <= 100; ++n) 
	{
		int r = CombinationFactorial(n);
		if (r != n / 2)
			count += (n - 2 * r + 1);
	}
	cout << count << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CombinationFactorialNum();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
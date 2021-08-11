#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <chrono>
using namespace std;

bool IsCoPrime(int a, int b) 
{
	while (a % b != 0) 
	{
		int temp = b;
		b = a % b;
		a = temp;
		if (b == 1)
			return true;
	}
	return false;
}

// Get rid of every not reduced fraction
void ProperFractionCount()
{
	int bound = 12000;
	int nonRepeatFraction = 0;
	int lowerLimit = 0;
	double upperLimit = 0;
	for (int i = 2; i <= bound; ++i)
	{
//		nonRepeatFraction = 0;
		lowerLimit = i / 3;
		upperLimit = i / 2.0;
		for (int j = lowerLimit + 1; j < upperLimit; ++j)
		{
			if (IsCoPrime(i, j))
				++nonRepeatFraction;
		}
//		fractionCount += nonRepeatFraction;
//		cout << nonRepeatFraction << "\n";
	}
	cout << nonRepeatFraction << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	ProperFractionCount();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
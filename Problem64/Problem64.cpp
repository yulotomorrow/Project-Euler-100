#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;

// when 3 terms all be the same: leading term, numerator and denomenator, we can say it cycled.

void CheckCycle() 
{
	array<int, 3> initialValue = {};
	int oddCycle = 0;
	for (int n = 2; n <= 10000; ++n) 
	{
		int baseValue = (int)sqrt(n);
		int steps = 0;
		if (pow(baseValue, 2) != n) 
		{
			array<int, 3> currentValue = {};

		}
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
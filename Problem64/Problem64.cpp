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
	int cycle = 0;
	double fraction = 0.0;
	int oddCycle = 0;
	
	for (int n = 2; n <= 10000; ++n) 
	{		
		int baseValue = (int)sqrt(n);
		int steps = 0;
		if (pow(baseValue, 2) != n) 
		{		
			int cycleStep = 0;
			initialValue[0] = (int)(1.0 / (sqrt(n) - baseValue));			
			initialValue[2] = n - pow(baseValue, 2);
			initialValue[1] = baseValue - initialValue[2] * initialValue[0];
			cycle = initialValue[0];
			fraction = (1.0 / (sqrt(n) - baseValue)) - cycle;
			double fraction2 = fraction;
			int cycle2 = cycle;
			array<int, 3> currentValue = initialValue;
			do
			{
				++cycleStep;
				currentValue[0] = (int)(currentValue[2] / (sqrt(n) + (float)currentValue[1]));
				currentValue[2] = (n - pow(currentValue[1], 2))/ currentValue[2];
				currentValue[1] = - currentValue[1] - currentValue[2] * currentValue[0];
				cycle2 = (int)(1.0 / fraction2);
				fraction2 = 1/ fraction2 - cycle2;
			}while (currentValue != initialValue);
			if (cycleStep % 2 != 0)
				++oddCycle;
		}
	}
	cout << oddCycle << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckCycle();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

// Only store first 3 digits and do recursion, count how many times larger than 1000
// Try to see the error first and decide if use more digits
//Doing digit sum is a bit unnecessary for this one
int DigitAccumulate() 
{
	int index = 12;
	int digits = 3;
	int fibo1 = 89;
	int fibo2 = 144;
	int fiboTemp = 0;
	while (digits < 1000) 
	{
		fiboTemp = fibo1 + fibo2;
		if (fiboTemp > 999 && digits < 4) 
		{
			++digits;
		}	
		if (fiboTemp > 9999 && digits < 5)
		{
			++digits;
		}
		// Actually, it needs 6 digits to converge...
		if (fiboTemp > 99999)
		{
			++digits;
			fiboTemp = fiboTemp / 10;
			fibo2 = fibo2 / 10;
		}

		fibo1 = fibo2;
		fibo2 = fiboTemp;
		++index;
	}
	return index;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << DigitAccumulate() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
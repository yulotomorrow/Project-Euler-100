#include <iostream>
#include <chrono>
using namespace std;

// We throw away +1, and a recursion appear: a(n+1)/b(n+1) = b(n)/2*b(n)+a(n)
// We also know a(n)/b(n) => sqrt(2) - 1, if we want a(n)+b(n) have more digits there's a clear limit of b(n)
void NumeratorExceedFraction()
{
	double a = 0.1;
	double b = 0.2;
	double temp = 0.0;
	int exceedFractionNum = 0;
	const double ref = 1 / sqrt(2); // I see every fraction as sqrt(2) already and b must larger than it to have exceed digit
	for (int i = 2; i <= 1000; ++i) 
	{
		temp = a;
		a = b;
		b = 2 * b + temp;
		// The number doesn't need to be exact so I used double to cut down, and convenient to compare
		if (b > 1) 
		{
			a /= 10;
			b /= 10;
		}
		// This step use a >= 1 also work (maybe more rigorous) but I just do a math trick here ;)
		if (b > ref)
			++exceedFractionNum;
	}
	cout << exceedFractionNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	NumeratorExceedFraction();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
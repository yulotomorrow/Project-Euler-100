#include <iostream>
#include <chrono>
using namespace std;

// The larget the denominator the better. Basically find a pair a/b where 3/7 - a/b the minimum.
// (3 * b - 7 * a)/(7*b) minimum, so b as large as possible, while (3*b) % 7 = 1
void FindClosestFraction() 
{
	int a = 1;
	int d = 1;
	for (int b = 1000000; b > 1; --b) 
	{
		if ((3 * b) % 7 == 1) 
		{
			a = (3 * b) / 7;
			d = b;
			break;
		}
	}
	// If this fraction is very close to 3/7, it's highly unlikely need to simplify (?)
	cout << a << " " << d << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindClosestFraction();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
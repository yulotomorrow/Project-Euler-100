#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

long SumOfSquare() 
{
	long sum = 0;
	for (int i = 1; i <= 100; ++i) 
	{
		sum += pow(i, 2);
	}
	return sum;
}

long SquareOfSum()
{
	long sum = 0;
	for (int i = 1; i <= 100; ++i)
	{
		sum += i;
	}
	return pow(sum, 2);
}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << SquareOfSum() - SumOfSquare()<< "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
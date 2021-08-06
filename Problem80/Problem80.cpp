#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;

void SquareRootGenerate( int number) 
{
	double seed = sqrt(number);
}

void SquareRootDigit() 
{
	for (int i = 2; i < 100; ++i)
	{
		double seed = sqrt(i);
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
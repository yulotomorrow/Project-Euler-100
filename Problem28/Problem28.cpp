#include <iostream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

void Spiral() 
{
	int spiralNum = 1;
	for (int i = 3; i <= 1001; i += 2) 
	{		
		int circle = (pow(i, 2) * 2 - 3 * (i - 1)) * 2;
		spiralNum += circle;
	}
	cout << spiralNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	Spiral();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
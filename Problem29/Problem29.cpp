#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
using namespace std;

// All terms 99*99, and just find repeat terms.
// Since no case that two numbers are not directly power of another happen in <=100, consider the results generating 2 digits and under
// 2-9^2, 2-4^3, 2-3^4, 2^5, 2^6

void DistinguishPower() 
{
	int powers = 99 * 99;
	for (int i = 2; i < 10; ++i) 
	{
		for (int j = 2; j <= 100; ++j) 
		{

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
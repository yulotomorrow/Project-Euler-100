#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
using namespace std;

// All terms 99*99, and just find repeat terms.
// Since no case that two numbers are not directly power of another happen in <=100, consider the results generating 2 digits and under
// 2-9^2, 2-4^3, 2-3^4, 2^5, 2^6, the key point is deal with 2, 4, 8, etc
// Larger number lower power has been covered already, store the power and do 100 / power, don't need to know base

void DistinguishPower() 
{
	int powers = 99 * 99;
	for (int i = 2; i < 10; ++i) 
	{
		vector<int> bases = {};
		for (int j = 2; j <= 6; ++j) 
		{
			if (pow(i, j) < 100)
			{
				bases.push_back(j);
			}
//				powers -= (100 / j - 1);
		}
	}
	cout << powers << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	DistinguishPower();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
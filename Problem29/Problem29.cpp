#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <chrono>
using namespace std;

// All terms 99*99, and just find repeat terms.
// Since no case that two numbers are not directly power of another happen in <=100, consider the results generating 2 digits and under
// 2-9^2, 2-4^3, 2-3^4, 2^5, 2^6, the key point is deal with 2, 4, 8, etc
// Larger number lower power has been covered already, store the power and do 100 / power, don't need to know base

int RepeatPower(int power) 
{
	unordered_set<int> distinguistTerms = {};
	const int limit = 100;
	for (int x = 2; x <= limit; ++x)
	{
		distinguistTerms.insert(x * power);
	}
	for (int i = power-1; i >= 1; --i) 
	{
		for (int j = 2; j <= limit; ++j)
		{
			if (distinguistTerms.find(i * j) != distinguistTerms.end())
				distinguistTerms.erase(i * j);
		}
	}
	return (limit - 1 - distinguistTerms.size());
}

void DistinguishPower() 
{
	const int limit = 100;
	int powers = pow((limit-1), 2);
	unordered_set<int> bases = {};
	for (int i = 2; i <= limit; ++i) 
	{
		// Repeat calculating 4, 8, 9, get rid of it
		if (bases.find(i) == bases.end())
		{
			for (int j = 2; j <= limit; ++j)
			{
				if (pow(i, j) <= limit) // 10 and 100
				{
					bases.insert(pow(i, j));
					powers -= RepeatPower(j);
//					cout << RepeatPower(j) << " " << j << "\n";
				}
			}
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
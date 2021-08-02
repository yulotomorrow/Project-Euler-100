#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
using namespace std;

void PrimeNumber(int upperLimit, set<int>& prime)
{
	for (int i = 2; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			if (i % a == 0)
			{
				goto skip;
			}
		}
		prime.insert(i);
	skip:
		;
	}
}

void CheckConjuncture(const set<int>& prime)
{
	for (int i = 3; i < 1000000; i += 2) 
	{
		bool condition = false;
		if (prime.find(i) == prime.end()) 
		{
			for (int j = 1; j < sqrt(i); ++j) 
			{
				if (prime.find(i - 2 * pow(j, 2)) != prime.end())
				{
					condition = true;
					break;
				}
			}
			if (!condition)
			{
				cout << i << "\n";
				return;
			}
		}
	}
}


int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList = {};
	set<int>& prime = primeList;
	PrimeNumber(10000, prime);
	CheckConjuncture(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
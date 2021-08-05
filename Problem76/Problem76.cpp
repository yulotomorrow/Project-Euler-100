#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
using namespace std;

// I just directly use problem 31 code, the same problem only parameter changed
// Problem 76: Note that at least 2 integers, so 100 not included as choice
// Problem 78 better use combination theory, it will be easier to calculate divisor.

void PrimeNumber(int upperLimit, vector<int>& prime)
{
	prime.push_back(2);
	prime.push_back(3);
	for (int i = 5; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			if (a <= sqrt(i))
			{
				if (i % a == 0)
				{
					goto skip;
				}
			}
			else
				break;
		}
		prime.push_back(i);
	skip:
		;
	}
}

// the bound of problem 77 is actually small?! (71)

int IntegerRecursion()
{
	int max = 100;
	const int numType = 99;
	array<array<int, 101>, 100> storage = {};
	for (int n = 0; n <= max; ++n)
	{
		if (n == 0)
		{
			for (int m = 0; m <= numType; ++m)
				storage[m][0] = 1;
		}
		else {
			for (int m = 0; m <= numType; ++m)
			{
				if (m == 0)
					storage[m][n] = 0;
				else
				{
					if (n - m >= 0)
					{
						storage[m][n] = storage[m - 1][n] + storage[m][n - m];
					}
					else
						storage[m][n] = storage[m - 1][n];
				}
			}
		}
	}
	return storage[numType][max];
}

int IntegerRecursion(vector<int>& prime)
{
	int max = 1000;
	const int numType = 99;
	array<array<int, 1001>, 100> storage = {};
	for (int n = 0; n <= max; ++n)
	{
		if (n == 0)
		{
			for (int m = 0; m <= numType; ++m)
				storage[m][0] = 1;
		}
		else {
			for (int m = 0; m <= numType; ++m)
			{
				if (m == 0)
					storage[m][n] = 0;
				else
				{
					if (n - prime[m - 1] >= 0)
					{
						storage[m][n] = storage[m - 1][n] + storage[m][n - prime[m - 1]];
					}
					else
						storage[m][n] = storage[m - 1][n];
					if (storage[m][n] > 5000)
						return n;
				}
			}
		}
	}
	return 0;
//	return storage[numType][max];
}

int main()
{
	auto startTime = chrono::system_clock::now();

	// problem 77
	vector<int> primeList = {};
	vector<int>& prime = primeList;
	PrimeNumber(1000, prime);
	cout << IntegerRecursion(prime) << "\n";
	// problem 76
	cout << IntegerRecursion() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
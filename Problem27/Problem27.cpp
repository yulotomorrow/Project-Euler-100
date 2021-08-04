#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <chrono>
using namespace std;

void PrimeNumber(int upperLimit, set<int>& prime)
{
	prime.insert(2);
	prime.insert(3);
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
		prime.insert(i);
	skip:
		;
	}
}

bool CheckPrime(int num, const set<int>& prime)
{
	if (num <= 1)
		return false;
	for (auto& a : prime)
	{
		if (a <= sqrt(num))
		{
			if (num % a == 0)
			{
				return false;
			}
		}
		else
			break;
	}
	return true;
}

// b must be positive,a could be negative, depending it will be increasing or decreasing
// assume this solution will be worse than the example 2 (where b > 1000), |a| < 80
// but use 1000 is still fast enough (run away)

void QuadraticPrime(const set<int>& prime)
{
	int maxChain = 0;
	int result = 0;
	for (auto& b : prime) 
	{
		if (b < 1000)
		{
			for (int a = -1000; a <= 1000; ++a) 
			{
				int n = 1;
				int checkPrime = pow(n, 2) + n * a + b;
				while (CheckPrime(checkPrime, prime))
				{
					++n;
					checkPrime = pow(n, 2) + n * a + b;
				}
				if (n > maxChain) 
				{
					maxChain = n;
					result = a * b;
//					cout << result << " " << n << "\n";
				}
			}
		}
		else
			break;
	}
	cout << result << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(10000, prime);
	QuadraticPrime(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
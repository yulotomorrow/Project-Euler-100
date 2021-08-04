#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
using namespace std;

// They give the hint of 11 primes, just brute force it until it's done (no

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

bool CheckTruncatePrime(int num, set<int>& prime)
{
	int testRightToLeft = num;	
	while (testRightToLeft / 10 != 0) 
	{
		testRightToLeft /= 10;
		if (prime.find(testRightToLeft) == prime.end())
			return false;
	}
	int testLeftToRight = num;
	while (testLeftToRight / 10 != 0)
	{
		testLeftToRight %= (int)pow(10, (int)log10(testLeftToRight));
		if (prime.find(testLeftToRight) == prime.end())
			return false;
	}
	return true;
}

void TruncatePrime(set<int>& prime)
{
	int primeCount = 0;
	int primeSum = 0;
	for (auto& a : prime)
	{
		if (CheckTruncatePrime(a, prime) && a > 10) 
		{
			primeSum += a;
			++primeCount;
//			cout << a << "\n";
		}
		if (primeCount == 11)
			break;
	}
	cout << primeSum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(1000000, prime);
	TruncatePrime(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
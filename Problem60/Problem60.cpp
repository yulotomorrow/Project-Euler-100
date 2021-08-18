#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <algorithm>
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

bool CheckPrime(long long num, const set<int>& prime)
{
	if (num == 2 || num == 3)
		return true;
	for (auto& a : prime)
	{
		if (a <= sqrt(num))
		{
			if (num % (long long)a == 0)
			{
				return false;
			}
		}
		else
			break;
	}
	return true;
}

// Let's assume this problem just requires us to find the fifth one based on the 4 we already know
// This doesn't really guarantee the result would be the smallest... so let's do it and see

void FindFifthPrime(const set<int>& prime)
{
	array<int, 4> fourPrimes = {3, 7, 109, 673};
	int primeSum = 792;
	int num = 673;
	while (num < 1e9) 
	{
		if (CheckPrime(num, prime))
		{
			bool isPrime = true;
			for (auto& a : fourPrimes)
			{
				isPrime = isPrime && CheckPrime(a + num * pow(10, (int)log10(a) + 1), prime);
				isPrime = isPrime && CheckPrime(num + a * pow(10, (int)log10(num) + 1), prime);
			}
			if (isPrime)
			{
				cout << primeSum + num << "\n";
				return;
			}
		}
		++num;
	}
}

// We found a reference in last method, what got form the last one is not the correct answer, but it gave us a upper bound of numbers.

void FindPrimeList(const set<int>& prime)
{
	vector<int> fivePrimes = { };
	int primeSum = 0;
	int minPrimeSum = 1e9;
	int initialNum = 3;
	// I'm changing bound accrording to intermidiate answers
	while (initialNum < 2.2e4)
	{
		while (!CheckPrime(initialNum, prime))
			++initialNum;
		primeSum = 0;
		fivePrimes = { };
		for (int num = initialNum; num < 1.1e5; ++num)
		{			
			if (CheckPrime(num, prime))
			{
				bool isPrime = true;
				for (auto& a : fivePrimes)
				{
					long long num1 = (long long)a + (long long)num * (long long)pow(10, (int)log10(a) + 1);
					long long num2 = (long long)num + (long long)a * (long long)pow(10, (int)log10(num) + 1);
					isPrime = isPrime && CheckPrime(num1, prime);
					isPrime = isPrime && CheckPrime(num2, prime);
					if (!isPrime)
						break;
				}
				if (isPrime)
				{
					fivePrimes.push_back(num);
					primeSum += num;
				}
				if (fivePrimes.size() == 5)
				{
					if (primeSum < minPrimeSum)
					{
						minPrimeSum = primeSum;
						cout << minPrimeSum << " " << fivePrimes[0] << " " << fivePrimes[4] << "\n";
					}
					break;
				}
			}
		}
		++initialNum;
	}
	cout << minPrimeSum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(1000000, prime);
	FindPrimeList(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

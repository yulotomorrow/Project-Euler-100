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
	for (auto& initialNum : prime)
	{
		for (int num = initialNum; num < 1e4; ++num)
		{			
			if (CheckPrime(num, prime))
			{
				bool isPrime = true;
				if (fivePrimes.size() == 0)
				{
					fivePrimes.push_back(num);
					primeSum = num;
				}
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
						cout << minPrimeSum << " " << fivePrimes[0] << " " << fivePrimes[3] << "\n";
					}
					break;
				}
			}
		}
	}
	cout << minPrimeSum << "\n";
}

// This problem is actually backtracking! There are cases the last method fail to cinsider
// I used 1e4 as boundary to try
bool FindPrimeRecursive(const set<int>& prime, vector<int>& fivePrimes, int& minPrimeSum, int& primeSum)
{
	if (fivePrimes.size() == 5)
	{
		if (primeSum < minPrimeSum)
		{
			minPrimeSum = primeSum;
		}
		fivePrimes = {};
		primeSum = 0;
		return true;
	}
	for (auto& num : prime)
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
			if (FindPrimeRecursive(prime, fivePrimes, minPrimeSum, primeSum))
			{
				return true;
			}
			else 
			{
				fivePrimes.pop_back();
				primeSum -= num;
			}
		}
	}
	return false;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList = {};
	set<int>& prime = primeList;
	PrimeNumber(10000, prime);
//	FindPrimeList(prime);
	vector<int> fivePrimelist = { };
	vector<int>& fivePrimes = fivePrimelist;
	int primesSum = 0;
	int& primeSum = primesSum;
	int minimumPrimeSum = 1e9;
	int& minPrimeSum = minimumPrimeSum;
	FindPrimeRecursive(prime, fivePrimes, minPrimeSum, primeSum);
	cout << minPrimeSum << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

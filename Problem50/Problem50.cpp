#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
using namespace std;

//I'm very unhappy with the thought but it sounds very brute froce to me...

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

void FindConsecutivePrime(set<int>& prime)
{
	auto itr1 = prime.begin();
	auto itr2 = prime.begin();
	++itr2;
	int maxLength = 0;
	int targetPrime = 2;
	while (itr1 != prime.end() && itr2 != prime.end())
	{
		int sum = *itr1 + *itr2;
		int chainLength = 2;
		while (sum < 1000000) 
		{
			if (prime.find(sum) != prime.end() && chainLength > maxLength) 
			{
				maxLength = chainLength;
				targetPrime = sum;
			}
			++itr2;
			++chainLength;
			sum += *itr2;		
//			cout << maxLength << "\n";
		}
		++itr1;
		itr2 = itr1;
		++itr2;
	}
	cout << targetPrime << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(1000000, prime);
	FindConsecutivePrime(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
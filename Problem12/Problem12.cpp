#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

// This one made me want to rewrite the whole ProjEuler in an OOP project...

void PrimeNumber(int upperLimit, vector<int>& prime)
{
	for (int i = 3; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			if (i % a == 0)
			{
				goto skip;
			}
		}
		prime.push_back(i);
	skip:
		;
	}
}

//Divisor number: (n+1)*(m+1)*...
//Triangular number: n(n+1)/2
//If only need to know number of divisors, we don't even need to know corresponding prime.
int DivisorNum(int num, const vector<int>& prime)
{
	int i = num;
	int divisorNum = 1;
	vector<int> divisors = {};
	for (auto& a : prime)
	{
		if (i % a == 0)
		{
			int divisorCount = 0;
			while (i % a == 0)
			{
				++divisorCount;
				i = i / a;
			}
			divisors.push_back(divisorCount);
		}
	}
	for (auto& b : divisors) 
	{
		divisorNum *= (b + 1);
	}
//	cout << divisorNum << "\n";
	return divisorNum;
}

void TriangleNumDivisor() 
{
	vector<int> primeList = { 2 };
	vector<int>& prime = primeList;
	int n = 1;
	//need to evaluate upperlimit here, and speed largely depends on it, which I'm not satisfied with
	int upperLimit = 1000;
	PrimeNumber(upperLimit, prime);
	while (DivisorNum((n * (n + 1) / 2), prime) < 500) 
	{
		++n;
	}
	cout << n * (n + 1) / 2 << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	TriangleNumDivisor();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
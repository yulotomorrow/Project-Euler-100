#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <chrono>
using namespace std;

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

// In this problem, only need to match divisor
unordered_set<int> DivisorNum(int num, const vector<int>& prime)
{
	int i = num;
	unordered_set<int> divisors = {};
	for (auto& a : prime)
	{
		if (i % a == 0)
		{
			while (i % a == 0)
			{
				i = i / a;
			}
			divisors.insert(a);
		}
	}
	if (i < num) 
		divisors.insert(i);
	return divisors;
}

// Really? Is it worthy?
array<unordered_set<int>, 1000000> DivisorNumList(const vector<int>& prime) 
{
	array<unordered_set<int>, 1000000> divisorNumList = {};
	for (int i =0; i < 1000000; ++i) 
	{
		divisorNumList[i] = DivisorNum(i, prime);
	}
	return divisorNumList;
}

bool CompareDivisor(int num1, int num2, const vector<int>& prime) 
{
	const unordered_set<int> divisors1 = DivisorNum(num1, prime);
	const unordered_set<int> divisors2 = DivisorNum(num2, prime);
	for (auto& a : divisors1)
	{
		if (divisors2.find(a) != divisors2.end())
			return true;
	}
	return false;
}

// Get rid of every not reduced fraction
void ProperFractionCount(const vector<int>& prime)
{
	int fractionCount = 0;
	int repeatFraction = 0;
	for (int i = 2; i <= 1000000; ++i) 
	{
		repeatFraction = 0;
		for (int j = 1; j < i; ++j) 
		{
			if (CompareDivisor(i, j, prime))
				++repeatFraction;
		}
		fractionCount = fractionCount + (i - 1) - repeatFraction;
//		cout << fractionCount << "\n";
	}
	cout << fractionCount << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<int> primeNum = { 2 };
	vector<int>& prime = primeNum;
	PrimeNumber(1000, prime);
	ProperFractionCount(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
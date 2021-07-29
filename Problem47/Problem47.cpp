#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

void PrimeNumber(int upperLimit, vector<int>& prime)
{
	bool isPrime = true;
	for (int i = 2; i <= upperLimit; ++i)
	{
		isPrime = true;
		for (auto& a : prime)
		{
			if (i % a == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			prime.push_back(i);
	}
}

// In this problem, we don't need to know the num of each divisor, nor the value of divisor itself
int DistinctDivisorNum(int num, const vector<int>& prime)
{
	int i = num;
	int divisorNum = 0;
	vector<int> divisors = {};
	for (auto& a : prime)
	{
		if (i % a == 0)
		{
			while (i % a == 0)
			{
				i = i / a;
			}
			++divisorNum;
		}
		else if (i == 1)
			break;
	}
	return divisorNum;
}

void FourNumFourDivisor(const vector<int>& prime)
{
	int num = 647;
	int sequenceLength = 0;
	bool sequenceFound = false;
	while (!sequenceFound) 
	{
		if (DistinctDivisorNum(num, prime) == 4) 
		{
			++sequenceLength;
			if (sequenceLength == 4)
				sequenceFound = true;
		}
		else
			sequenceLength = 0;
		++num;
	}
	cout << num - 4 << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<int> primeNumber = {};
	vector<int>& prime = primeNumber;
	PrimeNumber(1e4, prime);
	FourNumFourDivisor(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
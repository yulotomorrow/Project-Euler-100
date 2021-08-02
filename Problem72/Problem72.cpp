#include <iostream>
#include <vector>
#include <array>
#include <set>
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
int PhiFunction(int num, const vector<int>& prime)
{
	int i = num;
	int phi = num;
	set<int> divisors = {};
	for (auto& a : prime)
	{ 
		bool isDivisor = false;
		while (i % a == 0)
		{
			i = i / a;
			isDivisor = true;
		}
		if (isDivisor)
		{
			divisors.insert(a);
		}
	}
	if (i != 1) 
		divisors.insert(i);
	for (auto& b : divisors)
	{
		phi = phi / b;
//		cout << phi <<" " << b << "\n";
		phi *= (b - 1);		
	}
	
	return phi;
}

// Get rid of every not reduced fraction
void ProperFractionCount(const vector<int>& prime)
{
	long long fractionCount = 0;
	const int limit = 1000000;
	for (int i = 2; i <= limit; ++i) 
	{
		fractionCount += PhiFunction(i, prime);
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
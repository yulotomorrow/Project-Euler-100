#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <string>
#include <chrono>
using namespace std;

// find all primes or 4 digits first, then check permutation
// numbers are small, just sort and compare is enough

void PrimeNumber(int upperLimit, vector<int>& prime)
{
	for (int i = 2; i <= upperLimit; ++i)
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

// very ineffective, but okay for small list (both total primes and digits), need to revisit
void CheckPrimePermutation(const vector<int>& prime)
{
	vector<string> primePerm = {};
	int indexAppend = 0;
	for (auto& a : prime) 
	{
		if (a < 999) 
		{
			++indexAppend;
		}
		else 
		{			
			string tempNum = to_string(a);
			sort(tempNum.begin(), tempNum.end());
			primePerm.push_back(tempNum);
		}
	}
	vector<int> primeIndex = {};
	int incresing = 0;
	for (int i = 0; i < primePerm.size(); ++i)
	{
		for (int j = i + 1; j < primePerm.size(); ++j) 
		{
			if (primePerm[i] == primePerm[j] && primePerm[i] != "1478")
			{
				incresing = prime[j + indexAppend] - prime[i + indexAppend];
				for (int k = j + 1; k < primePerm.size(); ++k)
				{
					if (primePerm[j] == primePerm[k] && (prime[k + indexAppend] - prime[j + indexAppend]) == incresing)
					{
						cout << prime[i + indexAppend] << prime[j + indexAppend] << prime[k + indexAppend] << "\n";
					}
				}
			}
		}
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	int primeLimit = 10000;
	vector<int> primeNumber = {};
	vector<int>& prime = primeNumber;
	PrimeNumber(primeLimit, prime);
	CheckPrimePermutation(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
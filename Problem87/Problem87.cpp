#include <iostream>
#include <string>
#include <array>
#include <set>
#include <deque>
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

void PrimePowerTriples(const set<int>& prime)
{
	int limit = 50000000;
	int limit2 = limit - pow(2, 2) - pow(2, 3);
	int count = 0;
	for (int i = 2; i < pow(limit, 1.0 / 4); ++i) 
	{ 
		if (prime.find(i) != prime.end())
		{
			for (int j = 2; j < pow((limit - pow(i, 4)), 1.0 / 3); ++j)
			{
				if (prime.find(j) != prime.end() && (limit - pow(i, 4) - pow(j, 3)) >= 4)
				{
					int maxValue = (int)sqrt(limit - pow(i, 4) - pow(j, 3));
					auto itr = prime.begin();
					while (itr != prime.end() && *itr <= maxValue) //
					{
						++count;
						++itr;
					}
				}
			}
		}
	}
	cout << count << "\n";
}

// Thinking about it, if we need to loop through all possibilities anyway, why not just let the set collide the repeating for us?
// I'm sorry, memory, I promise it's just temporary (wait what

void PrimePowerTriplesV2(const set<int>& prime)
{
	int limit = 50000000;
	int count = 0;
	set<int> results = {};
	long long num = 0;
	for (auto& a : prime)
	{
		num = pow(a, 2);
		for (auto& b : prime)
		{			
			if (b <= pow(limit, 1.0 / 3))
			{
				long long num1 = num;
				num1 += pow(b, 3);
				if (num1 > limit)
					break;
				for (auto& c : prime)
				{
					if (c <= pow(limit, 1.0 / 4))
					{
						long long num2 = num1;
						num2 += pow(c, 4);
						if (num2 > limit)
							break;
						else
							results.insert((int)num2);
					}
				}
			}
		}
	}
	cout << prime.size() << "\n";
	cout << results.size() << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber((int)sqrt(50000000)+1, prime);
	PrimePowerTriplesV2(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
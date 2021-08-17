#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <map>
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

bool CheckPrime(int num, const set<int>& prime)
{
	for (auto& a : prime)
	{
		if (a <= sqrt(num))
		{
			if (num % a == 0)
			{
				return false;
			}
		}
		else
			break;
	}
	return true;
}

// 8 prime family REQUIRES changing 3 (or 6 or more) digits, otherwise there will be several being divided by 3.
// Let's assume it happens in 6 digits, otherwise I don't even know how to deal with it...

void PrimeDigitSubsitute(const set<int>& prime)
{
	int number = 1001;
	while (true) 
	{
		if (number % 10 == 1 || number % 10 == 3 || number % 10 == 7 || number % 10 == 9)
		{
			string numString = to_string(number);
			vector<int> repeatDigit = {};
			vector<int> repeatDigit2 = {};
			auto itr = numString.rbegin();
			int digitCount = 1;
			while (itr != numString.rend())
			{
				if (*itr == '0')
				{
					repeatDigit.push_back(digitCount);
				}
				else if (*itr == '1')
				{
					repeatDigit2.push_back(digitCount);
				}
				++itr;
				++digitCount;
			}
			// Should have written it as a separate function but anyway
			if (repeatDigit.size() >= 3)
			{				
				int repeatLength = repeatDigit.size();
				vector<int> repeats = { repeatDigit[0], repeatDigit[1], repeatDigit[2] };
				vector<int> index = { 0, 1, 2 };
				while (true)
				{
					int primeCount = 0;
					int increaseStep = 0;
					for (auto& a : repeats)
					{
						increaseStep += pow(10, a - 1);
					}
					// check prime
					int numCopy = number;
					for (int x = 0; x <= 9; ++x)
					{
						primeCount += CheckPrime(numCopy, prime) ? 1 : 0;
						numCopy += increaseStep;
					}
					if (primeCount >= 8)
					{
						cout << number << "\n";
						return;
					}
					// generate combination then check
					auto itr2 = index.rbegin();
					int b = 0;
					while (itr2 != index.rend() && *itr2 == repeatLength - 1 - b) 
					{
						++itr2;
						++b;
					}
					if (itr2 == index.rend())
						break;
					else 
					{
						int temp = *itr2 + 1;
						while (itr2 != index.rbegin())
						{
							*itr2 = temp;
							--itr2;
							++temp;
						}
						*itr2 = temp;
						int temp2 = 0;
						for (auto & c : index) 
						{
							repeats[temp2] = repeatDigit[c];
							++temp2;
						}
					}				
				}
			}
			if (repeatDigit2.size() >= 3)
			{
				int repeatLength = repeatDigit2.size();
				vector<int> repeats = { repeatDigit2[0], repeatDigit2[1], repeatDigit2[2] };
				vector<int> index = { 0, 1, 2 };
				while (true)
				{
					int primeCount = 0;
					int increaseStep = 0;
					for (auto& a : repeats)
					{
						increaseStep += pow(10, a - 1);
					}
					int numCopy = number;
					for (int x = 1; x <= 9; ++x)
					{
						primeCount += CheckPrime(numCopy, prime) ? 1 : 0;
						numCopy += increaseStep;
					}
					if (primeCount >= 8)
					{
						// should have checked if this one is prime, if not, add increaseStep till it is, but I'm lazy here
						cout << number << "\n";
						return;
					}
					// generate combination, check if it's the last combination
					auto itr2 = index.rbegin();
					int b = 0;
					while (itr2 != index.rend() && *itr2 == repeatLength - 1 - b)
					{
						++itr2;
						++b;
					}
					if (itr2 == index.rend())
						break;
					else
					{
						int temp = *itr2 + 1;
						while (itr2 != index.rbegin())
						{
							*itr2 = temp;
							--itr2;
							++temp;
						}
						*itr2 = temp;
						int temp2 = 0;
						for (auto& c : index)
						{
							repeats[temp2] = repeatDigit2[c];
							++temp2;
						}
					}
				}
			}
		}
		++number;
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(4000, prime);
	PrimeDigitSubsitute(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

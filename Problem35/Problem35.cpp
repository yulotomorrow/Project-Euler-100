#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
using namespace std;

// This one made me want to rewrite the whole ProjEuler in an OOP project...

void PrimeNumber(int upperLimit, set<int>& prime)
{
	for (int i = 2; i <= upperLimit; ++i)
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

void CheckCircular(const set<int>& prime)
{
	string checkNumS = "";
	int checkNum = 1;
	int circularNum = 0;
	bool isCircular = true;
	int digits = 1;
	for (auto& a : prime) 
	{
		checkNum = a;
		checkNumS = to_string(checkNum);
		isCircular = true;
		digits = 1;
		while (checkNum / 10 > 0) 
		{
			rotate(checkNumS.begin(), checkNumS.begin() + 1, checkNumS.end());
			if (prime.find(stoi(checkNumS)) == prime.end()) 
			{
				isCircular = false;
				break;
			}
			checkNum /= 10;
			++digits;
		}
		if (isCircular) 
		{
			++circularNum;
		}
	}
	cout << round(circularNum) << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeNumber = {};
	set<int>& prime = primeNumber;
	PrimeNumber(1000000, prime);
	CheckCircular(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
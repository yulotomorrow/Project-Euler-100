#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <chrono>
using namespace std;

void PrimeNumber(int upperLimit, set<int>& prime)
{
	prime.insert(2);
	prime.insert(3);
	for (int i = 5; i <= upperLimit; ++i)
	{
		for(auto& a : prime)
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

int TotientFunction(int num, const set<int>& prime)
{
	int i = num;
	int divisorNum = num;
	for (auto& a : prime)
	{
		if (a <= sqrt(num))
		{
			if (i % a == 0)
			{
				while (i % a == 0)
				{
					i /= a;
				}				
				divisorNum /= a; // divide first or easy to out of bound
				divisorNum *= (a - 1);
			}
		}
		else
			break;
	}
	if (i != 1)
	{		
		divisorNum /= i;
		divisorNum *= (i - 1);
	}
	return divisorNum;
}

void TotientPermutation(const set<int>& prime)
{
	const int limit = 1e7;
	int value = 0;
	long double minRatio = 1e7;
	for (int i = 10; i < limit; ++i) 
	{
		int totient = TotientFunction(i, prime);
		string numString = to_string(i);
		string totString = to_string(totient);
		sort(numString.begin(), numString.end());
		sort(totString.begin(), totString.end());
		if (numString == totString)
		{
			long double ratio = (i * 1.0) / (totient * 1.0);
			if (ratio < minRatio) 
			{
				minRatio = ratio;
				value = i;				
			}
//			cout << i <<" " << totient << " " << ratio << "\n";
		}
	}
	cout << value << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> primeList;
	set<int>& prime = primeList;
	PrimeNumber(((int)sqrt(1e7) + 1), prime);//
	TotientPermutation(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
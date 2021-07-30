#include <iostream>
#include <vector>
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


bool CheckPrime(int num, const vector<int>& prime)
{
	int limit = (int)sqrt(num) + 1;
	for (auto& a : prime) 
	{
		if (a < num)
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

void PrimePercentage(const vector<int>& prime)
{
	double primePercentage = 0;
	int primeCircle = 1;
	int num = 1;
	int totalNum = 1;
	int primeNum = 0;
	do 
	{
		primeCircle += 2;
		primeNum += CheckPrime(num + (primeCircle - 1), prime) ? 1 : 0;
		primeNum += CheckPrime(num + 2 * (primeCircle - 1), prime) ? 1 : 0;
		primeNum += CheckPrime(num + 3 * (primeCircle - 1), prime) ? 1 : 0;
		primeNum += CheckPrime(num + 4 * (primeCircle - 1), prime) ? 1 : 0;
		num += 4 * (primeCircle - 1);
		totalNum += 4;
//		cout << (double)primeNum / (double)totalNum << " " << num << "\n";
	} while ((double)primeNum / totalNum >= 0.1);
	cout << primeCircle << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<int> primeNum = { 2 };
	vector<int>& prime = primeNum;
	PrimeNumber(1000000, prime);
	PrimePercentage(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void PrimeNumber(vector<int> &prime) 
{
	for (int i = 3; i <= 20; ++i) 
	{		
		for (auto& a : prime) 
		{
			if (i % a == 0)
			{
				cout << i << " " << a << "\n";
				goto skip;
			}						
		}	
		prime.push_back(i);	
	skip:
		;
	}
}

int MinimunDividable(const vector<int>& prime)
{
	int num = 1;
	
	for (auto& a : prime)
	{
		num *= a;
	}
	for (int i = 1; i <= 20; ++i)
	{
		if (num % i != 0) 
		{
			for (auto itr = prime.begin(); itr != prime.end(); ++itr)
			{
				if ((*itr * num) % i == 0)
				{
					num *= *itr;
					break;
				}
			}
		}
	}
	return num;
}

int main()
{
	auto startTime = chrono::system_clock::now();
	vector<int> primeNumber = {};
	primeNumber.push_back(2);
	vector<int>& prime = primeNumber;
	PrimeNumber(prime);
	
	cout << MinimunDividable(prime) << "\n";
	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

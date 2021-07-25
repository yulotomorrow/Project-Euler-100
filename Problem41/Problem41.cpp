#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
using namespace std;

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


// Start from n = 7 because there's none in n = 8,9
array<int, 7> PrevPandigital()
{
	array<int, 7> digits = { 7, 6, 5, 4, 3, 2, 1 };
	vector<int> nums = {};
	for (int i = 6; i > 0; --i) 
	{
		if (digits[i-1] < digits[i]) 
		{
			for (int j = 6; j > i; --j)
			{
				if (digits[i - 1] < digits[j])
				{
					int temp = digits[i - 1];
					digits[i - 1] = digits[j];
					digits[j] = temp;
					return digits;
				}
			}
		}
	}
	return digits;
}

int FindPandigital(const vector<int>& prime) 
{
	array<int, 7> digits = { 7, 6, 5, 4, 3, 2, 1 };
	retry:
	while (prev_permutation(digits.begin(), digits.end()))
	{
		int permuNum = 0;
		for (int i = 0; i < 7; ++i)
		{
			permuNum += digits[i] * (int)pow(10, 6 - i);
		}	
		for (auto& a : prime) 
		{
			if (permuNum % a == 0)
			{
				goto retry;
			}			
		}
		return permuNum;
	}
	return 0;
}


int main()
{
	auto startTime = chrono::system_clock::now();

	int primeLimit = (int)sqrt(7654321) + 1;
	vector<int> primeNumber = {};
	vector<int>& prime = primeNumber;
	PrimeNumber(primeLimit, prime);
	cout << FindPandigital(prime) << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
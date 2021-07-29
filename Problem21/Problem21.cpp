#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

// We can store every single one in a container and check index. Is it possible to do it in the graph way?
void PrimeNumberV3(int upperLimit, vector<int>& prime)
{
	bool isPrime = true;
	int checkLimit = (int)sqrt(upperLimit) + 1;
	for (int i = 2; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			while (a <= checkLimit)
			{
				if (i % a == 0)
				{
					isPrime = false;
				}
			}
		}
		if (isPrime)
			prime.push_back(i);
	}
}

vector<int> Divisors(int num)
{
	int checkLimit = (int)sqrt(num) + 1;
	int divisorNum = 1;
	vector<int> divisors = {1};
	for (int a = 2; a <= checkLimit; ++a)
	{
		if (num % a == 0) 
		{
			divisors.push_back(a);

			if ((int)(num / a) != a)
				divisors.push_back((int)(num / a));
		}
	}
	return divisors;
}

vector<int> DivisorSum()
{
	vector<int> sumList = {};
	int sum = 0;
	for (int num = 1; num < 10000; ++num)
	{
		sum = 0;
		for (auto& a : Divisors(num))
		{
			sum += a;
		}
		sumList.push_back(sum);
//		cout << sum << "\n";
	}
	return sumList;
}

void AmicableSum(vector<int> divisorSum) 
{
	int amicableSum = 0;
	for (int num = 1; num < 10000; ++num)
	{
		int num1 = divisorSum[num - 1];
		int num2 = 0;
		if (num1 < 10000)
		{
			num2 = divisorSum[num1 - 1];
		}
		if (num2 == num && num1 != num2) 
		{
			amicableSum += (num1 + num2);
		}

	}
	cout << amicableSum / 2 << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	AmicableSum(DivisorSum()); 
//	cout << DivisorSum()[219] << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
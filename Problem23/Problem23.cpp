#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

// This is shamefully slow and need to fix
vector<int> Divisors(int num)
{
	int checkLimit = (int)sqrt(num); // don't get over the boundary because 2 and 6 will be counted wrongly
	int divisorNum = 1;
	vector<int> divisors = { 1 };
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

// If still use search, maybe change it into a set?
vector<int> AboundantList()
{
	vector<int> numList = {};
	int sum = 0;
	for (int num = 12; num <= 28123 - 12; ++num)
	{
		sum = 0;
		for (auto& a : Divisors(num))
		{
			sum += a;
		}
		if (sum > num)
		{
			numList.push_back(num);
		}
	}
	return numList;
}

// Check if a number is aboundant is faster than searching in a big container.
bool CheckAboundant(int num)
{
	int sum = 0;
	bool isAboundant = false;
	for (auto& a : Divisors(num))
	{
		sum += a;
	}
	if (sum > num)
		isAboundant = true;
	return isAboundant;
}

void AboundantSum(const vector<int>& aboundant)
{
	int nonAboundantSum = 0;
	bool isAboundantSum = false;
	for (int num0 = 1; num0 < 24; ++num0) 
	{
		nonAboundantSum += num0;
	}
	for (int num = 28123; num >= 25; --num)
	{
		isAboundantSum = false;
		for (auto& a : aboundant)
		{
			if ((num / 2 - a +1) > 0 && CheckAboundant(num - a))
			{
				isAboundantSum = true;
				break;
			}
			else if ((num / 2 - a + 1) <= 0)
			{
				break;
			}
		}
		if (!isAboundantSum) 
		{
			nonAboundantSum += num;
		}
	}
	cout << nonAboundantSum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<int> aboundantList = AboundantList();
	vector<int>& aboundant = aboundantList;
	AboundantSum(aboundant);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <chrono>
using namespace std;

string SingleDigitMultiply(string multiplier, int digit, bool& isDigit)
{
	int additionalPrev = 0;
	int additionalNext = 0;
	isDigit = false;
	string multiplier2 = "";
	for (int i = 0; i < multiplier.size(); ++i)
	{
		additionalPrev = additionalNext;
		int index = multiplier.size() - 1 - i;
		int newDigit = ((multiplier[index]-'0') * digit + additionalPrev) % 10;
		additionalNext = ((multiplier[index] - '0') * digit + additionalPrev) / 10;
		multiplier2 = to_string(newDigit) + multiplier2;
	}
	if (additionalNext != 0)
	{
		multiplier2 = to_string(additionalNext) + multiplier2;
		isDigit = true;
	}
	cout << multiplier2 << "\n";
	return multiplier2;
}

// 10^n has n+1 digits, so base choose from 1-9
void CheckSameDigit() 
{
	int num = 0;
	string numString = "";
	bool isSameDigit = true;
	bool& isDigit = isSameDigit;
	for (int i = 1; i <= 9; ++i) 
	{
		numString = to_string(i);
		isSameDigit = true;
		while (isSameDigit)
		{
			numString = SingleDigitMultiply(numString, i, isDigit);
			++num;
		}
	}
	cout << num << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckSameDigit();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
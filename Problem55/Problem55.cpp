#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include <chrono>
using namespace std;

// Can I know if it's palindrome here in generation?

// iterator of string points to char, need to convert
array<string, 2> BigIntSum(string num1, string num2)
{
	string sumResult = "";
	string palindromeResult = "";
	
	auto itr1 = num1.crbegin();
	auto itr2 = num2.crbegin();
	int additional = 0;
	while (itr1 != num1.crend() && itr2 != num2.crend())
	{
		int newDigit = (((*itr1) - '0') + ((*itr2) - '0') + additional) % 10;
		sumResult = to_string(newDigit)+ sumResult;
		palindromeResult = palindromeResult + to_string(newDigit);
		additional = (((*itr1) - '0') + ((*itr2) - '0') + additional) / 10;
		++itr1;
		++itr2;
	}
	// must be the same length
/*	while (itr1 != num1.crend() && itr2 == num2.crend())
	{
		int newDigit = (*itr1 + additional) % 10;
		sumResult = to_string(newDigit) + sumResult;
		additional = (*itr1 + additional) / 10;
		++itr1;
	}
	while (itr1 == num1.crend() && itr2 != num2.crend())
	{
		int newDigit = (*itr2 + additional) % 10;
		sumResult = to_string(newDigit) + sumResult;
		additional = (*itr2 + additional) / 10;
		++itr2;
	} */
	if (additional != 0)
	{
		sumResult = to_string(additional) + sumResult;
		palindromeResult = palindromeResult + to_string(additional) ;
	}
	array<string, 2> results = {sumResult, palindromeResult};
	return results;
}

void LychrelCheck() 
{
	int lychrelNum = 0;
	bool isLychrel = true;
	for (int i = 1; i < 10000; ++i) 
	{
		isLychrel = true;
		string numString = to_string(i);
		int times = 0; 
		string palindrome = string(numString.rbegin(), numString.rend());
		while (times < 50) 
		{
			array<string, 2> temp = BigIntSum(numString, palindrome);
			numString = temp[0];
			palindrome = temp[1];
//			cout << numString << "\n";
			if (numString == palindrome)
			{
				isLychrel = false;
				break;
			}
			++times;
		}
		if (isLychrel)
			++lychrelNum;
	}
	cout << lychrelNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	LychrelCheck();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
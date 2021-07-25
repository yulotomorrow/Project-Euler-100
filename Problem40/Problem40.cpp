#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <chrono>
using namespace std;

// There are 9*10^(n-1) ones for n digit numbers, find the range then find the digit. 
void FindDigits() 
{
	int multiplier = 1;
	int digit = 1;
	int digitSum = 0;
	array<int, 7> rangeList;
	for (int i = 0; i < 7; ++i) 
	{
		digitSum += 9 * pow(10, (i - 1)) * i;
		rangeList[i] = digitSum;
	}
	for (int i = 1; i < 7; ++i)
	{
		int index = pow(10, (i - 1));
		// j for digit number
		for (int j = 1; j < 7; ++j) 
		{
			if (index > rangeList[j - 1] && index <= rangeList[j]) 
			{
				int num = (index - rangeList[j - 1]) / j + pow(10, (j - 1)) - 1;
				int x = (index - rangeList[j - 1]) % j;
				if (x > 0) 
				{
					++num;
					string temp = to_string(num);
					digit *= temp[x - 1] -'0';
				}
				else 
				{
					digit *= num % 10;
				}
			}
		}
	}
	cout << digit << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindDigits();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;

deque<int> BigIntSum(deque<int> num1, deque<int> num2)
{
	deque<int> sumResult = {};
	auto itr1 = num1.crbegin();
	auto itr2 = num2.crbegin();
	int additional = 0;
	while (itr1 != num1.crend() && itr2 != num2.crend())
	{
		int newDigit = (*itr1 + *itr2 + additional) % 10;
		sumResult.push_front(newDigit);
		additional = (*itr1 + *itr2 + additional) / 10;
		++itr1;
		++itr2;
	}
	while (itr1 != num1.crend() && itr2 == num2.crend())
	{
		int newDigit = (*itr1 + additional) % 10;
		sumResult.push_front(newDigit);
		additional = (*itr1 + additional) / 10;
		++itr1;
	}
	while (itr1 == num1.crend() && itr2 != num2.crend())
	{
		int newDigit = (*itr2 + additional) % 10;
		sumResult.push_front(newDigit);
		additional = (*itr2 + additional) / 10;
		++itr2;
	}
	if (additional != 0)
		sumResult.push_front(additional);
	return sumResult;
}

deque<int> SingleDigitMultiplyNew(deque<int> multiplier, int digit)
{
	deque<int> multiplyResult = {};
	auto itr = multiplier.crbegin();
	int additional = 0;
	while (itr != multiplier.crend())
	{
		int newDigit = (*itr * digit) % 10;
		multiplyResult.push_front(newDigit + additional);
		additional = (*itr * digit) / 10;
		++itr;
	}
	if (additional != 0)
		multiplyResult.push_front(additional);
	return multiplyResult;
}

deque<int> GeneralMultiply(deque<int> multiplier1, deque<int> multiplier2)
{
	auto itr = multiplier2.crbegin();
	deque<int> multiplyResult = {};
	int digitPos = 0;
	while (itr != multiplier2.crend())
	{
		deque<int> nextDigitMulti = SingleDigitMultiplyNew(multiplier1, *itr);
		if (digitPos > 0)
		{
			for (int i = 0; i < digitPos; ++i)
			{
				nextDigitMulti.push_back(0);
			}
		}
		deque<int> tempList = BigIntSum(nextDigitMulti, multiplyResult);
		multiplyResult.assign(tempList.begin(), tempList.end());
		++digitPos;
		++itr;
	}
	return multiplyResult;
}

deque<int> IntToContainer(int num)
{
	deque<int> container = {};
	string storageTemp = to_string(num);
	for (auto& a : storageTemp)
	{
		container.push_back(a - '0');
	}
	return container;
}

void MaxDigitSum() 
{
	int maxSum = 0;
	for (int i = 2; i < 100; ++i) 
	{
		for (int j = 2; j < 100; ++j)
		{
			deque<int> multiplier1 = IntToContainer(i);
			deque<int> multiplier2 = IntToContainer(i);
			int times = j - 1;
			while (times > 0)
			{
				multiplier1 = GeneralMultiply(multiplier1, multiplier2);
				--times;
			}
			int sum = 0;
			for (auto& a : multiplier1)
			{
				sum += a;
			}
			if (sum > maxSum)
			{
				maxSum = sum;
			}
		}
	}
	cout << maxSum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	MaxDigitSum();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
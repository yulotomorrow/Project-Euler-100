#include "BigIntCalculation.h"
#include <iostream>
#include <string>
using namespace std;

void BigIntCalculation::SingleDigitMultiply(deque<int>& multiplier, int digit)
{
	int additionalPrev = 0;
	int additionalNext = 0;
	for (int i = 0; i < multiplier.size(); ++i)
	{
		additionalPrev = additionalNext;
		int index = multiplier.size() - 1 - i;
		int newDigit = (multiplier[index] * digit) % 10;
		additionalNext = (multiplier[index] * digit) / 10;
		multiplier[index] = newDigit + additionalPrev;
	}
	if (additionalNext != 0)
		multiplier.push_front(additionalNext);
}

void BigIntCalculation::DigitSum()
{
	deque<int> multiplier = {};
	multiplier.push_back(2);
	deque<int>& multi = multiplier;
	int sum = 0;
	for (int i = 1; i < 1000; ++i)
	{
		SingleDigitMultiply(multi, 2);
	}

	for (auto& a : multiplier)
		sum += a;
	cout << sum << "\n";
}

// New copy version
deque<int> BigIntCalculation::SingleDigitMultiplyNew(deque<int> multiplier, int digit)
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

deque<int> BigIntCalculation::BigIntSum(deque<int> num1, deque<int> num2)
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

deque<int> BigIntCalculation::GeneralMultiply(deque<int> multiplier1, deque<int> multiplier2)
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

deque<int> BigIntCalculation::IntToContainer(int num)
{
	deque<int> container = {};
	string storageTemp = to_string(num);
	for (auto& a : storageTemp)
	{
		container.push_back(a - '0');
	}
	return container;
}
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;

// Combine Problem 65 and 64, find both series and continuous function.
// This result is very big so have to use string operation again...
// I spent a shameful amount of time on this... :(

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

void PellEquation() 
{
	int maxD = 0;
	deque<int> maxSol = { 0 };
	for (int i = 2; i <= 1000; ++i)
	{
		int a0 = (int)sqrt(i); // leading num
		if (pow(a0, 2) != i) 
		{
			deque<int> numerator = { 1 };
			
			int an = (1.0 / (sqrt(i) - a0));
			int cn = (i - pow(a0, 2));
			int bn = a0 - cn * an;
			deque<int> denominator = IntToContainer(an);
			deque<int> newNumerator = BigIntSum(numerator, GeneralMultiply(denominator, IntToContainer(a0)));

			deque<int> xSquareTerm = GeneralMultiply(newNumerator,	newNumerator);
			deque<int> ySquareTerm = GeneralMultiply(IntToContainer(i),
				GeneralMultiply(denominator, denominator));
			ySquareTerm = BigIntSum(ySquareTerm, IntToContainer(1));
			while (xSquareTerm != ySquareTerm)
			{
				deque<int> temp = denominator;
				an = (cn / (sqrt(i) + (float)bn));
				cn = (i - pow(bn, 2)) / cn;
				bn = -bn - cn * an;
				//denominator = numerator + denominator * an; // new an
				denominator = BigIntSum(numerator, GeneralMultiply(denominator, IntToContainer(an)));
				numerator = temp;
				newNumerator = BigIntSum(numerator, GeneralMultiply(denominator, IntToContainer(a0)));
				xSquareTerm = GeneralMultiply(newNumerator, newNumerator);
				ySquareTerm = GeneralMultiply(IntToContainer(i),
					GeneralMultiply(denominator, denominator));
				ySquareTerm = BigIntSum(ySquareTerm, IntToContainer(1));
			}
			if (newNumerator.size() > maxSol.size() || (newNumerator.size() == maxSol.size() && newNumerator > maxSol))
			{
				maxSol = newNumerator;
				maxD = i;
//				cout << maxD  << "\n";
			}
		}
	}
	cout << maxD << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	PellEquation();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
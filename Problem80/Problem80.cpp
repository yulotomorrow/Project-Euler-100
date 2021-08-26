#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;

// Square root... oh what an interesting topic, there are over 10 algorithms just for this single topic...
// I decide to go with digit by digit method, for two reasons
// 1. the boundary is clear, I don't need to prove convergence, suitable for this problem
// 2. BigInt subtraction is still much better than... urg... division... >_<
// x(20p + x) < c

string SingleDigitMultiply(string multiplier, int digit)
{
	if (digit == 0)
		return "0";
	int additionalPrev = 0;
	int additionalNext = 0;
	string result = multiplier;
	for (int i = 0; i < multiplier.size(); ++i)
	{
		additionalPrev = additionalNext;
		int index = result.size() - 1 - i;
		int newDigit = ((result[index] - '0') * digit + additionalPrev) % 10;
		additionalNext = ((result[index] -'0') * digit + additionalPrev) / 10;
		result[index] = newDigit + '0';
	}
	if (additionalNext != 0)
		result = to_string(additionalNext) + result;
	return result;
}

string PositiveSubtraction(string num1, string num2)
{
	string subtractResult = "";
	auto itr1 = num1.crbegin();
	auto itr2 = num2.crbegin();
	int borrow = 0; // make it 0 or positive
	while (itr1 != num1.crend() && itr2 != num2.crend())
	{
		int newDigit = 0;
		int refVal = ((*itr1 - '0') - (*itr2 - '0') - borrow);
		if (refVal < 0)
		{
			newDigit = refVal + 10;
			borrow = 1;
		}
		else
		{
			newDigit = refVal;
			borrow = 0;
		}
		subtractResult = to_string(newDigit) + subtractResult;
		++itr1;
		++itr2;
	}
	while (itr1 != num1.crend() && itr2 == num2.crend())
	{
		int newDigit = 0;
		int refVal = ((*itr1 - '0') - borrow);
		newDigit = refVal;
		borrow = 0;
		subtractResult = to_string(newDigit) + subtractResult;
		++itr1;
	}
//	if (additional != 0)
//		subtractResult = to_string(additional) + subtractResult;
	auto itr3 = subtractResult.begin();
	if (*itr3 == '0')
	{
		while (*itr3 == '0') 
		{
			++itr3;
		}
		subtractResult.erase(subtractResult.begin(), itr3);
	}	
	return subtractResult;
}

string BigIntSum(string num1, string num2)
{
	string sumResult = "";
	auto itr1 = num1.crbegin();
	auto itr2 = num2.crbegin();
	int additional = 0;
	while (itr1 != num1.crend() && itr2 != num2.crend())
	{
		int newDigit = ((*itr1 - '0') + (*itr2 - '0') + additional) % 10;
		sumResult = to_string(newDigit) + sumResult;
		additional = ((*itr1 - '0') + (*itr2 - '0') + additional) / 10;
		++itr1;
		++itr2;
	}
	while (itr1 != num1.crend() && itr2 == num2.crend())
	{
		int newDigit = ((*itr1 - '0') + additional) % 10;
		sumResult = to_string(newDigit) + sumResult;
		additional = ((*itr1 - '0') + additional) / 10;
		++itr1;
	}
	while (itr1 == num1.crend() && itr2 != num2.crend())
	{
		int newDigit = ((*itr2 - '0') + additional) % 10;
		sumResult = to_string(newDigit) + sumResult;
		additional = ((*itr2 - '0') + additional) / 10;
		++itr2;
	}
	if (additional != 0)
		sumResult = to_string(additional) + sumResult;
	return sumResult;
}

// The result of a single sqrt should be around 450, statistically, because they're irrational

void SquareRootDigit() 
{
	int totalDigitSum = 0;
	for (int i = 2; i < 100; ++i)
	{
		int initialVal = (int)sqrt(i);
		if (i != pow(initialVal, 2))
		{
			string pString = to_string(initialVal);
			int newDigit = initialVal;
			string cStr = to_string(i - (int)pow(initialVal, 2));
			string factorStr = "20";
			for (int j = 1; j < 100; ++j) 
			{
				string fac = SingleDigitMultiply((pString + "0"), 2);
				cStr += "00";
				bool trial = true;
				int k = -1;
				while (trial && k < 10) 
				{
					++k;
					string compare = SingleDigitMultiply(BigIntSum(fac, to_string(k)), k);
					if (cStr.size() > compare.size() || (cStr.size() == compare.size() && cStr > compare))
						trial = true;
					else
						trial = false;					
				}
				string compare = SingleDigitMultiply(BigIntSum(fac, to_string(k-1)), k-1);
				cStr = PositiveSubtraction(cStr, compare);
				newDigit = k - 1;
				pString += to_string(newDigit);
			}
			int digitSum = 0;
			for (auto & dig : pString)
			{
				digitSum += (dig - '0');
			}
//			digitSum -= initialVal;
			totalDigitSum += digitSum;
		}
	}
	cout << totalDigitSum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	SquareRootDigit();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
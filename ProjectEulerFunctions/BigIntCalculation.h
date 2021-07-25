#pragma once
#include <deque>
class BigIntCalculation
{
public:
	void SingleDigitMultiply(std::deque<int>& multiplier, int digit);
	void DigitSum();
	std::deque<int> SingleDigitMultiplyNew(std::deque<int> multiplier, int digit);
	std::deque<int> BigIntSum(std::deque<int> num1, std::deque<int> num2);
	std::deque<int> GeneralMultiply(std::deque<int> multiplier1, std::deque<int> multiplier2);
	std::deque<int> IntToContainer(int num);
};


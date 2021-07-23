#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>
#include <chrono>
using namespace std;

array<int, 10> DigitFifthOrder()
{
	array<int, 10> digitFifthOrder = {};
	digitFifthOrder[0] = 0;
	int order5 = 1;
	for (int i = 1; i <= 9; ++i)
	{
		order5 = pow(i, 5);
		digitFifthOrder[i] = order5;
		cout << order5 << "\n";
	}
	return digitFifthOrder;
}

// digits: 3-6, base on factorial results
void CheckFifthOrder(array<int, 10> digitFifthOrder)
{
	int digitNum = 6;
	int order5Sum = 0;
	int sum = 0;
	vector<int> curious = {};
	for (int a = 10; a < 1000000; ++a)
	{
		int num = a;
		order5Sum = 0;
		for (int i = digitNum; i > 0; --i) 
		{
			order5Sum += digitFifthOrder[num / (int)pow(10, i - 1)];
			num = num % (int)pow(10, i - 1);
		}
		if (order5Sum == a) 
		{
			curious.push_back(a);
		}
	}
	for (auto& b : curious) 
	{
		sum += b;
	}
	cout << sum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	array<int, 10> fifthOrder = DigitFifthOrder();
	CheckFifthOrder(fifthOrder);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
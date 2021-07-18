#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <deque>
#include <chrono>
using namespace std;

void ReadInput() 
{
	fstream fs;
	fs.open("Input_11.txt");

	fs.close();
}

long long FindProduct(string inputNum)
{
	int i = 0;
	long long tempProduct = 1;
	long long maxProduct = 0;
	deque<int> fourNums = {};
	for (auto& num : inputNum)
	{
		//i = stoi();
		fourNums.push_back(i);
		fourNums.pop_front();

		tempProduct = 1;
		for (auto& tempDigit : fourNums)
		{
			tempProduct *= tempDigit;
		}
		if (tempProduct > maxProduct)
		{
			maxProduct = tempProduct;
		}
	}
	return maxProduct;
}

void RowSearch() 
{
}

void ColumnSearch()
{
}

void PlusDiagSearch()
{
}

void MinusDiagSearch()
{
}

int main()
{
	auto startTime = chrono::system_clock::now();

	array<array<int, 20>, 20> inputArray;

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

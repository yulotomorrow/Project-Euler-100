#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <deque>
#include <chrono>
using namespace std;

void InputProcess(string line, int lineNum, array<array<int, 20>, 20>& input)
{
	string num = "";
	int columnNum = 0;
	for (auto& chara : line) 
	{
		if (chara != ' ')
		{
			num += chara;
		}
		else 
		{
			input[lineNum][columnNum] = stoi(num);
			cout << input[lineNum][columnNum]<<" ";
			num = "";
			++columnNum;
		}
	}
	input[lineNum][columnNum] = stoi(num);
	cout << input[lineNum][columnNum];
}

void ReadInput(array<array<int, 20>, 20>& input)
{
	fstream fs;
	fs.open("Input_11.txt");
	string line;
	int lineNum = 0;
	while (getline(fs, line)) 
	{
		InputProcess(line, lineNum, input);
		cout << "\n";
		++lineNum;
	}
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

//Not satisfied with O(n^2), is there a better way?
int RowSearch(const array<array<int, 20>, 20>& input)
{
	int product = 1;
	int maxProduct = 1;
	for (int row = 0; row < 20; ++row) 
	{
		for (int column = 0; column < 17; ++column) 
		{
			product = input[row][column] * input[row ][column + 1] * input[row ][column + 2] * input[row][column + 3];
		}
		if (product > maxProduct)
			maxProduct = product;
	}

	return maxProduct;
}

int ColumnSearch(const array<array<int, 20>, 20>& input)
{
	int product = 1;
	int maxProduct = 1;
	for (int column = 0; column < 20; ++column)
	{
		for (int row = 0; row < 17; ++row)
		{
			product = input[row][column] * input[row + 1][column] * input[row + 2][column] * input[row + 3][column];
		}	
		if (product > maxProduct)
			maxProduct = product;
	}

	return maxProduct;
}

int PlusDiagSearch(const array<array<int, 20>, 20>& input)
{
	int product = 1;
	int maxProduct = 1;
	for (int row = 3; row < 20; ++row)
	{
		for (int column = 0; column < 17; ++column)
		{
			product = input[row][column]* input[row - 1][column + 1] * input[row - 2][column + 2] * input[row -3][column + 3];
		}
		if (product > maxProduct)
			maxProduct = product;
	}

	return maxProduct;
}

int MinusDiagSearch(const array<array<int, 20>, 20>& input)
{
	int product = 1;
	int maxProduct = 1;
	for (int row = 0; row < 17; ++row)
	{
		for (int column = 0; column < 17; ++column)
		{
			product = input[row][column] * input[row + 1][column + 1] * input[row + 2][column + 2] * input[row + 3][column + 3];
		}
		if (product > maxProduct)
			maxProduct = product;
	}
	return maxProduct;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	array<array<int, 20>, 20> inputArray = {0};
	array<array<int, 20>, 20>& input = inputArray;
	ReadInput(input);
	cout << RowSearch(input) << "\n";
	cout << ColumnSearch(input) << "\n";
	cout << MinusDiagSearch(input) << "\n";
	cout << PlusDiagSearch(input) << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

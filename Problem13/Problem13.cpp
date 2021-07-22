#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <deque>
#include <chrono>
using namespace std;

//Lazy way: take first 10 (11?) digits and add them, digits further than this doesn't matter
//Rigorously take more digits, when stable don't need to keep doing
void InputProcess(string line, int lineNum, array<long long, 100>& input)
{
	string num = "";
	int columnNum = 0;
	for (int i =0; i <=10; ++i)
	{
		num += line[i];
		cout << num << " ";
		input[lineNum]= stoll(num);
	}
}

void ReadInput(array<long long, 100>& input)
{
	fstream fs;
	fs.open("Input_13.txt");
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

// Way to do more digits, change it into same length version
deque<int> BigIntSum100(deque<int> num1, deque<int> num2)
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

int main()
{
	auto startTime = chrono::system_clock::now();
	array<long long, 100> inputNum = {};
	array<long long, 100>& input = inputNum;

	ReadInput(input);
	long long sum = 0;
	for (auto& a : inputNum) 
	{
		sum += a;
	}
	cout << sum << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
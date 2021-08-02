#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <chrono>
using namespace std;

string DecToBinary(int num) 
{
	string binary = "";
	while (num != 0) 
	{
		binary = to_string(num % 2) + binary;
		num /= 2;
	}
	return binary;
}

void CheckPalindrome() 
{
	int sum = 0;
	for (int i = 1; i < 1000000; i += 2) 
	{
		string numDec = to_string(i);
		// Bitset contains leading zeros
		//string numBinary = bitset<32>(i).to_string();
		string numBinary = DecToBinary(i);
		if (numDec == string(numDec.rbegin(), numDec.rend()) && numBinary == string(numBinary.rbegin(), numBinary.rend()))
			sum += i;
	}
	cout << sum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckPalindrome();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
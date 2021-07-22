#include <iostream>
#include <fstream>
#include <array>
#include <chrono>
using namespace std;

array<int, 10> DigitFactorial() 
{
	array<int, 10> digitFactorial = {};
	digitFactorial[0] = 1;
	int factorio = 1;
	for (int i = 1; i <= 9; ++i) 
	{
		factorio *= i;
		digitFactorial[i] = factorio;
		cout << factorio << "\n";
	}
	return digitFactorial;
}



int main()
{
	auto startTime = chrono::system_clock::now();

	array<int, 10> factorio = DigitFactorial();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
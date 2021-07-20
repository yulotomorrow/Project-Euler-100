#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

// this one is BORING even reading from string won't make it interesting :(
void Summation(vector<int> zeroToNineteen, vector<int> tens, int hundred, int thousand)
{
	int total = 0;
	int underHundred = 0;
	int zeroToNine = 0;
	int tenthZeroToNine = 0;
	for (int i = 0; i < 10; ++i) 
	{
		zeroToNine += zeroToNineteen[i];
		tenthZeroToNine += tens[i];
	}
	for (int i = 0; i < 20; ++i)
	{
		underHundred += zeroToNineteen[i];
	}
	underHundred += (tenthZeroToNine * 10 + zeroToNine * 8);
	total = underHundred * 10 + hundred * (900) - 9 * 3 + zeroToNine * 100 + thousand;
	cout << total << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	//hard coded character numbers
	vector<int> zeroToNineteen = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
	vector<int> tens = { 0, 0, 6, 6, 5, 5, 5, 7, 6, 6 };
	int hundred = 10;
	int thousand = 11;
	Summation(zeroToNineteen, tens, hundred, thousand);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

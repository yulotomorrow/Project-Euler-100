#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
using namespace std;

// I want to do it by hand but... well, let's do it backtrack way.
// 10 must be in outer circle, and the min number be the max, so 6, 7, 8, 9, 10 outside

void Gong5Chain() 
{
	int lineSum = (6 + 7 + 8 + 9 + 10 + 2 * (1 + 2 + 3 + 4 + 5)) / 5;
	array<array<int, 3>, 5> filling = {0};
	filling[0][0] = 6;
	filling[1][0] = 7;
	filling[2][0] = 8;
	filling[3][0] = 9;
	filling[4][0] = 10;
	for (int i = 0; i < 5; ++i) 
	{

	}

}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
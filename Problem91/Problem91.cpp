#include <iostream>
#include <string>
#include <array>
#include <set>
#include <deque>
#include <chrono>
using namespace std;

// The number of right triangle with right angle rely on grids is 50*50(possible coord combination)*3(original, x reflection, y reflection)
// So just find right angle inside the grid.

array<int, 2> ReduceFraction(int a, int b)
{
	int count = 0;
	int aCopy = a;
	int bCopy = b;
	while (a % b != 0)
	{
		int temp = b;
		b = a % b;
		a = temp;
		++count;
	}
	return { aCopy / b, bCopy / b };
}

void RightAngles() 
{
	int grid = 50;
	int rightAngles = grid * grid * 3;
	for (int x = 1; x <= grid; ++x)
	{
		for (int y = 1; y <= grid; ++y)
		{
			array<int, 2> reducePair = ReduceFraction(x, y);
			int a = reducePair[0];
			int b = reducePair[1];
			rightAngles += ((grid - x) / b) < (y / a) ? ((grid - x) / b) : (y / a);
			rightAngles += ((grid - y) / a) < (x / b) ? ((grid - y) / a) : (x / b);
		}
	}
	cout << rightAngles << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	RightAngles();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
using namespace std;

// I want to do it by hand but... well, let's do it backtrack way.
// 10 must be in outer circle, and the min number be the max, so 6, 7, 8, 9, 10 outside

bool CanFill(array<array<int, 3>, 5>& filling, int fillPos, int fillNum) 
{
	int fillPlace2 = 14 - filling[fillPos][0] - fillNum;
	if (fillPlace2 == fillNum)
		return false;
	for (int i = 0; i < fillPos; ++i)
	{
		if (filling[i][1] == fillNum || filling[i][2] == fillPlace2)
			return false;
	}
	return true;
}

bool BacktrackFilling(array<array<int, 3>, 5>& filling, int fillPos)
{
	for (int i = 5; i >= 1; --i) 
	{	
		if (CanFill(filling, fillPos, i))
		{
			filling[fillPos][1] = i;
			filling[fillPos][2] = 14 - filling[fillPos][0] - i;

			if (fillPos >= 4)
				return true;
			else if (BacktrackFilling(filling, fillPos + 1))
			{
				return true;
			}
		}
	}
	filling[fillPos][1] = 0;
	filling[fillPos][2] = 0;
	return false;
}

void RearrangedOutput(array<array<int, 3>, 5>& filling)
{
	int index = 0;
	do
	{
		for (auto& b : filling[index])
			cout << b;
		for (int i2 = 0; i2 < 5; ++i2) 
		{
			if (filling[i2][1] == filling[index][2]) 
			{
				index = i2;
				break;
			}
		}
	} while (index !=  0);
	return;
}

void Gong5Chain() 
{
	int lineSum = (6 + 7 + 8 + 9 + 10 + 2 * (1 + 2 + 3 + 4 + 5)) / 5;
	array<array<int, 3>, 5> fillingList = {0};
	array<array<int, 3>, 5>& filling = fillingList;
	filling[0][0] = 6;
	filling[1][0] = 7;
	filling[2][0] = 8;
	filling[3][0] = 9;
	filling[4][0] = 10;

	if (BacktrackFilling(filling, 0))
	{
		RearrangedOutput(filling);
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	Gong5Chain();
	cout << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
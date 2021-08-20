#include <iostream>
#include <set>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// We need to prove two things here, to change this problem to a find primitive integer right triangle problem
// 1. the "half triangle" is integer right triangle. Because we want 2a, c to be integer, as well as a * b to be integer.
// At least b has to be integer and a is half integer. But if a is not an integer there's no way c can be integer.
// a and b cannot both be fraction, for instance, the result calculating c denominator cannot be eliminate.
// so we need to find integer right triangle.
// 2. it's fully reduced triagle, since 2a - c must be integer and must be +- 1
// there's no reduced factor. so it's primitive.

bool IsCoprime(int a, int b) 
{
	while (a % b != 0) 
	{
		int temp = b;
		b = a - b * (a / b);
		a = temp;
	}
	if (b == 1)
		return true;
	else
		return false;
}

void FindPerfectTriGroup()
{
	int solution = 0;
	const int limit = (1e9 + 2) / 3;
	int triBound = (int)sqrt(limit) + 2;
	for (int m = 3; m <= triBound; m += 2)
	{
		for (int n = 1; n < m; n += 2)
		{
			if (IsCoprime(m, n)) 
			{
				int a = m * n;
				int b = (pow(m, 2) - pow(n, 2)) / 2;
				int c = (pow(m, 2) + pow(n, 2)) / 2;
				if (c - 2 * a == 1|| 2 * a - c == 1 )
				{
					solution += c * 2 + a * 2;
				}
				else if (c - 2 * b == 1 || 2 * b - c == 1)
				{
					solution += c * 2 + b * 2;
				}
			}
		}
	}
	cout << solution << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindPerfectTriGroup();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
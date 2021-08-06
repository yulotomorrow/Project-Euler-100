#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <chrono>
using namespace std;

// If answer is within 10000^3, it's still acceptable to brute force, otherwise there must be math method.

void CubicPermutation() 
{
	array<string, 10000> cubicSorted = {};
	long long result = 0;
	for (int i = 0; i < 10000; ++i) 
	{
		long long cube = pow((i + 1), 3);
		string cubeStr = to_string(cube);
		sort(cubeStr.begin(), cubeStr.end());
		cubicSorted[i] = cubeStr;
//		cout << cubeStr << "\n";
	}
	for (int j = 0; j < 10000; ++j)
	{
		int count = 0;
		for (int k = (j + 1); k < 10000; ++k)
		{
			if (cubicSorted[j] == cubicSorted[k])
				++count;
			else if (cubicSorted[j].size() < cubicSorted[k].size())
				break;
		}
		if (count >= 4) 
		{
			result = pow((j + 1), 3);
			break;
		}
	}
	cout << result << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CubicPermutation();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
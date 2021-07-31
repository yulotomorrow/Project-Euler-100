#include <iostream>
#include <map>
#include <chrono>
using namespace std;

// The total number of rectangles of n*m lattice is n(n+1)m(m+1)/4
// 8000000^1/4 = 53.18
void FindCloseToTargetPair() 
{
	const int ref = 8000000;
	const int ref2 = (int)sqrt(ref);

	int pairMultiply = 0;
	int smallestDifference = ref;
	for (int n = 2; n < (int)sqrt(ref2); ++n)
	{
		int m = ref2 / n;
		map<int, int> closePair = {};
		closePair[n * m]=( n * (n + 1) * m * (m + 1));
		closePair[(n-1) * m] = (n * (n - 1) * m * (m + 1));
		closePair[n * (m-1)] = (n * (n + 1) * m * (m - 1));
		closePair[(n-1) * (m-1)] = (n * (n - 1) * m * (m - 1));
		for (auto& a : closePair) 
		{
			// can modify it and store difference directly, or exchange key and value with auto sort
			if (abs(a.second - ref) < smallestDifference) 
			{
				smallestDifference = abs(a.second - ref);
				pairMultiply = a.first;
			}
		}
	}
	cout << pairMultiply << " " << smallestDifference << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindCloseToTargetPair();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
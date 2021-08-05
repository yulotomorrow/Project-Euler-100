#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <chrono>
using namespace std;

// Any geometrical solution for this one?
// difference between two pentagon: p(n) - p(n-1) = 1 + 3 (n - 1)
// p(n) - p(n-k) = k + 3 (2n - 1 - k) * k / 2
// p(n) + p(n-k) = k + 3 (2n - 1 - k) * k / 2 + (n-k) (3n - 3k -1)

// Here used cacheing method, see problem 45 for checking method. 
// Need some evaluation (guess) on the range

void PentagonNumber() 
{
	set<int> pentagons = {};
	int minDifference = 100000000;
	for (int n = 1; n <= 3000; ++n) 
	{
		int pentagon = n * (3 * n - 1) / 2;
		pentagons.insert(pentagon);
	}
	auto itr1 = pentagons.begin();
	auto itr2 = pentagons.begin();
	while (itr1 != pentagons.end()) 
	{
		itr2 = itr1;
		++itr2;
		while (itr2 != pentagons.end())
		{
			int sum = *itr1 + *itr2;
			int diff = *itr2 - *itr1;
			if (pentagons.find(sum) != pentagons.end() && pentagons.find(diff) != pentagons.end() && diff < minDifference)
			{
				minDifference = diff;
			}
			++itr2;
		}
		++itr1;
	}
	cout << minDifference << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	PentagonNumber();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
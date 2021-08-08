#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <chrono>
using namespace std;

// Sorry, number theory can't save you either (unless you can prove the modulation equation)
// Just run and pray the one would be reached quickly (?)
// I'm very unhappy with this two dimention memoization, the recurtion of partition function is 1D...
// Okay so I use partition function recursion relationship and it worked...

void IntegerRecursion()
{
	int max = 100000;
	const int numType = max;
	const int limit = 1e9;
	const int mod = 1e6;
	array<int, 100001> partition = {};
	for (int n = 0; n <= max; ++n)
	{
		if (n == 0 || n == 1)
		{
			partition[n] = 1;
		}
		else 
		{
			int bound = sqrt((n * 2) / 3.0) + 1;
			partition[n] = 0;
			for (int k = -bound; k <= bound; ++k)
			{
				int pentagon = (k * (3 * k - 1)) / 2;
				if (n - pentagon >= 0 && pentagon != 0)
				{
					partition[n] += pow(-1, k + 1) *partition[n - pentagon];
					partition[n] %= limit;
				}
			}
		}
		if (partition[n] % mod == 0)
		{
			cout << n << "\n";
			return;
		}	
	}
}



int main()
{
	auto startTime = chrono::system_clock::now();

	IntegerRecursion();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
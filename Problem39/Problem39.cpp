#include <iostream>
#include <set>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// Use Euclid's fomular, a = m^2-n^2, b = 2mn, c = m^2 + n^2, a+b+c = 2m^2 + 2mn
// k*m*(m+n), 3 divisor, this is again a find divisor problem
// m > n, m(m+1) < 1000

void FindPerfectTriGroup() 
{
	int solutionNum = 0;
	int mostGroup = 0;
	set<int> minimumTri = {};
	const int limit = 1000 / 2;
	int triBound = (int)sqrt(limit) + 2;
	for (int m = 2; m <= triBound; ++m)
	{
		for (int n = 1; n < m; ++n)
		{
			if (minimumTri.find((2 * m * (m + n))) == minimumTri.end()) {
				minimumTri.insert((2 * m * (m + n)));
				cout << (2 * m * (m + n)) << "\n";
			}
		}
	}
	for (int p = 12; p <= 1000; ++p) 
	{
		int solution = 0;
		for (auto& a : minimumTri) 
		{
			if (p % a == 0) 
			{
				++solution;
			}
		}				
		if (solution > solutionNum) 
		{
			solutionNum = solution;
			mostGroup = p;
			cout << mostGroup << " " << solutionNum << "\n";
		}	
	}
	cout << mostGroup << " "<< solutionNum << "\n";
}

void FindSingleTriGroup()
{
	int solutionNum = 0;
	set<int> minimumTri = {};
	const int limit2 = 1500000 / 2;
	int triBound2 = (int)sqrt(limit2) + 2;
	for (int m = 2; m <= triBound2; ++m)
	{
		for (int n = 1; n < m; ++n)
		{
			int element = 2 * m * (m + n);
			bool isSingleGroup = true;
			for (auto& b : minimumTri)
			{
				if (b < round(element / 2) + 1)
				{
					if (element % b == 0)
					{
						isSingleGroup = false;
						break;
					}
				}
				else
					break;
			}
			if (isSingleGroup)
				minimumTri.insert(element);
		}
	}
	cout << minimumTri.size() << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();
	// Problem 39
	FindPerfectTriGroup();
	// Problem 75
//	FindSingleTriGroup();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
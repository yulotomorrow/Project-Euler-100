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

void PrimeNumber(int upperLimit, set<int>& prime)
{
	prime.insert(2);
	prime.insert(3);
	for (int i = 5; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			if (a <= sqrt(i))
			{
				if (i % a == 0)
				{
					goto skip;
				}
			}
			else
				break;
		}
		prime.insert(i);
	skip:
		;
	}
}

bool IsCoprime(int a, int b, const set<int>& prime)
{
	for (auto& p : prime) 
	{
		if (p <= a)
		{
			if (a % p == 0 && b % p == 0)
				return false;
		}
		else 
			break;
	}
	return true;
}

void FindPerfectTriGroup(const set<int>& prime)
{
	int solutionNum = 0;
	int mostGroup = 0;
	set<int> minimumTri = {};
	const int limit = 1000 / 2;
	int triBound = (int)sqrt(limit) + 2;
	for (int m = 3; m <= triBound; m += 2)
	{
		for (int n = 1; n < m; n += 2)
		{
			if (minimumTri.find((m * (m + n))) == minimumTri.end() && IsCoprime(m, n, prime)) {
				minimumTri.insert((m * (m + n)));
				cout << ( m * (m + n)) << "\n";
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
//			cout << mostGroup << " " << solutionNum << "\n";
		}	
	}
	cout << mostGroup << " "<< solutionNum << "\n";
}

void FindPerfectTriGroupV2(const set<int>& prime)
{
	int solutionNum = 0;
	int mostGroup = 0;
	set<int> minimumTri = {};
	const int limit2 = 1500000;
	int triBound = (int)sqrt(limit2) + 2;
	for (int m = 3; m <= triBound; m += 2)
	{
		for (int n = 1; n < m; n += 2)
		{
			if (minimumTri.find((m * (m + n))) == minimumTri.end() && IsCoprime(m, n, prime)) {
				minimumTri.insert((m * (m + n)));
//				cout << (m * (m + n)) << "\n";
			}
		}
	}
	for (int p = 12; p <= limit2; ++p)
	{
		int solution = 0;
		for (auto& a : minimumTri)
		{
			if (p % a == 0)
			{
				++solution;
			}
		}
		if (solution == 1)
		{
			++solutionNum;
			//			cout << mostGroup << " " << solutionNum << "\n";
		}
	}
	cout << solutionNum << "\n";
}

// there are non-minimal but only one way triangle

void FindSingleTriGroup(const set<int>& prime)
{
	int solutionNum = 0;
	set<int> minimumTri = {};
	set<int> notMinimum = {};
	set<int> repeat = {};
	const int limit2 = 1500000;
	int triBound2 = (int)sqrt(limit2) + 2;
	int totalNum = 0;
	for (int m = 3; m <= triBound2; m += 2)
	{
		for (int n = 1; n < m; n += 2)
		{
			if ((m * (m + n)) <= limit2 && IsCoprime(m, n, prime))
			{
				if (minimumTri.find((m * (m + n))) == minimumTri.end())
				{
					minimumTri.insert((m * (m + n)));
//					++totalNum;
					//				cout << (m * (m + n)) << "\n";
				}
				else
					repeat.insert((m * (m + n)));
			}
		}
	}
	for (auto element : minimumTri)
	{
		for (int k = 1; k <= (limit2 / element); ++k)
		{
			int solution = 0;
			for (auto& a : minimumTri)
			{
				if ((k * element ) % a == 0)
				{
					++solution;
				}
			}
			if (solution == 1)
			{
				++solutionNum;
				//			cout << mostGroup << " " << solutionNum << "\n";
			}
		}
	}
//	cout << minimumTri.size() + notMinimum.size() - repeat.size() << "\n";
	cout << solutionNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();
	// Problem 39
	set<int> primeList = {};
	set<int>& prime = primeList;
//	FindPerfectTriGroup(prime);
	// Problem 75
	FindSingleTriGroup(prime);
//	FindPerfectTriGroupV2(prime);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
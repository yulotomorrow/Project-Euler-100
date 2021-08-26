#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;

// Here I am challenging the siad to be hardest problem in 1-100
// It's easy to see only by filling 1s can we reach the same value, so the question is how many 1s.
// Think about it from two aspects:
// One is the boundary of search. The number N must larger than k which is obvious
// And it must be smaller than 2k, at least for even numbers, that the worst case is 1s* 2 * k
// Then think about the lower and upper bound of k for a composite number.
// The smallest k is achieved by 1s*(smallest divisor)*(else)
// The largest k is achieved by 1s * (all minimum divisors)
// The largest k is got from: k = N - (multiply)(minimum divisors - 1)
// So for a given k, can we 1) composite the N; 2)search the N

// ...The problem is, here we need new combinatorics techniques
// Either generate all partition of divisors, or all partition of difference

vector<int> NextPartition(vector<int> partition)
{
	int res = 0;
	vector<int> nextP = partition;
	vector<int> ref = {};
	auto itr = nextP.end() - 1;
	while (*itr == 1 && itr != nextP.begin())
	{
		++res;
		--itr;
	}
	if (*itr != 1)
	{
		--*itr;
		++res;
		int p = *itr;
		nextP.erase(itr + 1, nextP.end());
		if (res <= p)
		{
			nextP.push_back(res);	
		}
		else 
		{
			while (res > p) 
			{
				nextP.push_back(p);
				res -= p;
			}
			nextP.push_back(p);
		}
		return nextP;
	}
	else
		return ref;
}

// You have done partition function in previous problems, yulo, you should know it's a bad idea... 

void FindMinimumPartition() 
{
	set<int> numList = {};
	for (int k = 22; k <= 30; ++k) 
	{
		for (int diff = 2; diff <= k; ++diff) 
		{
			int N = k + diff;
			vector<int> partition = { };
			vector<int> ref = {};
			partition.push_back(diff);
			partition = NextPartition(partition);
			while (partition != ref)
			{
				if (pow(2, diff) < N)
					break;
				int predictProduct = 1;
				for (auto& a : partition) 
				{
					predictProduct *= a + 1;
					if (predictProduct > N)
						break;
				}
				if (predictProduct == N)
				{
					numList.insert(N);
					cout << N << "\n";
					goto find;
				}
				//else if (predictProduct > N)
				//{
				//	break;
				//}
				partition = NextPartition(partition);
			}
		}
	find:
	;
	}
	int sum = 0;
	for (auto& b : numList) 
	{
		sum += b;
	}
	cout << sum << "\n";
}

set<int> FindDivisors(int num) 
{
	set<int> divisors = {};
	for (int i = 2; i <= sqrt(num); ++i)
	{
		if (num % i == 0) 
		{
			divisors.insert(i);
			divisors.insert(num / i);
		}
	}
	return divisors;
}

// Aaah I finally find the needed "get all factor combination" algorithm!!!

void DivisorRecursion(vector<int>& kList, vector<int> kValues, int num, int firstFactor, int accumProd)
{
	if (firstFactor > num || accumProd > num)
		return;
	if (accumProd == num)
	{
		int kVal = 0;
		for (auto& a : kValues)
			kVal += a;
		kList.push_back(kVal);
	}
	for (int i = firstFactor; i < num; ++i)
	{
		if (i * accumProd > num)
			break;
		if (num % i == 0)
		{
			kValues.push_back(i - 1);
			DivisorRecursion(kList, kValues, num, i, i * accumProd);
			kValues.pop_back();
		}		
	}
}

int DivisorRecursionV2(vector<int> kValues, int num, int firstFactor, int accumProd)
{
	if (firstFactor > num || accumProd > num)
		return 1;
	if (accumProd == 1)
		return 1;
	int kVal = 1;
	for (int i = firstFactor; i < num; ++i)
	{
		if (i * accumProd > num)
			break;
		if (num % i == 0)
		{
			kVal = (i - 1) * DivisorRecursionV2(kValues, num, i, i * accumProd);
		}
	}
	if (accumProd == num)
	{
		kValues.push_back(1);
		
	}
	return kVal;
}

void FindMinimumDivisor()
{
	set<int> numList = {};
	int bound = 12000;
	array<int, 12000 -1> numListInPlace = {1e6};
	array<int, 12000 - 1>& numL = numListInPlace;
	for (int n = 24000; n>=4; --n)
	{
		vector<int> kValList = {};
		vector<int>& kList = kValList;
		vector<int> kValues = {};
		DivisorRecursion(kList, kValues, n, 2, 1);
		for (auto& kVal : kValList) 
		{
			int k = n - kVal;
			if (k <= 12000)
				numListInPlace[k - 2] = n;
		}
	}
	set<int> divisorList = {};
	int sum = 0;
	for (auto& b : numListInPlace)
	{
		divisorList.insert(b);
	}
	for (auto& c : divisorList)
	{
		sum += c;
	}
	cout << sum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

//	FindMinimumPartition();
	FindMinimumDivisor();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
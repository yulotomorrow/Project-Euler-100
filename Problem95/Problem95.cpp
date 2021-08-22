#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;

int ProperDivisorSum(int n) 
{
	if (n == 1)
		return 1;
	int sum = 1;
	for (int i =2; i < sqrt(n); ++i) 
	{
		if (n % i == 0) 
		{
			sum += i;
			sum += n / i;
		}
	}
	if (n == pow((int)sqrt(n), 2))
		sum += sqrt(n);
	return sum;
}

void MaxAmicableChain() 
{
	unordered_set<int> visited = {};
	vector<int> chain = {};
	int maxLength = 0;
	int smallElement = 0;
	for (int i = 1; i < 1e6; ++i) 
	{
		chain = {};
		if (visited.find(i) == visited.end())
		{
			int num = i;
			while (find(chain.begin(), chain.end(), num) == chain.end())
			{
				chain.push_back(num);
				num = ProperDivisorSum(num);
				if (num >= 1e6)
					goto skip;
			}
			auto itr = find(chain.begin(), chain.end(), num);
			int chainLength = chain.end() - itr;
			if (maxLength < chainLength)
			{
				maxLength = chainLength;
				smallElement = *min_element(itr, chain.end());
			}
			visited.insert(chain.begin(), chain.end());
		}
	skip:
		;
	}
	cout << smallElement << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	MaxAmicableChain();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
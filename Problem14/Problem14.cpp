#include <iostream>
#include <set>
#include <chrono>
using namespace std;

// Don't know if reversing this process and build a tree works?

void CollatzSeries() 
{
	int maxChain = 0;
	int maxChainPos = 1;
	for (int i = 1; i <= 1000000; ++i) 
	{
		long long chainLength = 1;
		long long num = i;
		while (num != 1) 
		{
			num = (num % 2 == 0) ? (num / 2) : (3 * num + 1);
			chainLength += 1;
		}
		if (chainLength > maxChain)
		{
			maxChain = chainLength;
			maxChainPos = i;
		}
	}
	cout << maxChainPos << "\n";
}

// A possible improvement, start from largest, and if encounter, skip checking this number 
// conclusion: maybe not, the cost of building a 1 million set is too large >_<
void CollatzSeriesV2()
{
	cout << "start" << "\n";
	int maxChain = 0;
	int maxChainPos = 1;
	set<int> skipList = {};
	auto itr = skipList.begin();
	for (int i = 1000000; i > 1; --i)
	{
		itr = skipList.find(i);
		if (itr != skipList.end()) 
		{
			skipList.erase(itr);
		}
		else
		{
			long long chainLength = 1;
			long long num = i;
			while (num != 1)
			{
				num = (num % 2 == 0) ? (num / 2) : (3 * num + 1);
				if (num < 1000000 && skipList.find(num) == skipList.end()) 
				{
					skipList.emplace(num);
					cout << num << "\n";
				}
					
				chainLength += 1;
			}
			if (chainLength > maxChain)
			{
				maxChain = chainLength;
				maxChainPos = i;
			}
		}
	}
	cout << maxChainPos << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CollatzSeries();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
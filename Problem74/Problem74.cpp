#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int FactorialDigitGenerate(map<char, int>& factorialMap, int n) 
{
	if (n == 0)
	{
		factorialMap['0'] = 1;
		return 1;
	}
	char digit = n + '0';
	factorialMap[digit] = n * FactorialDigitGenerate(factorialMap, n - 1);
	return factorialMap[digit];
}

// Definetely not the best solution.
// First, generate a new list storing previous number and check if appear, then I don't need to set the limit at 57.
// Second, generate all possible digit factorial result number, this either needs some combinatorics or still go over the whole list,
// so I didn't use it.
// Third, find the leading number with this chain length and regenerate laa possible combinations, 
// but can't make sure there's only one such chain.
// Well, going over all possibilities is still the safest...

void LengthBeforeCycle(set<int> cycleEnd, const map<char, int>& factorialMap)
{
	int chainNum = 0;
	for (int i = 3; i < 1e6; ++i) 
	{
		int unrepeatLength = 0;
		long long num = i;
		while (cycleEnd.find(num) == cycleEnd.end())
		{
			string numStr = to_string(num);
			num = 0;
			for (auto& a : numStr) 
			{
				num += factorialMap.find(a)->second;
			}
			++unrepeatLength;
		}
		if (unrepeatLength >= 57 && (num == 169 || num == 363601 || num == 1454)) 
		{
			++chainNum;
		}
	}
	cout << chainNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	map<char, int> fMap = {};
	map<char, int>& factorialMap = fMap;
	set<int> cycleEnd = {};
	// Sorry for this I should have written another function to wrap it up >_<
	cycleEnd.insert(145);
	cycleEnd.insert(40585);
	cycleEnd.insert(1);
	cycleEnd.insert(2);
	cycleEnd.insert(169);
	cycleEnd.insert(1454);
	cycleEnd.insert(363601);
	cycleEnd.insert(871);
	cycleEnd.insert(872);
	cycleEnd.insert(45361);
	cycleEnd.insert(45362);
	FactorialDigitGenerate(factorialMap, 9);
	LengthBeforeCycle(cycleEnd, factorialMap);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

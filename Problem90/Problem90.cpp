#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;

// C(10, 6) is just 210, so we can brute force it (wait?!

array<int, 6> NextCombinationC10_6(array<int, 6> combination)
{
	array<int, 10> baseArray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto itr1 = combination.rbegin();
	auto itr2 = baseArray.rbegin();
	for (int i = 5; i >= 0; --i) 
	{
		if (*itr1 != *itr2) 
		{
			int temp = *itr1;
			for (int j = 0; j <= 5 - i; ++j) 
			{
				combination[j + i] = temp + j + 1;
			}
			break;
		}
		++itr1;
		++itr2;
		if (itr1 == combination.rend())
			return {0, 0, 0, 0, 0, 0};
	}
	return combination;
}

bool IsCubePair(array<int, 6> c1, array<int, 6> c2)
{
	for (int i = 0; i < 9; ++i)
	{
		int digit1 = (int)pow((i + 1), 2) / 10;
		int digit2 = (int)pow(i + 1, 2) % 10;
		if (digit1 != 6 && digit1 != 9 && digit2 != 6 && digit2 != 9) 
		{
			bool cond1 = (find(c1.begin(), c1.end(), digit1) != c1.end() && find(c2.begin(), c2.end(), digit2) != c2.end());
			bool cond2 = (find(c1.begin(), c1.end(), digit2) != c1.end() && find(c2.begin(), c2.end(), digit1) != c2.end());
			if (!(cond1 || cond2))
			{
				return false;
			}
		}
		else if(digit1 == 6 || digit1 == 9) 
		{
			bool cond1 = ((find(c1.begin(), c1.end(), 6) != c1.end() || find(c1.begin(), c1.end(), 9) != c1.end())
				&& find(c2.begin(), c2.end(), digit2) != c2.end());
			bool cond2 = (find(c1.begin(), c1.end(), digit2) != c1.end() && 
				(find(c2.begin(), c2.end(), 6) != c2.end() || find(c2.begin(), c2.end(), 9) != c2.end()));
			if (!(cond1 || cond2))
			{
				return false;
			}
		}
		else if (digit2 == 6 || digit2 == 9)
		{
			bool cond1 = ((find(c1.begin(), c1.end(), 6) != c1.end() || find(c1.begin(), c1.end(), 9) != c1.end())
				&& find(c2.begin(), c2.end(), digit1) != c2.end());
			bool cond2 = (find(c1.begin(), c1.end(), digit1) != c1.end() &&
				(find(c2.begin(), c2.end(), 6) != c2.end() || find(c2.begin(), c2.end(), 9) != c2.end()));
			if (!(cond1 || cond2))
			{
				return false;
			}
		}
	}
	return true;
}

void FindCubePair() 
{
	array<int, 6> initialComb = {0, 1, 2, 3, 4, 5};
	array<int, 6> comb1 = initialComb;
	array<int, 6> comb2 = initialComb;
	array<int, 6> empty = { 0, 0, 0, 0, 0, 0 };
	double combPair = 0;
	while (comb1 != empty)
	{
		comb2 = initialComb;
		while (comb2 != empty)
		{
			bool cond1 = find(comb1.begin(), comb1.end(), 6) != comb1.end();
			bool cond2 = find(comb1.begin(), comb1.end(), 9) != comb1.end();
			bool cond3 = find(comb2.begin(), comb2.end(), 6) != comb2.end();
			bool cond4 = find(comb2.begin(), comb2.end(), 9) != comb2.end();
			float c = 0.5;
			if ((cond1 && !cond2) || (cond2 && !cond1)) 
			{
				c /= 2.0;
			}
			if ((cond3 && !cond4) || (cond4 && !cond3))
			{
				c /= 2.0;
			}
			combPair += IsCubePair(comb1, comb2) ? c : 0;
			comb2 = NextCombinationC10_6(comb2);
		}
		comb1 = NextCombinationC10_6(comb1);
	}
	cout << combPair << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	IsCubePair({0, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 6, 7});
	FindCubePair();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
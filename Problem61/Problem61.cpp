#include <iostream>
#include <string>
#include <array>
#include <set>
#include <map>
#include <deque>
#include <chrono>
using namespace std;

// Generating every possible numbers and which figure number it is, there will defenitely be repeating so use multimap.
// Multimap is sorted so easier to just search in a range.

multimap<int, int> FigureNums() 
{
	multimap<int, int> figureNums = {};
	for (int n = sqrt(2000) - 1; n < sqrt(20000) + 1; ++n)
	{
		int tri = (n * (n + 1)) / 2;
		int sqr = n * n;
		int pnt = (n * (3 * n - 1)) / 2;
		int hex = n * (2 * n - 1);
		int hep = (n * (5 * n - 3)) / 2;
		int oct = n * (3 * n - 2);
		if (tri > 1000 && tri < 10000)
			figureNums.insert(pair<int, int>(tri, 3));
		if (sqr > 1000 && sqr < 10000)
			figureNums.insert(pair<int, int>(sqr, 4));
		if (pnt > 1000 && pnt < 10000)
			figureNums.insert(pair<int, int>(pnt, 5));
		if (hex > 1000 && hex < 10000)
			figureNums.insert(pair<int, int>(hex, 6));
		if (hep > 1000 && hep < 10000)
			figureNums.insert(pair<int, int>(hep, 7));
		if (oct > 1000 && oct < 10000)
			figureNums.insert(pair<int, int>(oct, 8));
	}
	return figureNums;
}

/*
void CyclicalFigureNum(const multimap<int, int> figureNums)
{	
	for (int m = 19; m < 59; ++m)
	{
		int prevNum = m * (3 * m - 2);
		int lowBound = (prevNum % 100) * 100;
		int upBound = (prevNum % 100 + 1) * 100;
		set<int> groupNum = {};
		groupNum.insert(8);		
		for (int count = 1; count <= 6; ++count) 
		{
			auto itr = figureNums.lower_bound(lowBound);
			while (itr != figureNums.upper_bound(upBound)) 
			{
				prevNum = itr->first;
			}
		}
	}
}
*/

array<int, 4> CyclicalFN(const multimap<int, int> figureNums, set<int>& groupNum, int& resultSum, int layer)
{
	if (layer > 0)
	{
		array<int, 4> target = CyclicalFN(figureNums, groupNum, resultSum, layer - 1);
		int prevNum = target[0];
		int index = target[1];
		int lowBound = (prevNum % 100) * 100;
		int upBound = (prevNum % 100 + 1) * 100;	
		
		if (groupNum.find(index) != groupNum.end()) 
		{
			groupNum.insert(index);
			// add the result to sum
		}
		else
		{
			// backtrack
		}
		// The range of the next loop is decided by the previous, by up and low bound in multimap

	}
	else 
	{
		groupNum = {};
		// The first loop is diffrernt
		for (int m = 19; m < 59; ++m)
		{
			int prevNum = m * (3 * m - 2);
			int lowBound = (prevNum % 100) * 100;
			int upBound = (prevNum % 100 + 1) * 100;
			groupNum.insert(8);
			
			return { prevNum, 8, lowBound, upBound };
		}
	}

}


int main()
{
	auto startTime = chrono::system_clock::now();

	multimap<int, int> figNums = FigureNums();
	set<int> figIndex = {};
	set<int>& groupNum = figIndex;
	int result = 0;
	int& resultSum = result;
	CyclicalFN(figNums, groupNum, resultSum, 6-1);
	cout << result << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
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
// I'm crying... First time encountering a problem I know the method but I don't know how to write the code... :(

multimap<int, int> FigureNums() 
{
	multimap<int, int> figureNums = {};
	for (int n = 1; n < 200; ++n)//(int n = sqrt(2000) - 1; n < sqrt(20000) + 1; ++n)
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


bool CyclicalFN(const multimap<int, int>& figureNums, set<int>& groupNum, int& resultSum,
	int lowBound, int upBound, int& refNum, int prevNum, int step)
{
	if (step <= 1)
		return true;
	for (auto itr = figureNums.lower_bound(lowBound); itr != figureNums.upper_bound(upBound); ++itr)
	{
		int index = itr->second;
		if (groupNum.find(index) == groupNum.end())
		{			
			int value = itr->first;
			int lowBound2 = (value % 100) * 100;
			int upBound2 = (value % 100 + 1) * 100 - 1;				
			groupNum.insert(index);		
			resultSum += value;
			refNum = value; // write the innermost value last

			if (lowBound2 < 1000 || !CyclicalFN(figureNums, groupNum, resultSum, lowBound2, upBound2, refNum, prevNum, step - 1))
			{
				groupNum.erase(index);
				resultSum -= value;
			}		
			else if (step == 2 && refNum % 100 != prevNum / 100)
			{
				groupNum.erase(index);
				resultSum -= value;
			}
			else
			{				
				return true;
			}				
		}
	}
	return false;
}


void CyclicalFigureNum(const multimap<int, int> figureNums)
{	
	for (int m = 19; m < 59; ++m)
	{
		int prevNum = m * (3 * m - 2);
		int lowBound = (prevNum % 100) * 100;
		int upBound = (prevNum % 100 + 1) * 100 - 1;
		set<int> groupNums = {};
		set<int>& groupNum = groupNums;
		groupNum.insert(8);		
		int result = prevNum;
		int& resultSum = result;
		bool endNum = false;
		int ref = 0;
		int& refNum = ref;
		if (lowBound >= 1000 && upBound >= 1000)
			endNum = CyclicalFN(figureNums, groupNum, resultSum, lowBound, upBound, refNum, prevNum, 6);
		if (endNum && refNum % 100 == prevNum / 100)
		{
			cout << prevNum << " " << resultSum << "\n";
			return; // This version there will only be one solution
		}
	}
}

void CyclicalFigureNumV2(const multimap<int, int>& figureNums)
{
	for (auto &a : figureNums)
	{
		int prevNum = a.first;
		int lowBound = (prevNum % 100) * 100;
		int upBound = (prevNum % 100 + 1) * 100 - 1;
		set<int> groupNums = {};
		set<int>& groupNum = groupNums;
		groupNum.insert(a.second);
		int result = prevNum;
		int& resultSum = result;
		bool endNum = false;
		int ref = 0;
		int& refNum = ref;
		if (lowBound >= 1000 && upBound >= 1000)
			endNum = CyclicalFN(figureNums, groupNum, resultSum, lowBound, upBound, refNum, prevNum, 6);
		if (endNum && refNum % 100 == prevNum / 100)
		{
			cout << prevNum <<" "<< a.second <<" " <<resultSum<< "\n";
			return; // Now that it's correct, I can make sure the 6 values are equavalent
		}
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	multimap<int, int> figNums = FigureNums();
	multimap<int, int>& figureNums = figNums;
	CyclicalFigureNum(figureNums);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
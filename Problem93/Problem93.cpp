#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <chrono>
using namespace std;

array<int, 4> NextCombinationC9_4(array<int, 4> combination)
{
	array<int, 9> baseArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto itr1 = combination.rbegin();
	auto itr2 = baseArray.rbegin();
	for (int i = 3; i >= 0; --i)
	{
		if (*itr1 != *itr2)
		{
			int temp = *itr1;
			for (int j = 0; j <= 3 - i; ++j)
			{
				combination[j + i] = temp + j + 1;
			}
			break;
		}
		++itr1;
		++itr2;
		if (itr1 == combination.rend())
			return { 0, 0, 0, 0};
	}
	return combination;
}

// I can't think of better solutions other than enumeration...
// There will sure be repeat cases, and it's ugly code, but eliminating repeat case will make it even uglier
// We first enumertae combinations and permutations, which are both small numbers
// Then we insert 3 operations, because we permute so don't worry about missing cases
// In this case we use left to right calculation rule combine with brackets, because brackets will take care of calculation order
// Then validation check, if it's an integer, if it's positive
// Go over the set and see where the first case it's not consecutive, get the length.
// brackets: 12, 13, 14; 23, 13, 14; 12, 34, 14; 23, 24, 14; 34, 24, 14;

double Operations(double first, double second, int operation)
{
	switch (operation) 
	{
	case 0:
		return (first + second);
	case 1:
		return (first - second);
	case 2:
		return (first * second);
	case 3:
		return (first / (second*1.0));
	}
}

int CheckCondition(double num) 
{
	if (num <= 0)
		return 0;
	else if (num - floor(num) <= 1e-15)
		return floor(num);
	else
		return 0;
}

void CheckLargestSequence() 
{
	array<int, 4> comb = { 1, 2, 3, 4 };
	// Why don't you write enum? even in this problem?? --because I'm lazy (run away)
	array<int, 4> operation = { 0, 1, 2, 3 };
	array<int, 4> ref = { 0, 0, 0, 0 };
	set<int> createdInts = {};
	int longestSeq = 0;
	array<int, 4> longestSeqSet = {};
	do
	{
		do
		{
			for (int i = 0; i< 64; ++i) 
			{
				int opr1 = i % 4;
				int opr2 = (i / 4) % 4;
				int opr3 = (i / 16) % 4;
				createdInts.insert(CheckCondition(
					Operations(Operations(Operations(comb[0], comb[1], opr1), comb[2], opr2), comb[3], opr3)));
				createdInts.insert(CheckCondition(
					Operations(Operations(comb[0], Operations(comb[1], comb[2], opr2) , opr1), comb[3], opr3)));
				createdInts.insert(CheckCondition(
					Operations(comb[0], Operations( comb[1], Operations(comb[2], comb[3], opr3), opr2),  opr1)));
				createdInts.insert(CheckCondition(
					Operations(Operations(comb[0], comb[1], opr1), Operations(comb[2], comb[3], opr3), opr2)));
				createdInts.insert(CheckCondition(
					Operations(comb[0], Operations(Operations(comb[1], comb[2], opr2), comb[3], opr3), opr1)));
			}
		} while (next_permutation(comb.begin(), comb.end()));
		if (*createdInts.begin() == 0)
			createdInts.erase(createdInts.begin());
		int count = 0;
		for (auto& a : createdInts)
		{
			if (a == count + 1)
			{
				++count;
			}
			else
				break;
		}
		if (count > longestSeq)
		{
			longestSeq = count;
			longestSeqSet = comb;
		}

		comb = NextCombinationC9_4(comb);
		createdInts = {};

	} while (comb != ref);
	string seqString = "";
	for (auto& b : longestSeqSet) 
	{
		seqString += to_string(b);
	}
	cout << seqString << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckLargestSequence();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
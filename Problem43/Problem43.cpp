#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <string>
#include <chrono>
using namespace std;

// Limitations:
// d6 must be 5, d4 from 2, 4, 6, 8, 0, (d3+d4+d5) % 3, d1, d2 doesn't matter (can exchange)

// brute force: (this is VERY BAD and slow)
void CheckPermutation() 
{
	array<int, 10> perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	array<int, 7> prime = { 2, 3, 5, 7, 11, 13, 17};
	long long permuResult = 0;
	while (next_permutation(perm.begin(), perm.end())) 
	{
		int permuNum = 0;		
		string digits = "";			
		string permDigits = "";
		deque<int> perm3digit = {};
		perm3digit.push_back(perm[8]);
		perm3digit.push_back(perm[9]);
		auto itr = prime.rbegin();
		for (int i = perm.size()-3; i > 0; --i)
		{
			perm3digit.push_front(perm[i]);
			permDigits = "";
			for (auto& a : perm3digit)
			{
				permDigits += to_string(a);
			}
			permuNum = stoi(permDigits);
			perm3digit.pop_back();				

			if (permuNum % *itr != 0)
				goto skip;
			++itr;
		}
		for (auto& b : perm)
			digits += to_string(b);
		permuResult += stoll(digits);	
		cout << permuResult << "\n";
	skip:;
	}
	cout << permuResult << "\n";			

}

// 1. permutation revised to simplifiy this problem
array<int, 10> NextPandigital()
{
	array<int, 10> perm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int bound = (int)perm.size() - 1;
	for (int i = bound; i > 0; --i)
	{
		if (perm[i - 1] > perm[i] && i != 6)
		{
			for (int j = bound; j > i; --j)
			{
				if (perm[i - 1] > perm[j] && j != 5)
				{
					int temp = perm[i - 1];
					perm[i - 1] = perm[j];
					perm[j] = temp;
					return perm;
				}
			}
		}
	}
	return perm;
}

// 2. find all 3 digit number that can be divided by 11 (start at 5), 13, 17

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckPermutation();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
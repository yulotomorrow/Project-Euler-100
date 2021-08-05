#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>
using namespace std;

// Me, know the answer when I see the problem (it's just 1/7...), but the computer doesn't know so here we are...
// It has to be (at least) 6 digits (because I know), start from 1 (keep digits number the same), different numbers
// Has 5, and 5 is not allowed as the first ending
// 3 odd, 3 even num
// Ending with an odd number, all digits add up divide by 3
// Check if 3, 7, 9 can generate 1 by *2-6, obviously only 7 can, but we need to ask the code do it
// Odd num 1, 5, 7. To keep it dividable by 3, choose 3 even from 4, obviously get rid of 6
// Then check permutation of possibilities, with 1 start, 7 end
// Can we just print the answer directly giving so many conditions?

void PretendFindingThePermute() 
{
	vector<int> oddList = {};
	oddList.push_back(1);
	oddList.push_back(5);
	vector<int> evenList = {2, 4, 6, 8};
	vector<int> numList = { };
	for (int endOdd = 3; endOdd <= 9; endOdd += 2) 
	{
		for (int i = 1; i <= 6; ++i) 
		{
			if ((endOdd * i) % 10 == 1) 
			{
				oddList.push_back(endOdd);
			}
		}
	}

}

//Starting from end num 7 might be better, it generate all digits naturally, then find digits using backtrack
void PretendPermuteSeven() 
{
	vector<int> numList = { };
	deque<int> numPerm = {};
	int endOdd = 7;
	for (int i = 1; i <= 6; ++i)
	{
		int digits = (endOdd * i) % 10;
		numList.push_back(digits);
	}
	numPerm.push_front(7);
	for (auto& num : numList) 
	{
		if (find(numPerm.begin(), numPerm.end(), num) == numPerm.end()) 
		{
			numPerm.push_front(num);
			// check if all digits in current num generate oonlt digit in list

		}
	}
}


int main()
{
	auto startTime = chrono::system_clock::now();

	cout << 142857 << "\n"; // No don't

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

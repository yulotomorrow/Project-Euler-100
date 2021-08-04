#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
using namespace std;

// The power digits converge really fast, the first step will go under 1000 
// so we store the results equal or smaller than the largest number of first iteration 
// might be better using bitmap.

int DigitSquare(int num) 
{
	string numString = to_string(num);
	int digitSquare = 0;
	for (auto& digit : numString) 
	{
		digitSquare += pow((digit - '0'), 2);
	}
	return digitSquare;
}

void CheckDigitSquare() 
{
	int num = 0;
	const int upperLimit1 = 1e7;
	const int upperLimit2 = pow(9, 2) * 7;
	unordered_map<int, bool> is89 = {};
	bool isDigitSquare89 = false;
	for (int i = 1; i < upperLimit1; ++i) 
	{
		if (i <= upperLimit2) 
		{
			if (is89.find(i) == is89.end())
			{
				vector<int> chain = {i};
				int digitSquare = i;
				while (digitSquare != 1 && digitSquare != 89) 
				{					
					if (is89.find(digitSquare) != is89.end())
					{
						chain.push_back(digitSquare);
					}
					digitSquare = DigitSquare(digitSquare);
				}
				if (digitSquare == 1) 
				{
					for (auto& a : chain) 
					{
						is89[a] = false;
						isDigitSquare89 = false;
					}
				}
				else if (digitSquare == 89)
				{
					for (auto& b : chain)
					{
						is89[b] = true;
						isDigitSquare89 = true;
					}
				}
			}
			else 
			{
				auto itr = is89.find(i);
				if (itr != is89.end())
					isDigitSquare89 = itr->second;
			}
		}
		else 
		{
			int digitSquare2 = DigitSquare(i);
			auto itr = is89.find(digitSquare2);
			if (itr != is89.end())
				isDigitSquare89 = itr -> second;
		}
		num += isDigitSquare89 ? 1 : 0;
	}
	cout << num << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	CheckDigitSquare();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
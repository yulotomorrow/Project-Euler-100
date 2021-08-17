#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

// It's a predictably tedious problem... But as I think about it, it's actually doable
// Since square of a certain digit number isn't too big a range
// Find anagram first, then find square pair of the length, then pattern matching

vector<array<string, 2>> InputProcess(string line)
{
	map<string, string> input = {};

	vector<array<string, 2>> wordPair = {};
	string word = "";
	for (auto& chara : line)
	{
		if (chara != '\"' && chara != ',')
		{
			word += chara;
		}
		else if (chara == ',')
		{
			string sortedWord = word;
			sort(sortedWord.begin(), sortedWord.end());
			if (input.find(sortedWord) == input.end())
			{
				input[sortedWord] = word;
			}
			else 
			{
				wordPair.push_back({ input[sortedWord] , word });
//				cout << input[sortedWord] << " " << word << "\n";
			}
			word = "";
		}
	}
	string sortedWord = word;
	sort(sortedWord.begin(), sortedWord.end());
	if (input.find(sortedWord) == input.end())
	{
		input[sortedWord] = word;
	}
	else
	{
		wordPair.push_back({ input[sortedWord] , word });
	}
	return wordPair;
}

// This is a low efficiency method, but let's just bet there won't be many anagrams...
// Note that using map container is not rigorous, if 3 anagrams happen it will fail. Here it works because we are lucky.

void PairMacthing(const vector<array<string, 2>> wordPair) 
{
	int maxSquareNum = 0;
	for (auto& word : wordPair)
	{
		int wordLength = word[0].size();
		map<string, string> nums = {};
		vector<array<string, 2>> numPair = {};
		for (int i = sqrt(pow(10, wordLength - 1)) + 1; i < sqrt(pow(10, wordLength)); ++i)
		{
			string numString = to_string((int)pow(i, 2));
			string sortedNum = numString;
			sort(sortedNum.begin(), sortedNum.end());
			if (nums.find(sortedNum) == nums.end())
			{
				nums[sortedNum] = numString;
			}
			else
			{
				// need pattern checking, so generate two copies, doing here we can skip doing for words 
				// (which doubles this loop, this is already terrible, we should just generate all at once and store them...)
				numPair.push_back({ nums[sortedNum] , numString });
				numPair.push_back({ numString, nums[sortedNum] });
			}
		}
		if (numPair.size() != 0) 
		{
			for (auto& n : numPair) 
			{
				map<char, char> tempMap1 = {};
				map<char, char> tempMap2 = {};
				for (int j = 0; j < wordLength; ++j) 
				{
					// pattern matching check, if fail, skip directly.
					if (tempMap1.find(n[0][j]) == tempMap1.end() || 
						(tempMap1.find(n[0][j]) != tempMap1.end() && tempMap1.find(n[0][j])->second == word[0][j]))
					{
						tempMap1[n[0][j]] = word[0][j];
						tempMap2[n[1][j]] = word[1][j];
					}
					else 
					{
						goto skip;
					}
				}
				if (tempMap1 == tempMap2)
				{
					if (max(stoi(n[0]), stoi(n[1])) > maxSquareNum)
					{
						maxSquareNum = max(stoi(n[0]), stoi(n[1]));
						cout << maxSquareNum << "\n";
					}

				}
			skip:
				;
			}
		}
	}
	cout << maxSquareNum << "\n";
}

void ReadInput()
{
	fstream fs;
	fs.open("Input_98.txt");
	string line;
	while (getline(fs, line))
	{
		PairMacthing(InputProcess(line));
	}
	fs.close();
}


int main()
{
	auto startTime = chrono::system_clock::now();

	ReadInput();


	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

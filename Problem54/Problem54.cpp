#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <deque>
#include <map>
#include <chrono>
using namespace std;

// the notationg in this code is all reversed, smaller number and rank means larger winning. 
// Put together rank and sorted result string, and compare the two containers to see who wins.
// house doesn't matter unless it's flush so we don't record it.

map<char, int> MappingRelation() 
{
	map<char, int> charMap = {};
	charMap['2'] = 12;
	charMap['3'] = 11;
	charMap['4'] = 10;
	charMap['5'] = 9;
	charMap['6'] = 8;
	charMap['7'] = 7;
	charMap['8'] = 6;
	charMap['9'] = 5;
	charMap['T'] = 4;
	charMap['J'] = 3;
	charMap['Q'] = 2;
	charMap['K'] = 1;
	charMap['A'] = 0;
	return charMap;
}

deque<int> RankDeciding(array<int, 13> values, bool isFlush)
{
	bool isStraight = false;
	bool startStraight = false;
	int straightCount = 0;
	int rank = 9;
	bool isTK = false;
	int pairNum = 0;
	deque<int> rearrange = {};
	int index = 0;
	for (auto& a : values) 
	{
		if (a == 4) 
		{
			rank = 9 - 7;
			for (int i = 0; i < 4; ++i)
				rearrange.push_front(index);
		}
		else if (a == 3) 
		{
			isTK = true;
			for (int i = 0; i < 3; ++i)
				rearrange.push_front(index);
		}
		else if (a == 2) 
		{
			++pairNum;
			if (isTK) 
			{
				for (int i = 0; i < 2; ++i)
					rearrange.push_back(index);
				rank = 9 - 6;
			}
			else if (pairNum == 2) 
			{
				rank = 9 - 2;
				if (rearrange.size() == 3) 
				{
					int temp = rearrange.back();
					rearrange.pop_back();
					for (int i = 0; i < 2; ++i)
						rearrange.push_back(index);
					rearrange.push_back(temp);
				}
			}
			else 
			{
				rank = 9 - 1;
				for (int i = 0; i < 2; ++i)
					rearrange.push_front(index);
			}
		}
		else if (a == 1)
		{
			++straightCount;
			startStraight = true;
			rearrange.push_back(index);
		}
		else if (startStraight && straightCount < 5)
		{
			straightCount = 0;
			isStraight = false;
			startStraight = false;
		}
		++index;
	}
	if (straightCount == 5)
		isStraight = true;
	if (isStraight && isFlush && rearrange.front() == 0)
		rank = 9 - 9;
	else if (isStraight && isFlush)
		rank = 9 - 8;
	else if (isFlush)
		rank = 9 - 5;
	else if (isStraight)
		rank = 9 - 4;
	if (isTK && pairNum != 0)
		rank = 9 - 6;
	else if (isTK)
		rank = 9 - 3;
	rearrange.push_front(rank);
	return rearrange;
}

bool InputProcess(string line, map<char, int> charMap)
{
	int charaNum = 0;
	char house = ' ';
	bool isFlush = true;
	array<int, 13> p1Values = { 0 };
	array<int, 13> p2Values = { 0 };
	deque<int> p1Results = {};
	deque<int> p2Results = {};
	int p1Rank = 0;
	int p2Rank = 0;
	for (auto& chara : line)
	{
		++charaNum;
		bool isStart = (charaNum / 3 == 0 || charaNum / 3 == 5);
		bool isP1 = (charaNum <= 15);
		if (charaNum % 3 == 1)
		{
			if(isP1)
				++p1Values[charMap[chara]];
			else
				++p2Values[charMap[chara]];
		}
		else if (charaNum % 3 == 2)
		{
			if (isStart)
			{
				house = chara;
				isFlush = true;
			}
			else
			{
				if (chara != house) 
				{
					isFlush = false;
				}
			}
		}
		// process player 1
		else if (charaNum == 15) 
		{
			p1Results = RankDeciding(p1Values, isFlush);
		}
	}
	// process player 2
	p2Results = RankDeciding(p2Values, isFlush);

	return (p1Results < p2Results);
}

void ReadInput(map<char, int> charMap)
{
	fstream fs;
	fs.open("Input_54.txt");
	string line;
	int player1WinTimes = 0;
	while (getline(fs, line))
	{
		player1WinTimes += InputProcess(line, charMap) ? 1 : 0;
	}
	fs.close();
	cout << player1WinTimes << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	ReadInput(MappingRelation());

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
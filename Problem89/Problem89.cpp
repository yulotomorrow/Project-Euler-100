#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <map>
#include <chrono>
using namespace std;

// Change Roman to number, and don't need to change back
// Accroding to rules each digit is completely separate, just map to character numbers directly.
// Edge case: 4M cannot be written as 2 characters

int InputProcess(string line, map<char, int> charaValue)
{
	int num = 0;
	int charaNum = 0;
	int OriginalCharaNum = 0;
	array<int, 10> digitCharaNum = {0, 1, 2, 3, 2, 1, 2, 3, 4, 2};
	int lastCharaValue = 5000;
	for (auto& chara : line)
	{
		auto charaItr = charaValue.find(chara);
		if (charaItr != charaValue.end()) 
		{
			int charaVal = charaItr->second;
			num += charaVal;
			if (lastCharaValue < charaVal) 
			{
				num -= (2 * lastCharaValue);
			}
			lastCharaValue = charaVal;
			++OriginalCharaNum;
		}		
	}	
//	cout << num << "\n";
	if (num >= 4000) 
	{
		charaNum = 2;
	}
	while (num != 0) 
	{
		charaNum += digitCharaNum[(num % 10)];
		num /= 10;
	}
 //	cout << charaNum << "\n";
	return (OriginalCharaNum - charaNum);
}

void ReadInput(map<char, int> charaValue)
{
	fstream fs;
	fs.open("Input_89.txt");
	string line;
	int totalCharaNum = 0;
	while (getline(fs, line))
	{
		totalCharaNum += InputProcess(line, charaValue);
	}
	fs.close();
	cout << totalCharaNum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	map<char, int> charaValue = {};
	charaValue['M'] = 1000;
	charaValue['D'] = 500;
	charaValue['C'] = 100;
	charaValue['L'] = 50;
	charaValue['X'] = 10;
	charaValue['V'] = 5;
	charaValue['I'] = 1;
	ReadInput(charaValue);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
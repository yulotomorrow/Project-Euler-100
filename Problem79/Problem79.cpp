#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include "Node.h"
using namespace std;

// Search for digits, if not in tree already, attach to root.
// if not the first one not in tree, make a branch

// I use map instead. It kind of feels like... sorting?
// This method has the assumption that digits won't repeat. And I could have not change it in int, char is fine.
void InputProcess(string line, map<int, int>& password)
{	
	int charaNum = 1;
	bool prevCharaFound = false;
	int prevCharaOrder = 0;
	for (auto& chara : line)
	{			
		int charaValue = chara - '0';
		auto itr = password.find(charaValue);
		// new chara insert
		if (itr == password.end())
		{
			password[charaValue] = (prevCharaOrder + 1);
			prevCharaFound = false;
			++prevCharaOrder;			
		}
		// reorder
		else
		{
			if (charaNum != 1)
			{
				if (itr->second <= prevCharaOrder) 
				{
					password[charaValue] = (prevCharaOrder + 1);
				}
			}
			prevCharaFound = true;
			prevCharaOrder = itr->second;
		}
		++charaNum;
	}

}

void ReadInput(map<int, int>& password)
{
	fstream fs;
	fs.open("Input_79.txt");
	string line;
	int lineNum = 0;
	while (getline(fs, line))
	{
		InputProcess(line, password);
		++lineNum;
	}
	fs.close();
	int i = 1;
	int found = true;
	while (found) 
	{
		for (auto& a : password)
		{
			if (a.second == i)
			{				
				cout << a.first;
				++i;
				found = true;
				break;
			}
			found = false;
		}		
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	map<int, int> passwordList = {}; // key: digit, value:order, assume no repeat digit
	map<int, int>& password = passwordList;
	ReadInput(password);
	cout << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
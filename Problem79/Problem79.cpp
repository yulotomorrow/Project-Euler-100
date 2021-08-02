#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include "Node.h"
using namespace std;

// Search for digits, if not in tree already, attach to root.
// if not the first one not in tree, make a branch


void PasswordTree() 
{
	Node* root = new Node(-1);
}

void PasswordMap() 
{
}

void InputProcess(string line)
{
	string num = "";
	int columnNum = 0;
	map<int, int> passwordList = {}; // key: digit, value:order, assume no repeat digit
	for (auto& chara : line)
	{
		num += chara;
		if (passwordList.find(chara - '0') == passwordList.end())
		{

		}
	}

}

void ReadInput()
{
	fstream fs;
	fs.open("Input_79.txt");
	string line;
	int lineNum = 0;
	while (getline(fs, line))
	{
		InputProcess(line);
		++lineNum;
	}
	fs.close();
}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
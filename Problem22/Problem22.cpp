#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
using namespace std;

void InputProcess(string line, map<string, int>& input)
{
	string name = "";
	int num = 0;
	for (auto& chara : line)
	{
		if (chara != ',' && chara != '\"')
		{
			name += chara;
			num += chara - 'A' + 1;
		}
		else if (chara == ',')
		{
			input[name] = num;
			name = "";
			num = 0;
		}
	}
	input[name] = num;
}


void ReadInput(map<string, int>& input)
{
	fstream fs;
	fs.open("Input_22.txt");
	string line;
	while (getline(fs, line))
	{
		InputProcess(line, input);
		cout << "\n";
	}
	fs.close();
}

// map is natually sorted
long long NameScore(const map<string, int>& input)
{
	int count = 0;
	long long nameScore = 0;
	for (auto& a : input) 
	{
		++count;
		nameScore += a.second * count;
	}
	return nameScore;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	map<string, int> inputName = {};
	map<string, int>& input = inputName;
	ReadInput(input);
	cout << NameScore(input) << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// Now it's a different way to go from bottom to top, but still similar to prooblem 18

void InputProcess(string line, int lineNum, vector<vector<int>>& input)
{
	string num = "";
	int columnNum = 0;
	vector<int> lineList = {};
	for (auto& chara : line)
	{
		if (chara != ',')
		{
			num += chara;
		}
		else
		{
			lineList.push_back(stoi(num));
			num = "";
			++columnNum;
		}
	}
	lineList.push_back(stoi(num));
	input.push_back(lineList);
}

void ReadInput(vector<vector<int>>& input)
{
	fstream fs;
	string filename = "Input_83.txt";
	fs.open(filename);
	string line;
	int lineNum = 0;
	while (getline(fs, line))
	{
		InputProcess(line, lineNum, input);
		++lineNum;
	}
	fs.close();
}

// Okay, now we need some SERIOUS shortest path algorithms...

void FindMinPathSum4Dir(vector<vector<int>>& input)
{
	int bound = 80;
	int initial = 1e8;
	vector<vector<int>> inputCopy(bound, vector<int>(bound, initial));
	multimap<int, array<int, 2>> pairs = {};
	for (int diag = 0; diag < 2 * bound - 1; ++diag)
	{
		for (int col = 0; col < bound; ++col) 
		{
			int row = diag - col;
			if (row >= bound || row < 0)
				break;
		}
	}

	cout << inputCopy[bound-1][bound-1] << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<vector<int>> inputList = {};
	vector<vector<int>>& input = inputList;
	ReadInput(input);
	FindMinPathSum4Dir(input);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// similar to prooblem 18, but the container "shape" is different

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
	string filename = "Input_81.txt";
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

void FindMinPathSum2Dir(vector<vector<int>>& input)
{
	int bound = 80;
	for (int indexSum = ((bound - 1) * 2 - 1); indexSum >= 0; --indexSum)
	{
		for (int j = 0; j < bound; ++j)
		{ 
			int i = indexSum - j;
			if (i < bound && i >= 0)
			{
				if (i + 1 < bound && j + 1 < bound)
					input[i][j] += min(input[i + 1][j], input[i][j + 1]);
				else if (i + 1 >= bound)
					input[i][j] += input[i][j + 1];
				else if (j + 1 >= bound)
					input[i][j] += input[i + 1][j];
			}
		}
	}
	cout << input[0][0] << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<vector<int>> inputList = {};
	vector<vector<int>>& input = inputList;
	ReadInput(input);
	FindMinPathSum2Dir(input);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
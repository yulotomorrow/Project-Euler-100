#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// Dynamic programming is actually not that hard...?
// Outer container used vector not array because the problem has variants, don't want to hard code line number
void InputProcess(string line, int lineNum, vector<vector<int>>& input)
{
	string num = "";
	int columnNum = 0;
	vector<int> lineList = {};
	for (auto& chara : line)
	{
		if (chara != ' ')
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
	string filename = "Input_67.txt";
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

// In this problem rewrite the numbers in container directly for simplicity
void FindMaxPathSum(vector<vector<int>>& input) 
{
	for (int i = input.size() - 2; i >= 0; --i) 
	{
		for (int j = 0; j <= i; ++j) 
		{
//			input[i][j] += input[i + 1][j] > input[i + 1][j + 1] ? input[i + 1][j] : input[i + 1][j + 1];
			input[i][j] += max(input[i + 1][j], input[i + 1][j + 1]);
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
	FindMaxPathSum(input);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

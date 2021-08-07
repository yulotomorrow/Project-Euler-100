#include <iostream>
#include <fstream>
#include <set>
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
	string filename = "Input_82.txt";
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

// shortest path from column n-1 to n
// note that there is no necessary to go up or down in the last column, we always do it in the previous column.
// this is badly written, need to revisit...

void FindMinPathSum3Dir(vector<vector<int>>& input)
{
	int bound = 80;
	int smallestAns = 1e7;
	for (int column = bound - 2; column >= 0; --column)
	{
		vector<int> newColumn = {};
		for (int row= 0; row < bound; ++row)
		{
			int smallestChain = 1e7;
			int chainPlus = 0;
			int chainMinus = 0;
			for (int i = 0; i < bound; ++i)
			{
				int row2 = row + i;
				int row3 = row - i;
				if (row2 < bound)
				{
					if (row2 == row)
						chainPlus = input[row][column + 1];
					else
						chainPlus += (input[row2][column + 1] + input[row2][column] - input[row2 - 1][column + 1]);
				}
				if (row3 >= 0)
				{
					if (row3 == row)
						chainMinus = input[row][column + 1];
					else
						chainMinus += (input[row3][column + 1] + input[row3][column] - input[row3 + 1][column + 1]);
				}
				if (smallestChain > chainPlus)
					smallestChain = chainPlus;
				if (smallestChain > chainMinus)
					smallestChain = chainMinus;
			}
			newColumn.push_back(input[row][column] + smallestChain);
		}
		for (int k = 0; k < bound; ++k)
		{
			input[k][column] = newColumn[k];
		}
	}
	for (int j = 0; j < bound; ++j) 
	{
		if (smallestAns > input[j][0])
			smallestAns = input[j][0];
	}
	cout << smallestAns << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<vector<int>> inputList = {};
	vector<vector<int>>& input = inputList;
	ReadInput(input);
	FindMinPathSum3Dir(input);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
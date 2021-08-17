#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

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

array<int, 2> FindCurrentMinimum(const vector<vector<int>> inputCopy, const vector<vector<bool>> canVisit)
{
	int bound = 80;
	int min = 1e8;
	array<int, 2> coord = { 0,0 };
	for (int i = 0; i < bound; ++i) 
	{
		for (int j = 0; j < bound; ++j)
		{
			if (inputCopy[i][j] < min && canVisit[i][j]) 
			{
				coord = { i, j };
				min = inputCopy[i][j];
			}
		}
	}
	return coord;
}

void MinOverwrite(vector<vector<int>>& inputArr, const vector<vector<int>>& input, 
	const vector<vector<bool>> canVisit, int r, int c, int compareVal)
{
	if (inputArr[r][c] > compareVal && canVisit[r][c])
		inputArr[r][c] = compareVal;
}

void FindMinPathSum4Dir(vector<vector<int>>& input)
{
	int bound = 80;
	int initial = 1e8;
	vector<vector<int>> inputCopy(bound, vector<int>(bound, initial));
	vector<vector<int>>& inputArr = inputCopy;
	vector<vector<bool>> canVisit(bound, vector<bool>(bound, true));
	multimap<int, array<int, 2>> pairs = {};
	inputCopy[0][0] = 0;
	for (int a = 1; a <= pow(bound, 2); ++a)
	{
		array<int, 2> coord = FindCurrentMinimum(inputCopy, canVisit);
		int row = coord[0];
		int col = coord[1];
		if (row < bound - 1) 
		{
			if (inputArr[row + 1][col] > (inputArr[row][col] + input[row][col]) && canVisit[row + 1][col])
				inputArr[row + 1][col] = (inputArr[row][col] + input[row][col]);
		}
		if (row > 0)
		{
			if (inputArr[row - 1][col] > (inputArr[row][col] + input[row][col]) && canVisit[row - 1][col])
				inputArr[row - 1][col] = (inputArr[row][col] + input[row][col]);
		}
		if (col < bound - 1)
		{
			if (inputArr[row ][col+ 1] > (inputArr[row][col] + input[row][col]) && canVisit[row][col + 1])
				inputArr[row ][col+ 1] = (inputArr[row][col] + input[row][col]);
		}
		if (col > 0)
		{
			if (inputArr[row][col - 1] > (inputArr[row][col] + input[row][col]) && canVisit[row][col - 1])
				inputArr[row][col - 1] = (inputArr[row][col] + input[row][col]);
		}

		canVisit[row][col] = false;
	}
	// The last element is not in the path, add it.
	cout << inputCopy[bound-1][bound-1] + input[bound - 1][bound - 1] << "\n";
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
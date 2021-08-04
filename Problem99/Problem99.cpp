#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
using namespace std;

// Comparing log method

double InputProcess(string line)
{
	string num = "";
	double result = 0;
	int baseNum = 0;
	int powerNum = 0;
	for (auto& chara : line)
	{
		if (chara != ',')
		{
			num += chara;
		}
		else
		{
			baseNum = stoi(num);
			num = "";
		}
	}
	powerNum = stoi(num);
	result = powerNum * log10(baseNum);
	return result;
}

void ReadInput()
{
	fstream fs;
	fs.open("Input_99.txt");
	string line;
	int lineNum = 0;
	double maxValue = 0;
	int maxLine = 0;
	while (getline(fs, line))
	{
		++lineNum;
		double lineValue = InputProcess(line);
		if (lineValue > maxValue) 
		{
			maxValue = lineValue;
			maxLine = lineNum;
		}		
	}
	fs.close();
	cout << maxLine << "\n";
}


int main()
{
	auto startTime = chrono::system_clock::now();

	ReadInput();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
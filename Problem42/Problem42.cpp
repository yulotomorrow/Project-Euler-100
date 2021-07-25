#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <chrono>
using namespace std;

unordered_set<int> TriangleNumbers(int upperLimit)
{
	unordered_set<int> triangleList = {};
	int triangle = 0;
	int n = 1;
	// this will cause one larger than limit get in the list, in this case doesn't matter, if matters pop it.
	while (triangle < upperLimit) 
	{
		triangle = n * (n + 1) / 2;
		triangleList.insert(triangle);
//		cout << triangle << "\n";
		++n;
	}
	return triangleList;
}

// in this case triangle list won't be large
void InputProcess(string line, unordered_set<int> triangle)
{
	string word = "";
	int num = 0;
	int count = 0;
	for (auto& chara : line)
	{
		if (chara != ',' && chara != '\"')
		{
			word += chara;
			num += chara - 'A' + 1;
		}
		else if (chara == ',')
		{
			if (triangle.find(num) != triangle.end()) 
			{
				++count;
			}
			word = "";
			num = 0;
		}
	}
	if (triangle.find(num) != triangle.end())
	{
		++count;
	}
	cout << count << "\n";
}


void ReadInput(unordered_set<int> triangle)
{
	fstream fs;
	fs.open("Input_42.txt");
	string line;
	while (getline(fs, line))
	{
		InputProcess(line, triangle);
		cout << "\n";
	}
	fs.close();
}

int main()
{
	auto startTime = chrono::system_clock::now();

	int triangleLimit = 500; // for words, roughly 20 * 26

	ReadInput(TriangleNumbers(triangleLimit));

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
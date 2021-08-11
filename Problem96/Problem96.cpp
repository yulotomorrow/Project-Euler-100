#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <chrono>
using namespace std;

// I didn't optimize it, sorry...
// half-backtrack, at this step unfilledList and possible choice list will be fixed.
void BacktrackFilling(set<int> unfilled, array<int, 81>& currentNums, array<array<int, 20>, 81> neighbors,
	array<set<int>, 81>& possNums)
{
	set<int>::iterator unfillItr;
	set<int>::iterator valueItr;
	unfillItr = unfilled.begin();

	while (unfillItr != unfilled.end())
	{
		valueItr = possNums[*unfillItr].begin();
		currentNums[*unfillItr] = *valueItr;
	retry:
		for (auto& nb : neighbors[*unfillItr])
		{
			if (valueItr == possNums[*unfillItr].end())
			{
				currentNums[*unfillItr] = 0;
				--unfillItr;
				valueItr = possNums[*unfillItr].find(currentNums[*unfillItr]);
				++valueItr;
				goto retry;
			}
			currentNums[*unfillItr] = *valueItr;
			if (currentNums[*unfillItr] == currentNums[nb])
			{
//				cout << *unfillItr << " " << currentNums[*unfillItr] << "\n";
				++valueItr;
				goto retry;
			}
		}
		++unfillItr;
	}
//	cout << "finish" << "\n";
}

array<int, 3> DigitSignature(const int i)
{
	int para1 = i / 9;
	int para2 = i % 9;
	int para3 = ((para1 / 3) * 3 + para2 / 3);
	array<int, 3> signature = { para1, para2, para3 };
	return signature;
}

array<array<int, 3>, 81> SignatureList()
{
	array<array<int, 3>, 81> signatureList;
	for (int x = 0; x < 81; ++x)
	{
		signatureList[x] = DigitSignature(x);
	}
	return signatureList;
}

array<array<int, 20>, 81> RelationList(array<array<int, 3>, 81> signatures)
{
	array<int, 20> initial = { 0 };
	array<array<int, 20>, 81> relationList = { initial };
	bool b1 = false;
	bool b2 = false;
	bool b3 = false;
	for (int index = 0; index < 81; ++index)
	{
		int i = 0;
		for (int x = 0; x < 81; ++x)
		{
			b1 = signatures[x][0] == signatures[index][0];
			b2 = signatures[x][1] == signatures[index][1];
			b3 = signatures[x][2] == signatures[index][2];
			if ((b1 || b2 || b3) && !(b1 && b2 && b3))
			{
				relationList[index][i] = x;
				++i;
			}
		}
	}
	return relationList;
}

void EliminateElements(array<set<int>, 81>& possNums, const array<array<int, 20>, 81> neighbors, int index, int inputValue)
{
	for (auto& a : neighbors[index])
	{
		if (!possNums[a].empty() && (possNums[a].find(inputValue) != possNums[a].end()))
		{
			possNums[a].erase(possNums[a].find(inputValue));
		}
	}
}

int SodokuCalculation(set<int> unfill, array<int, 81>& currentNums, const array<array<int, 20>, 81>& neighbors,
	array<set<int>, 81>& possNums)
{
	int threeDigitNum = 0;
	if (unfill.size() == 0)
	{
		cout << "unfill" << "\n";
		return 0;
	}
	else 
	{
		BacktrackFilling(unfill, currentNums, neighbors, possNums);
		threeDigitNum = currentNums[0] * 100 + currentNums[1] * 10 + currentNums[2];
	}
	return threeDigitNum;
}

int InputProcess(string line, int& charaCount, int& lineCount, array<array<int, 20>, 81> neighbors,
	array<int, 81>& initialNums, array<set<int>, 81>& possNums, set<int>& unfill)
{
	int sum = 0;
	
	set<int> initialP{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (auto& chara : line)
	{
		if (chara == 'G')
		{
			initialNums = { 0 };
			charaCount = 0;
			lineCount = 0;
			unfill = {};
			fill(possNums.begin(), possNums.end(), initialP);
			return 0;
		}
		else
		{
			int charaValue = chara - '0';
			initialNums[charaCount] = charaValue;
			if (charaValue == 0)
			{
				unfill.insert(charaCount);
			}
			else
			{
				possNums[charaCount].clear();
				EliminateElements(possNums, neighbors, charaCount, charaValue);
			}
			++charaCount;			
		}
	}		
	++lineCount;
//	cout << lineCount << "\n";
	if (lineCount == 9)
	{
		sum = SodokuCalculation(unfill, initialNums, neighbors, possNums);
		cout << sum << "\n";
	}
	return sum;
}

void ReadInput(array<int, 81>& initialNums, array<array<int, 20>, 81> neighbors)
{
	fstream fs;
	fs.open("Input_96.txt");
	string line;
	int lineNum = 0;
	int charas = 0;
	int& charaCount = charas;
	int& lineCount = lineNum; 
	set<int> unfilledCoord = {};
	set<int>& unfill = unfilledCoord;
	int sum = 0;

	set<int> initialP{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	array<set<int>, 81> possibleNums;
	fill(possibleNums.begin(), possibleNums.end(), initialP);
	array<set<int>, 81>& possNums = possibleNums;

	while (getline(fs, line))
	{
		sum += InputProcess(line, charaCount, lineCount, neighbors, initialNums, possNums, unfill);
//		cout << charas << "\n";
	}
	fs.close();
//	cout << sum << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	array<int, 81> arrayForNums = { 0 };
	array<int, 81>& initialNums = arrayForNums;
	const array<array<int, 20>, 81> neighborList = RelationList(SignatureList());
	const array<array<int, 20>, 81>& neighbors = neighborList;

	ReadInput(initialNums, neighbors);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
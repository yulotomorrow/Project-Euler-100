#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <chrono>
using namespace std;

// Biggest factorio in this problem is 9!
int Factorio(int base) 
{
	int factorio = 1;
	if (base > 0)
	{
		for (int i = 1; i <= base; ++i)
		{
			factorio *= i;
		}
	}
	return factorio;
}

void LexicographicOutput(int index) 
{	
	int remainder = index - 1;
	list<int> permutationList = {};
	vector<int> permutationResult = {};
	list<int>::iterator permItr = permutationList.begin();

	for (int i = 0; i < 10; ++i)
	{
		permutationList.push_back(i);
	}
	for (int a = 9; a >= 0; --a)
	{
		permItr = permutationList.begin();
		int value = remainder / Factorio(a);
		remainder %= Factorio(a);
		advance(permItr, value);		
		permutationResult.push_back(*permItr);		
		permutationList.erase(permItr);
		cout << value << "\n";
	}
	for (auto& x : permutationResult)
	{
		cout << x;
	}
	cout << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	LexicographicOutput(1000000);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}

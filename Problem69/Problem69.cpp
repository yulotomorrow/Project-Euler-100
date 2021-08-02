#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <chrono>
using namespace std;

// Use Euler's product fomular, p as small as possible, just multiply from prime list until hitting the limit.
void MaxTotient() 
{
	const int limit = 1000000;
	vector<int> primeList = { };
	int num = 2;
	int multi = 1;
	do 
	{		
		for (auto& a : primeList)
		{
			if (num % a == 0)
			{
				goto skip;
			}
		}
		primeList.push_back(num);
		multi *= num;
		cout << multi << "\n";
	skip:
		++num;
	}while (multi <= limit);
	cout << multi / (num - 1) << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	MaxTotient();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
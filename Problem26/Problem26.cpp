#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
using namespace std;

// Reversed counting for fewer writes, not really improving
int CheacReciprocalCycle() 
{
	int largestCycle = 0;
	int cycleIndex = 1;
	int cycleNum = 0;
	for (int d = 999; d >2; --d) 
	{
		vector<int> devisors = {};
		auto itr = devisors.begin();
		int i = -1;
		do
		{
			devisors.push_back(i);
			i = (i * 10) % d;
			itr = find(devisors.begin(), devisors.end(), i);
		} while (itr == devisors.end() && i != 0);
		cycleNum = distance(itr, devisors.end());
		if (cycleNum > largestCycle)
		{
			largestCycle = cycleNum;
			cycleIndex = d;
//			cout << d << "\n";
		}
	}
	return cycleIndex;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << CheacReciprocalCycle() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
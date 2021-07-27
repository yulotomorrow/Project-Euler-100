#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <chrono>
using namespace std;

// Any geometrical solution for this one?
// difference between two pentagon: p(n) - p(n-1) = 1 + 3 (n - 1)
// p(n) - p(n-k) = k + 3 (2n - 1 - k) * k / 2
// p(n) + p(n-k) = k + 3 (2n - 1 - k) * k / 2 + (n-k) (3n - 3k -1)
void PentagonNumber() 
{
	for (int n = 1; n < 100; ++n) 
	{
		int pantagon = n * (3 * n - 1) / 2;

	}
}

int main()
{
	auto startTime = chrono::system_clock::now();

	

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
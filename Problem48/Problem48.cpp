#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
using namespace std;

// Last digits sum & mutiply are rigorous, can use cut down method, every cycle only leave 10 digits.
// Can use the string sum & multiply written before, I'm lazy, I will use long long calculation directly >_<
// still need to find a way not doing all these mutipling
void PowerSum() 
{
	long long tenDigit = 0;
	const long long cutting = 1e10;
	for (int i = 1; i < 1000; ++i) // I just don't calculate 1000 here, too obvious
	{
		long long tenDigitLocal = 1;
		for (int j = 1; j <= i; ++j) 
		{
			tenDigitLocal *= i;
			tenDigitLocal %= cutting;
		}
		tenDigit += tenDigitLocal;
		tenDigit %= cutting;
	}
	cout << tenDigit << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	PowerSum();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
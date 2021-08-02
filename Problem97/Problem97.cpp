#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
using namespace std;

// The better way to do it is power over power of 2 and change base , like (2^a)^b = (2^(a^2))^(b/a)
// but I'm too lazy to get my string multiply function (10 digit * 10 digit is risky)
// So, I apologise, I have to loop over 7830457 / 16 (or around 30? which value is not risky?)

void LargePrime()
{
	const long long cutting = 1e10;
	const int multiply1 = 28433;
	const int power = 7830457;
	// use 2^16 as base, 2^32 is a bit risky for long long limit.
	const int newBase = pow (2,16);
	long long tenDigit = 1;
	for (int j = 1; j <= power/16; ++j)
	{
		tenDigit *= newBase;
		tenDigit %= cutting;
//		cout << tenDigit << "\n";
	}
		tenDigit *= pow(2, (power % 16));
		tenDigit %= cutting;
		tenDigit *= multiply1;
		tenDigit %= cutting;
		++tenDigit;
	cout << tenDigit << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	LargePrime();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
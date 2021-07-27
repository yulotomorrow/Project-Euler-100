#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <chrono>
using namespace std;

// Change fraction to multiplication, a/b = c/d => a * d = b * c
// It can be proved that ab * c = a* bc and the 3 digits are all different
// Not only permutation of abc, but has to be cycling. Only 3 groupes for given abc

void FindCancellingFraction() 
{
	vector<array<int, 2>> fractionPair = {};
	int numerator = 1;
	int denominator = 1;
	for (int a = 1; a <= 9; ++a) 
	{	
		for (int b = 1; b <= 9; ++b)
		{
			for (int c = 1; c <= 9; ++c) 
			{	
				if (a != b && b != c) //eliminate trivial cases
				{
					bool multiplier1 = ((a * 10 + b) * c - (b * 10 + c) * a) == 0;
//					bool multiplier2 = ((b * 10 + c) * a - (c * 10 + a) * b) == 0;
//					bool multiplier3 = ((c * 10 + a) * b - (a * 10 + b) * c) == 0;
					if (multiplier1)
						fractionPair.push_back({ a, c });
//					if (multiplier2)
//						fractionPair.push_back({ b, a });
//					if (multiplier3)
//						fractionPair.push_back({ c, b });
				}
			}
		}
	}
	for (auto& a : fractionPair) 
	{
		numerator *= a[0];
		denominator *= a[1];
	}
	// I skip the important part of finding lowest common terms, need to revisit
	cout << numerator << " " << denominator << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindCancellingFraction();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
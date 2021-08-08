#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
using namespace std;

// denominator large enough, the value of a in a/b * (a-1)/(b-1) should be close enough to 1/sqrt(2).
// a/b > (a-1)/(b-1) so a is celling, (a-1) is floor of b/sqrt(2).
// 3/4 * 2/3, 7/10*5/7... This looks familiar, I GUESS this might related to the generation of sqrt(2) (problem 57)

void PrimeNumber(int upperLimit, set<int>& prime)
{
	prime.insert(2);
	prime.insert(3);
	for (int i = 5; i <= upperLimit; ++i)
	{
		for (auto& a : prime)
		{
			if (a <= sqrt(i))
			{
				if (i % a == 0)
				{
					goto skip;
				}
			}
			else
				break;
		}
		prime.insert(i);
	skip:
		;
	}
}

void Coprime(long long &a, long long &b, const set<int>& prime)
{
	for (auto& p : prime)
	{
		if (p <= b)
		{
			while (a % p == 0 && b % p == 0)
			{
				a /= p;
				b /= p;
			}
		}
		else
			break;
	}
}

void FindExactlyHalf(const set<int>& prime)
{	
	long long bCopy = 1e12;	
	while (true) 
	{
		long long b = bCopy;
		long long a = (long long)(b / sqrt(2)) + 1;
		long long aCopy = a;
		long long aMin = a - 1;
		long long bMin = b - 1;
		long long& aRef = a;
		long long& bRef = b;
		long long& amRef = aMin;
		long long& bmRef = bMin;
		Coprime(aRef, bmRef, prime);
		Coprime(amRef, bRef, prime);
		a *= aMin;
		b *= bMin;
		Coprime(aRef, bRef, prime);
		if (a == 1) 
		{
			cout << aCopy << "\n";
			return;
		}
		++bCopy;
	}
}

// Shockingly, I guessed the math method to solve it, still need to prove...
void Sqrt2Generator()
{
	// a and b before +1
	long long a = 1;
	long long b = 2;
	int exceedFractionNum = 0;
//	const double ref = 1 / sqrt(2); 
	const long long ref = 1e12 / sqrt(2);
	while (true)
	{
		long long temp1 = a; // old numerator but haven't plus one
		long long temp2 = b; // old denomerator
		a = b;
		b = 2 * b + temp1;
		long long ap =  a + b; // new numerator
		// the result should be denomerator*previous numerator (b(n)*a(n-1)), or (b(n-1)*a(n)+1)
		if (ap * temp2 > ref)
		{
			cout << (ap * temp2 + 1) << "\n";
			return;
		}
	}	
}


int main()
{
	auto startTime = chrono::system_clock::now();

//	set<int> primeList = {};
//	set<int>& prime = primeList;
//	PrimeNumber((int)1e6, prime);
//	FindExactlyHalf(prime);
	Sqrt2Generator();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
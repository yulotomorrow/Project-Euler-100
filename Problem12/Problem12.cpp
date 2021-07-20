#include <iostream>
#include <set>
#include <chrono>
using namespace std;

// This one made me want to rewrite the whole ProjEuler in an OOP project...

void PrimeNumber(int upperLimit) 
{
}

void Divisors() 
{

}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
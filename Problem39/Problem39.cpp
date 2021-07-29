#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// Use Euclid's fomular, a = m^2-n^2, b = 2mn, c = m^2 + n^2, a+b+c = 2m^2 + 2mn
// k*m*(m+n), 3 divisor, this is again a find divisor problem
void FindPerfectTriGroup() 
{
	int solutionNum = 0;
	int mostGroup = 0;
	for (int p = 500; p >= 1; --p) 
	{

		
	}
}

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
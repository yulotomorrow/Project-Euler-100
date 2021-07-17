#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

void FibonacciGenerator(long upperLimit, vector<long>& fiboArray)
{
	long i1 = 1;
	long i2 = 2;
	long i3;
	loop:
	i3 = i1 + i2;
	if ((i3) < upperLimit) 
	{
		fiboArray.push_back(i3);		
		i1 = i2;
		i2 = i3;
		goto loop;
	}
}

long FibonacciAdding(const vector<long>& fiboArray)
{
	long i = 0;
	for (auto &a : fiboArray) 
	{
		if (a % 2 == 0)
		{
			i += a;
			cout << a << "\n";
		}
			
		
	}
	return i;
}

int main()
{
	auto startTime = chrono::system_clock::now();
	vector<long> fibonacciArray = { 2 };
	vector<long>& fiboArray = fibonacciArray;
	long upperLimit = 4000000;
	FibonacciGenerator(upperLimit, fiboArray);
	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	cout << FibonacciAdding(fiboArray) << "\n";
	cout << runTime / 1000.0 << "\n";
}


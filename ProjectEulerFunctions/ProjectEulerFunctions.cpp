#include <iostream>
#include <chrono>
using namespace std;

int main()
{
	auto startTime = chrono::system_clock::now();


	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
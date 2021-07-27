#include <iostream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

// Every other (odd index) triangle number is hexagonal number, only check pentagon
// 3(k-1)^2 > 2Tn > 3k^2
// note that indexes also need to be long long in this problem
long long CheckPentagon() 
{
	long long index = 285 + 2;
	long long triangleNum2 = 0;
	bool isEqual = false;
	do 
	{
		triangleNum2 = index * (index + 1);
		int upperLimit = round(sqrt(triangleNum2 / 3.0)) + 1;
		int lowerLimit = (int)sqrt(triangleNum2 / 3.0);
		// 2-4 values, O(1)
		for (long long i = lowerLimit; i <= upperLimit; ++i) 
		{
			isEqual = (triangleNum2 == i * (3 * i - 1) );
			if (isEqual)
				break;
		}
		index += 2;
	} while (!isEqual);
	return triangleNum2 / 2;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << CheckPentagon() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
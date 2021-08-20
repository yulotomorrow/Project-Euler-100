#include <iostream>
#include <set>
#include <string>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

// For integer right triangles in a box, we have a, b, c, and the trinagel A, B < C.
// let a = A, and a should be the largest edge, so b + c <= a, B <= 2A.
// Let b > c, then the number b is between b = a and b = celling( B / 2 ) (if B > A).
// The M we want is A(a).

void FindTriNumsGivenOneEdge()
{
	int solution = 0;
	const int limit = (1e9 + 2) / 3;
	int triBound = (int)sqrt(limit) + 2;
	int a = 2;
	while (solution < 1e6)
	{
		++a;
		for (int b = 2; b <= 2 * a; ++b)
		{
			int cSquare = pow(a, 2) + pow(b, 2);
			if (cSquare == pow((int)sqrt(cSquare), 2))
			{
				if (b <= a)
					solution += b / 2;
				// (b-a, a) to (b/2, b/2(+1))
				else
					solution += a - ceil(b/2.0) + 1;
//				cout << a << " " << b << "\n";
			}
		}		
	}
	cout << a << " "<< solution<<"\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindTriNumsGivenOneEdge();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

/*
* The possible route is symmetric at the diagonal nodes
* And the possible routes to each diagonal node follows the Yang Hui triangle (Pascal's triangle)
* We need to calculate the 21st line of the triangle (start with 1, 20 ...) to solve the problem
*/

void FindTriangleRow(vector<int>& triangle)
{
	for (int i = 1; i <= 20; ++i) 
	{
		triangle.push_back(1);
		if (triangle.size() >= 2) 
		{
			for (int x = i - 1; x > 0; --x)
				triangle[x] += triangle[x - 1];
		}
	}
}

long long SumOfSquare(const vector<int>& triangle)
{
	long long sum = 0;
	for (auto& a : triangle)
	{
		sum += pow(a, 2);
	}
	return sum;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	vector<int> triangleList = {1};
	vector<int>& triangle = triangleList;
	FindTriangleRow(triangle);
	cout << SumOfSquare(triangle) << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
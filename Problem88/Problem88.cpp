#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;

// Here I am challenging the siad to be hardest problem in 1-100
// It's easy to see only by filling 1s can we reach the same value, so the question is how many 1s.
// Think about it from two aspects:
// One is the boundary of search. The number N must larger than k which is obvious
// And it must be smaller than 2k, at least for even numbers, that the worst case is 1s* 2 * k
// Then think about the lower and upper bound of k for a composite number.
// The smallest k is achieved by 1s*(smallest divisor)*(else)
// The largest k is achieved by 1s * (all minimum divisors)
// The largest k is got from: k = N - (multiply)(minimum divisors - 1)
// So for a given k, can we 1) composite the N; 2)search the N

int main()
{
	auto startTime = chrono::system_clock::now();



	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
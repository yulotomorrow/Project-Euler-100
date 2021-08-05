#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

// two ways of dividing: 1, 4, 4 and 2, 3, 4
// Do all permutations and check these two ways
// Why not directly change to int...?

void PandigitalProduct() 
{
	int result = 0;
	set<int> results = {}; // use set collide to avoid repeating
	string pandigital = "123456789";
	bool canPerm = true;
	while (canPerm)
	{
		string multi1 = string(1, pandigital[0]);
		string multi4 = string(1, pandigital[2]) + string(1, pandigital[3]) + string(1, pandigital[4]);
		string multi2 = string(1, pandigital[1]) + multi4;
		string multi3 = multi1 + string(1, pandigital[1]);
		string multi = string(1, pandigital[5]) + string(1, pandigital[6]) + string(1, pandigital[7]) + string(1, pandigital[8]);
		if (stoi(multi1) * stoi(multi2) == stoi(multi) || stoi(multi3) * stoi(multi4) == stoi(multi))
		{
			results.insert(stoi(multi));
//			cout << multi << "\n";
		}
		canPerm = next_permutation(pandigital.begin(), pandigital.end());
	}
	for (auto& a : results)
		result += a;
	cout << result << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	PandigitalProduct();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
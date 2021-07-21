#include <iostream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

//This problem gave a high lower limit in the problem itself and can be largely simplified by analysis.
// n must equal 2 to get possible larger result than example. 
//Because starting with 9, next number must have more digits, eliminating the possibility of n = 3 and 4

// I'm VERY VERY unsatisfied with the method using here...
void FindLargePandigital()
{
	vector<int> multiply1 = {};
	vector<int> multiply2 = {};

	repeat:
	for (int i = 9; i > 0; --i)
	{
		if (find(multiply1.begin(), multiply1.end(), i) == multiply1.end() &&
			find(multiply2.begin(), multiply2.end(), i) == multiply2.end() && multiply1.size() < 4)
		{
			cout << i << "\n";
			multiply1.push_back(i);
			if (i * 2 > 9) 
			{
				if (multiply2.size() == 0) 
				{
					multiply2.push_back(1);
				}
				else
				{					
					int temp1 = multiply2.back();
					if (find(multiply1.begin(), multiply1.end(), temp1 + 1) != multiply1.end() ||
						find(multiply2.begin(), multiply2.end(), temp1 + 1) != multiply2.end() ||
						(i * 2) % 10 == 0)
					{
						multiply1.pop_back();
						goto skip;
					}
					multiply2.back() += 1;
				}

			}	
			else
			{}
			if (find(multiply1.begin(), multiply1.end(), (i * 2) % 10) != multiply1.end() ||
				find(multiply2.begin(), multiply2.end(), (i * 2) % 10) != multiply2.end())
			{
				multiply1.pop_back();
				goto skip;
			}
			else
			{
					multiply2.push_back((i * 2) % 10);
					goto repeat;
			}
			
		}
		else if (multiply1.size() == 4) 
		{
			for (auto& a : multiply1)
				cout << a;
			for (auto& b : multiply2)
				cout << b;
			cout << "\n";
			return;
		}
	skip:
		;		
	}

}

int main()
{
	auto startTime = chrono::system_clock::now();

	FindLargePandigital();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
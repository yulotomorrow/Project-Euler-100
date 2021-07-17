#include <iostream>
#include <string>
#include <chrono>
using namespace std;

bool CheckPalindrome(int value) 
{
	string s = to_string(value);
	auto itr1 = s.begin();
	auto itr2 = s.cbegin();
	while (itr1 != s.end()) 
	{
		if (*itr1 != *itr2) 
		{
			return false;
		}
	}
	return true;
}

int CreatePalindrome6Digits(int num_3digits) 
{
	int palindrome = (num_3digits % 10) * 1100 + ((num_3digits / 10) % 10) * 10010
		+ ((num_3digits / 100) % 10) * 100001;
	return palindrome;
}

bool CheckDividing (int palindrome) 
{
	for (int i = 999; i >= 100; --i) 
	{
		if (palindrome % i == 0 && palindrome / i < 999)
		{
			cout << palindrome << " " << i << "\n";
			return true;
		}
	}
	return false;
}

int FindPalindrome() 
{
	for (int i = 979; i >= 100; --i)
	{
		if (CheckDividing(CreatePalindrome6Digits(i)) == true)
		{
			return CreatePalindrome6Digits(i);
		}
	}
	return -1;
}

int main()
{
	auto startTime = chrono::system_clock::now();

	cout << FindPalindrome() << "\n";

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}



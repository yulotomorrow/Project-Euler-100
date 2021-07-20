#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <chrono>
using namespace std;

//Somehow I remember doing this one in elementry school... pen and paper ofc

// start from Monday, need all days % 7 = 6 to get Sunday
void CheckInYear(array<int, 12> months, array<int, 12>::iterator itr1)
{ 
	itr1 = months.begin();
	int accumulateDays = 0;
	int sundays = 0;
	if (itr1 != months.end())
	{
		accumulateDays += *itr1;
		++itr1;
		if (accumulateDays % 7 == 6)
			sundays += 1;
	}
}

void CheckSunday(array<int, 12> months, array<int, 12> monthsLeap)
{
	int accumulateDays = 0;
	int sundays = 0;
	int year = 1901;
	array<int, 12>::iterator itr1 = months.begin();
	array<int, 12>::iterator itr2 = monthsLeap.begin();
	while (year <= 2000)
	{
		if (year % 4 == 0 && year != 1900)
		{
			while (itr2 != monthsLeap.end())
			{
				if (accumulateDays % 7 == (6-(365 % 7)))
				{
					sundays += 1;
				}					
				accumulateDays += *itr2;
				++itr2;

			}
			++year;
			itr1 = months.begin();
			itr2 = monthsLeap.begin();
		}
		else 
		{
			while (itr1 != months.end())
			{
				if (accumulateDays % 7 == (6 - (365 % 7)))
				{
					sundays += 1;
				}					
				accumulateDays += *itr1;
				++itr1;
			}
			++year;
			itr1 = months.begin();
			itr2 = monthsLeap.begin();
		}

	}
	cout << sundays << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	array<int, 12> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	array<int, 12> monthsLeap = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	CheckSunday(months, monthsLeap);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
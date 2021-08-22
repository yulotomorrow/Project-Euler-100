#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <set>
#include <random>
#include <chrono>
using namespace std;

// What? Instead of calculation as usual, this problem might require us to do SIMULATION??
// Well, I forgot almost everything about probablilty, so let's do it in simulation way and see...

pair<int, bool> RandomGenerator(int diceFace) 
{
	int random1 = rand() % diceFace + 1;
	int random2 = rand() % diceFace + 1;
	if (random1 == random2)
		return pair<int, bool>(random1 + random2, true);
	else
		return pair<int, bool>(random1 + random2, false);
}

int CardSetCC(int input, int now) 
{
	if (input == 1)
		return 0;
	else if (input == 2)
		return 10;
	else
		return now;
}

int CardSetCH(int input, int now)
{
	switch (input)
	{
	case 1:
		return 0;
	case 2:
		return 10;
	case 3:
		return 11;
	case 4:
		return 24;
	case 5:
		return 39;
	case 6:
		return 5;
	case 7:
	case 8:
		if (now == 7)
			return 15;
		else if (now == 22)
			return 25;
		else if (now == 36)
			return 5;
	case 9:
		if (now == 7 || now == 36)
			return 12;
		else if (now == 22)
			return 28;
	case 10:
		return now - 3;
	default:
		return now;
	}
}

void MonopolySimulation() 
{
	array<int, 40> landingTimes = { 0 };
	array<int, 16> cards = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	shuffle(cards.begin(), cards.end(), default_random_engine(seed1));
	array<int, 16> card1 = cards;
	unsigned seed2 = chrono::system_clock::now().time_since_epoch().count();
	shuffle(cards.begin(), cards.end(), default_random_engine(seed2));
	array<int, 16> card2 = cards;

	int maxRoll = 1000000;
	int repeatCounter = 0;
	int currentBlock = 0;
	auto itr1 = card1.begin();
	auto itr2 = card2.begin();

	for (int i = 1; i <= maxRoll; ++i) 
	{
		pair<int, bool> casting = RandomGenerator(4);
		currentBlock += casting.first;
		currentBlock %= 40;
		if(currentBlock == 30)
			currentBlock = 10;
		else if (currentBlock == 7 || currentBlock == 22 || currentBlock == 36)
		{
			currentBlock = CardSetCH(*itr1, currentBlock);
			++itr1;
			if (itr1 == card1.end())
				itr1 = card1.begin();
		}
		// Use if because CH can lead to CC (but not the other way)
		if (currentBlock == 2 || currentBlock == 17 || currentBlock == 33)
		{
			currentBlock = CardSetCC(*itr2, currentBlock);
			++itr2;
			if (itr2 == card2.end())
				itr2 = card2.begin();
		}
		if (casting.second)
		{
			++repeatCounter;
			if (repeatCounter == 3)
				currentBlock = 10;
		}
		else
			repeatCounter = 0;
		++landingTimes[currentBlock];
	}

	string largeSequence = "";
	for (int j = 1; j <= 3; ++j) 
	{
		auto itr3 = max_element(landingTimes.begin(), landingTimes.end());
		if (itr3 - landingTimes.begin() < 10)
		{
			largeSequence += '0';
			largeSequence += to_string(itr3 - landingTimes.begin());
		}
		else
			largeSequence += to_string(itr3 - landingTimes.begin());
		*itr3 = 0;
	}
	cout << largeSequence << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	MonopolySimulation();

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
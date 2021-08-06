#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <array>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

// ASCII upper case: 65-90 Lower case: 97-122
// I can do mod 2 repeatly but I'm lazy here...

int XOROperation(int text, int cipher)
{
	string binaryText = bitset<8>(text).to_string();
	string binaryCipher = bitset<8>(cipher).to_string();
	string binaryConvert = "";
	for (int i = 0; i < 8; ++i) 
	{
		binaryConvert = binaryConvert + to_string(((binaryText[i] - '0') + (binaryCipher[i] - '0')) % 2);
	}
	return stoi(binaryConvert, 0, 2);
}

bool ValidCipher(int text, int cipher)
{
	int target = XOROperation(text, cipher);
	if ((target >= 65 && target <= 90) || (target >= 97 && target <= 122)) //
		return true;
	else
		return false;
}

array<int, 3> InputProcess(string line, set<int> cipher, vector<int>& charas)
{
	string num = "";
	int charaNum = 0;
	set<int> cipher1 = cipher;
	set<int> cipher2 = cipher;
	set<int> cipher3 = cipher;
	array<int, 3> ciphers = {0};
	for (auto& chara : line)
	{
		if (chara != ',')
		{
			num += chara;
		}
		else
		{			
			int dex = stoi(num);
			for (int a = 97; a <= 122; ++a)
			{
				if (!ValidCipher(dex, a)) 
				{
					if (charaNum % 3 == 0)
						cipher1.erase(a);
					else if (charaNum % 3 == 1)
						cipher2.erase(a);
					else if (charaNum % 3 == 2)
						cipher3.erase(a);
				}
			}
			charas.push_back(dex);
			num = "";
			++charaNum;
		}
	}
	int dex = stoi(num);
	for (int a = 97; a <= 122; ++a)
	{
		if (!ValidCipher(dex, a))
		{
			if (charaNum % 3 == 0)
				cipher1.erase(a);
			else if (charaNum % 3 == 1)
				cipher2.erase(a);
			else if (charaNum % 3 == 2)
				cipher3.erase(a);
		}
	}
	charas.push_back(dex);

//	if (cipher1.size() == 1)
		ciphers[0] = *(cipher1.begin());
//	if (cipher2.size() == 1)
		ciphers[1] = *(cipher2.begin());
//	if (cipher3.size() == 1)
		ciphers[2] = *(cipher3.begin());
	return ciphers;
}

void ReadInput(set<int> cipher, vector<int>& charas)
{
	fstream fs;	
	string line;
	int total = 0;
	array<int, 3> ciphers = {};
	fs.open("Input_59.txt");
	while (getline(fs, line))
	{
		ciphers = InputProcess(line, cipher, charas);
	}
	fs.close();
	int index = 0;
	for (auto& b : charas) 
	{
		total += XOROperation(b, ciphers[index % 3]);
		++index;
	}
	cout << total << "\n";
}

int main()
{
	auto startTime = chrono::system_clock::now();

	set<int> cipher = {};
	vector<int> characters = {};
	vector<int>& charas = characters;
	for (int a = 97; a <= 122; ++a) 
	{
		cipher.insert(a);
	}
	ReadInput(cipher, charas);

	auto endTime = chrono::system_clock::now();
	auto runTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

	cout << runTime / 1000.0 << "\n";
}
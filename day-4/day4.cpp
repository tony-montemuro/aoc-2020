//Programmer: Anthony Montemuro
//Date: 12/4/2020
//Description: Solution to Day 4 in Advent of Code 2020 [NOTE: THIS CODE ONLY RETURNS THE RESULT FOR PART 2!]

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool validPass(const map<string, string>& m);
bool validValues(const map<string, string>& m);
bool withinRange(string y, string year1, string year2);

int main()
{
	//Declare variables
	int numOfValid = 0;
	ifstream puzzle_input;
	vector<string> v;
	//Open file - if opening file fails, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through the list of passports, and store each one within vector v
	while (!puzzle_input.eof())
	{
		string str = " ", passport = "";
		//This assures that the entirety of each password is stored, since the formatting in puzzleInput varies from passport to passport
		while (!puzzle_input.eof() && str != "")
		{
			getline(puzzle_input, str, '\n');
			if (passport.empty())
			{
				passport += str;
			}
			else
			{
				passport += " " + str;
			}
		}
		//Add to vector v
		v.push_back(passport);
	}
	v.back() += " ";
	//Check each passport, and increment numOfValid1 if passport is valid
	for (int i = 0; i < v.size(); i++)
	{
		//Declare and initialize variables
		string currentPass = v.at(i);
		int spacePos = 0, pos = 0;
		map<string, string> m;
		//Split up passports to find each key-value pair, and insert each pair into map m
		spacePos = currentPass.find(" ");
		while (spacePos != string::npos)
		{
			string keyvalue = currentPass.substr(pos, spacePos-pos);
			string key = keyvalue.substr(0, 3), value = keyvalue.substr(4, keyvalue.length()-4);
			m.insert(pair<string, string>(key, value));
			pos = spacePos+1;
			spacePos = currentPass.find(" ", spacePos+1);
		}
		//If passport is valid, increment numOfValid
		if (validPass(m))
		{
			numOfValid++;
		}
	}
	//Print result to console [answer to part 1 was 260]
	cout << numOfValid << endl;
	return 0;
}

bool validPass(const map<string, string>& m)
{
	/*
		Precond: m is of type const map<string, string>&, and is the map of each passport's fields
		Postcond: If the passport is valid, true is returned. Otherwise, false is returned.
	*/
	//If the passport has less than 7 fields, it cannot be valid
	if (m.size() < 7)
	{
		return false;
	}
	if (validValues(m))
	{
		//If the passport has 7 fields, it is only valid if it is missing the cid field
		if (m.size() == 7)
		{
			auto it = m.find("cid");
			//If cid field is not found in passport, return true; otherwise, returns false
			if (it == m.end())
			{
				return true;
			}
			return false;
		}
		//Returns true when all 8 fields are present
		return true;
	}
	//Returns false if the values aren't valid
	return false;
}

bool validValues(const map<string, string>& m)
{
	/*
		Precond: m is of type const map<string, string>&, and is the map of each passport's fields
		Postcond: If all the values of the passports are valid, true is returned. If any of them are invalid, however, false is returned
	*/
	//Initialize iterator
	auto it = m.cbegin();
	//First check - birthyear
	if (!withinRange(it->second, "1920", "2002"))
	{
		return false;
	}
	//If there is a cid field, ignore
	if ((++it)->first == "cid")
	{
		++it;
	}
	//Second check - eye color
	//Initialize variables
	bool validEye = false;
	string validEyeColor[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	for (int i = 0; i < 7; i++)
	{
		if (it->second == validEyeColor[i])
		{
			validEye = true;
		}
	}
	if (!validEye)
	{
		return false;
	}
	//Third check - expiration year
	if (!withinRange((++it)->second, "2020", "2030"))
	{
		return false;
	}
	//Fourth check - hair color
	//If hair color is not exactly 7 characters, it cannot be valid
	if ((++it)->second.length() != 7)
	{
		return false;
	}
	//If the first character of hcl is not #, it is not valid
	else if (it->second[0] != '#')
	{
		return false;
	}
	//If a character that is not 0-9 or a-f is present in the hex value, return false
	for (int i = 1; i < it->second.length(); i++)
	{
		if (it->second[i] > 'f')
		{
			return false;
		}
	}
	++it;
	//Fifth check - height
	//Initialize variables
	string unit = it->second.substr(it->second.length()-2, 2);
	string num = it->second.substr(0, it->second.length()-2);
	//if unit is cm, if num is not within the correct range, false is returned
	if (unit == "cm")
	{
		if (!withinRange(num, "150", "193"))
		{
			return false;
		}
	}
	//if unit is in, if num is not within the correct range, false is returned
	else if (unit == "in")
	{
		if (!withinRange(num, "59", "76"))
		{
			return false;
		}
	}
	//if unit is not cm or in, it is an invalid unit
	else
	{
		return false;
	}
	//Sixth check - issue year
	if (!withinRange((++it)->second, "2010", "2020"))
	{
		return false;
	}
	//Seventh check - passport id
	if ((++it)->second.length() != 9)
	{
		return false;
	}
	//If all checks have passed, this passport is valid; return true
	return true;
}

bool withinRange(string v, string bound1, string bound2)
{
	/*
		Precond: v, bound1, and bound2 are all of type string; bound1 < bound2; v is the string to be tested
		Postcond: If v is within the bounds of bound1 and bound2, true is returned. Otherwise, false is returned
	*/
	if (v >= bound1 && v <= bound2)
	{
		return true;
	}
	return false;
}

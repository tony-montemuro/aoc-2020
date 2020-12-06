//Programmer: Anthony Montemuro
//Date: 12/6/2020
//Description: Solution to Day 6 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool isUnique(char c, string s);
int numOfUnanimous(vector<string>& v);

int main()
{
	//Declare variables
	int sumOfCounts1 = 0, sumOfCounts2 = 0;
	ifstream puzzle_input;
	vector<string> customs;
	//Open file - if problems, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	while (!puzzle_input.eof())
	{
		string str = " ", custom = "";
		while (!puzzle_input.eof() && str != "")
		{
			getline(puzzle_input, str, '\n');
			if (custom.empty())
			{
				custom += str;
			}
			else
			{
				custom += " " + str;
			}
		}
		//Add custom to vector customs
		customs.push_back(custom);
	}
	customs.back() += " ";
	//Count the number of questions answered in each custom
	for (int i = 0; i < customs.size(); i++)
	{
		//Declare variables
		vector<string> v;
		string custom = customs.at(i), allChar = "";
		int spacePos = 0, pos = 0;
		//Loop through each character of custom; if the character is unique, increment sumOfCounts.
		for (int j = 0; j < custom.length(); j++)
		{
			if (custom[j] != ' ' && isUnique(custom[j], allChar))
			{
				allChar += custom[j];
				sumOfCounts1++;
			}
		}
		//Split the string into substrings that represent each unique set of answers
		spacePos = custom.find(" ");
		while (spacePos != string::npos)
		{
			v.push_back(custom.substr(pos, spacePos-pos));
			pos = spacePos+1;
			spacePos = custom.find(" ", pos);
		}
		//Increment sumOfCounts2 by the number of unique answers in each answer group
		sumOfCounts2 += numOfUnanimous(v);
	}
	//Print result to console
	cout << sumOfCounts1 << endl;
	cout << sumOfCounts2 << endl;
	return 0;
}

bool isUnique(char c, string s)
{
	/*
		Precond: c is of type char, s is of type string.
		Postcond: If c is found within s, return false. Otherwise, return true.
	*/
	for (int i = 0; i < s.length(); i++)
	{
		if (c == s[i])
		{
			return false;
		}
	}
	return true;
}

int numOfUnanimous(vector<string>& v)
{
	/*
		Precond: v is of type const vector<string>&, and represents the answers to the questions for each person.
		Postcond: If only one person responded in the group, return the number of answers he had. Otherwise, return the number of answers that everyone answered.
	*/
	//If answer group is only one person, all answers are unanimous, so simply return the length of v.front()
	if (v.size() == 1)
	{
		return v.front().length();
	}
	//First, sort each string
	for (int i = 0; i < v.size(); i++)
	{
		sort(v.at(i).begin(), v.at(i).end());
	}
	//Now, determine which characters appear in each string
	string unan = v.front(), newUnan = "";
	//Compare the current string with the list of unanimous answers; if character a j in s is found in unan, add it to newUnan
	for (int i = 1; i < v.size(); i++)
	{
		string s = v.at(i);
		for (int j = 0; j < s.length(); j++)
		{
			if (!isUnique(s[j], unan))
			{
				newUnan += s[j];
			}
		}
		//Set unan equal to newUnan, and reset unan; also, if unan.length() is 0, just return 0
		unan = newUnan;
		if (unan.length() == 0)
		{
			return 0;
		}
		newUnan = "";
	}
	return unan.length();
}

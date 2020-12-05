//Programmer: Anthony Montemuro
//Date: 12/5/2020
//Description: Solution to Day 5 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getID(string s);
int getYourID(const vector<int>& v);

int main()
{
	//Declare variables
	int maxSeatID = 0;
	vector<int> ids;
	ifstream puzzle_input;
	//Open file - if unable, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	while (!puzzle_input.eof())
	{
		string s;
		puzzle_input >> s;
		int i = getID(s);
		if (i > maxSeatID)
		{
			maxSeatID = i;
		}
		ids.push_back(i);
	}
	sort(ids.begin(), ids.end());
	//Print result to console
	cout << maxSeatID << endl;
	cout << getYourID(ids) << endl;
	return 0;
}

int getID(string s)
{
	/*
		Precond: s is of type string, and represents a binary space partitioned seat.
		Postcond: The seat ID is returned.
	*/
	int row, col, lower = 0, upper = 127;
	for (int i = 0; i < 7; i++)
	{
		char c = s[i];
		if (c == 'F')
		{
			upper = (lower + upper) / 2;
		}
		else
		{
			lower = (lower + upper) / 2 + 1;
		}
	}
	row = upper;
	lower = 0;
	upper = 7;
	for (int i = 7; i < 10; i++)
	{
		char c = s[i];
		if (c == 'L')
		{
			upper = (lower + upper) / 2;
		}
		else
		{
			lower = (lower + upper) / 2 + 1;
		}
	}
	col = upper;
	return row * 8 + col;
}

int getYourID(const vector<int>& v)
{
	for (int i = 0, j = v.at(i); i < v.size(); i++, j++)
	{
		if (v.at(i) != j)
		{
			return v.at(i) - 1;
		}
	}
	return -1;
}

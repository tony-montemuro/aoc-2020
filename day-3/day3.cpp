//Programmer: Anthony Montemuro
//Date: 12/3/2020
//Description: Solution to Day 3 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	//Declare variables
	vector<string> v;
	int treeCtr[5];
	int pos = 0, len, product = 1;
	ifstream puzzle_input;
	//Initialize treeCtr array
	for (int i = 0; i < 5; i++)
	{
		treeCtr[i] = 0;
	}
	//Open file
	puzzle_input.open("C:/Users/TonyA/OneDrive/Documents/AoC2020/day-3/puzzleInput.txt");
	//Return 1 if file cannot be opened
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through and push puzzle input into vector v
	while (!puzzle_input.eof())
	{
		string s;
		puzzle_input >> s;
		v.push_back(s);
	}
	len = v.front().length();
	//Right 1, down 1
	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i).at(pos) == '#')
		{
			treeCtr[0]++;
		}
		pos = (pos + 1) % len;
	}
	pos = 0;
	//Right 3, down 1
	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i).at(pos) == '#')
		{
			treeCtr[1]++;
		}
		pos = (pos + 3) % len;
	}
	pos = 0;
	//Right 5, down 1
	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i).at(pos) == '#')
		{
			treeCtr[2]++;
		}
		pos = (pos + 5) % len;
	}
	pos = 0;
	//Right 7, down 1
	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i).at(pos) == '#')
		{
			treeCtr[3]++;
		}
		pos = (pos + 7) % len;
	}
	pos = 0;
	//Right 1, down 2
	for (int i = 0; i < v.size(); i+=2)
	{
		if (v.at(i).at(pos) == '#')
		{
			treeCtr[4]++;
		}
		pos = (pos + 1) % len;
	}
	//Get the product of all traversals
	for (int i = 0; i < 5; i++)
	{
		product *= treeCtr[i];
	}
	//Print results to console (result 1: number of trees encountered travelling right 3 down 1 each time; result 2: product of number of trees encountered in each traversal)
	cout << treeCtr[1] << endl;
	cout << product << endl;
	return 0;
}

//Programmer: Anthony Montemuro
//Date: 12/2/2020
//Description: Solution to Day 3 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int traverse(const std::vector<std::string>& v, int right, int down);

using namespace std;

int main()
{
	//Declare variables
	vector<string> v;
	int treeCtr[5];
	int product = 1;
	ifstream puzzle_input;
	//Open file
	puzzle_input.open("puzzleInput.txt");
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
	//Calculate the number of trees per traversal
	treeCtr[0] = traverse(v, 1, 1);
	treeCtr[1] = traverse(v, 3, 1);
	treeCtr[2] = traverse(v, 5, 1);
	treeCtr[3] = traverse(v, 7, 1);
	treeCtr[4] = traverse(v, 1, 2);
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

int traverse(const vector<string>& v, int right, int down)
{
	/*
		Precond: v is of type const& vector<string>, which stores the puzzle input; right is the number of steps right, and is of type int; down is the number of steps down, and is of type int
		Postcond: The number of trees encountered on the given traversal is returned
	*/
	int pos = 0, treeCtr = 0, len = v.front().length();
	for (int i = 0; i < v.size(); i+=down)
	{
		//If pos is at a tree, increase treeCtr
		if (v.at(i).at(pos) == '#')
		{
			treeCtr++;
		}
		//If pos exceeds len, it will loop back to the start
		pos = (pos + right) % len;
	}
	return treeCtr;
}

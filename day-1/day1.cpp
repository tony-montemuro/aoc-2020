//Programer: Anthony Montemuro
//Date: 12/1/2020
//Description: Solution to Day 1 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
	//Initialize variables
	bool isFound = false;
	vector<int> v;
	ifstream puzzle_input;
	int i, j, k, sum;
	//Open file
	puzzle_input.open("C:/Users/TonyA/OneDrive/Documents/AoC2020/day-1/puzzleInput.txt");
	//If file cannot open, return 1
	if (!puzzle_input)
	{
		cout << "Could not file puzzleInput.txt for reading." << endl;
		return 1;
	}
	//Loop through the file, and add each entry into vector v
	while (!puzzle_input.eof())
	{
		int i;
		string i_str;
		puzzle_input >> i_str;
		//Coverts each string to int
		stringstream stream(i_str);
		stream >> i;
		v.push_back(i);
	}
	//Loop through vector v in search of the two entries that sum to equal 2020
	for (i = 0; i < v.size()-1; i++)
	{
		for (j = i+1; j < v.size(); j++)
		{
			//When the solution is found, break out of the loop
			if (v.at(i) + v.at(j) == 2020)
			{
				isFound = true;
				break;
			}
		}
		if (isFound)
		{
			break;
		}
	}
	//Print result 1 to console
	cout << v.at(i) * v.at(j) <<  endl;
	//Loop through vector v in search of the three entries that sum to equal 2020
	isFound = false;
	for (i = 0; i < v.size()-2; i++)
	{
		for (j = i+1; j < v.size()-1; j++)
		{
			for (k = j+1; k < v.size(); k++)
			{
				if (v.at(i) + v.at(j) + v.at(k) == 2020)
				{
					isFound = true;
					break;
				}
			}
			if (isFound)
			{
				break;
			}
		}
		if (isFound)
		{
			break;
		}
	}
	//Print result 2 to console
	cout << v.at(i) * v.at(j) * v.at(k) << endl;
	return 0;
}

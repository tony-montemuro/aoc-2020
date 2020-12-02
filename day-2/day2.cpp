//Programmer: Anthony Montemuro
//Date: 12/2/2020
//Description: Solution to Day 2 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	//Declare variables
	int numOfCorrect1 = 0, numOfCorrect2 = 0;
	ifstream puzzle_input;
	//Open file
	puzzle_input.open("C:/Users/TonyA/OneDrive/Documents/AoC2020/day-2/puzzleInput.txt");
	//If file cannot open, return 1
	if (!puzzle_input)
	{
		cout << "Could not file puzzleInput.txt for reading." << endl;
		return 1;
	}
	//Loop through file to check each password
	while(!puzzle_input.eof())
	{
		//Declare variables
		bool correct = false;
		int i = 0, ctr = 0, pos = 1, lower, upper;
		char ch;
		string line, lower_s = "", upper_s = "", pass;
		//Get line from file
		getline(puzzle_input, line, '\n');
		//Initialize lower_s
		while (isdigit(line[i]))
		{
			lower_s += line[i];
			i++;
		}
		//Convert lower_s to int
		stringstream stream1(lower_s);
		stream1 >> lower;
		i++;
		//Initialize upper_s
		while (isdigit(line[i]))
		{
			upper_s += line[i];
			i++;	
		}
		//Convert upper_s to int
		stringstream stream2(upper_s);
		stream2 >> upper;
		//Initialize ch
		ch = line[++i];
		i += 3;
		//Initialize pass substr
		pass = line.substr(i, line.size()-i);
		//Counts the number of occurences of ch in password
		for (int j = 0; j < pass.size(); j++)
		{
			//If index of pass is equal to ch, increment ctr
			if (pass[j] == ch)
			{
				ctr++;
				//If the index summed by 1 is equal to lower or upper, and the element at this index is ch, correct is set equal to true [unless correct is already true, since only 1 of the two bounds can equal ch]
				if (j+1 == lower || j+1 == upper)
				{
					if (correct)
					{
						correct = false;
					}
					else
					{
						correct = true;
					}
				}
			}
		}
		//If number of occurences in password is within bounds, increment numOfCorrect
		if (ctr >= lower && ctr <= upper)
		{
			numOfCorrect1++;
		}
		//If ch is found at lower or upper, increment numOfCorrect2
		if (correct)
		{
			numOfCorrect2++;
		}
	}
	//Print results to console
	cout << numOfCorrect1 << endl;
	cout << numOfCorrect2 << endl;
	return 0;
}

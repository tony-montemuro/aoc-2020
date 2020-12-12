//Programmer: Anthony Montemuro
//Date: 12/11/2020
//Description: Solution to Day 11 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int simulate1(const vector<string>& v);
char* getSurroundingSeats(int i, string prev, string s, string next);
int simulate2(const vector<string>& v);
int numOfVisible(int x, int y, const vector<string> v);

int main()
{
	//Declare variables
	ifstream puzzle_input;
	vector<string> layout;
	//Open file - if unsuccessful, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through file, and store the entire seat layout into vector layout
	while(!puzzle_input.eof())
	{
		string s;
		puzzle_input >> s;
		layout.push_back(s);
		//cout << s << endl; 
	}
	//Print results to console
	cout << simulate1(layout) << endl;
	cout << simulate2(layout) << endl;
	
	return 0;
}

int simulate1(const vector<string>& v)
{
	/*
		Precond: v is of type const vector<string>&, and stores the seating arrangement.
		Postcond: A simulation is run on the seating arrangement until the simulation makes no change, and the number of occupied seats is returned.
	*/
	//Declare variables
	int numOfOccupied;
	vector<string> prev, current;
	current = v;
	string rowOfFloor = "", floor = ".";
	//Initialize rowOfFloor
	for (int i = 0; i < current.at(0).length()+2; i++)
	{
		rowOfFloor += floor;
	}
	//Insert a row of floor to the beginning and end of the seating arrangement
	current.insert(current.begin(), rowOfFloor);
	current.push_back(rowOfFloor);
	//Append a floor to the beginning and end of each row
	for (int i = 1; i < current.size()-1; i++)
	{
		current.at(i).insert(0, floor);
		current.at(i) += floor;
	}
	//Loop through simulation until simuation has no effect on the seating arrangement
	do
	{
		//Assign previous equal to current, and clear current and numOfOccupied
		prev = current;
		current.clear();
		current.push_back(rowOfFloor);
		numOfOccupied = 0;
		//Loop through each row
		for (int i = 1; i < prev.size()-1; i++)
		{
			string s = ".";
			for (int j = 1; j < prev.at(i).length()-1; j++)
			{
				//Initialize variables - n will store number of occupied seats, surr is the list of surrounding seats
				int n = 0;
				char* surr = getSurroundingSeats(j, prev.at(i-1), prev.at(i), prev.at(i+1));
				for (int k = 0; k < 8; k++)
				{
					//Count number of occupied seats
					if (surr[k] == '#')
					{
						n++;
					}
				}
				if (prev.at(i)[j] == 'L')
				{
					//Case 1: Seat is unoccupied, and no seats adjacent to it are occupied - occupy seat, and increment numOfOccupied
					if (n == 0)
					{
						s += "#";
						numOfOccupied++;
					}
					//Case 2: Seat is unoccupied, and there are seats adjacent to it - remain unoccupied
					else
					{
						s += "L";
					}
				}
				else if (prev.at(i)[j] == '#')
				{
					//Case 3: Seat is occupied, and there are 4 or more occuupied adjacent seats to it - unoccupy seat
					if (n >= 4)
					{
						s += "L";
					}
					//Case 4: Seat is occupied, and there are less than 4 occupied adjacent seats to it - remain occupied, and increment numOfOccupied
					else
					{
						s += "#";
						numOfOccupied++;
					}
				}
				//Case 5: Floor seat, do not change
				else
				{
					s += ".";
				}
			}
			s += ".";
			current.push_back(s);
		}
		current.push_back(rowOfFloor);
	} while (current != prev);
	return numOfOccupied;
}

int simulate2(const vector<string>& v)
{
	/*
		Precond: v is of type const vector<string>&, and stores the seating arrangement.
		Postcond: A different simulation from the one in simulate1 is run on the seating arrangement until the simulation makes no change, and the number of occupied seats is returned.
	*/
	//Declare variables
	int numOfOccupied;
	vector<string> prev, current;
	current = v;
	string rowOfFloor = "", floor = ".";
	//Initialize rowOfFloor
	for (int i = 0; i < current.at(0).length()+2; i++)
	{
		rowOfFloor += floor;
	}
	//Insert a row of floor to the beginning and end of the seating arrangement
	current.insert(current.begin(), rowOfFloor);
	current.push_back(rowOfFloor);
	//Append a floor to the beginning and end of each row
	for (int i = 1; i < current.size()-1; i++)
	{
		current.at(i).insert(0, floor);
		current.at(i) += floor;
	}
	//Loop through simulation until simuation has no effect on the seating arrangement
	do
	{
		//Assign previous equal to current, and clear current and numOfOccupied
		prev = current;
		current.clear();
		current.push_back(rowOfFloor);
		numOfOccupied = 0;
		//Loop through each row
		for (int i = 1; i < prev.size()-1; i++)
		{
			string s = ".";
			for (int j = 1; j < prev.at(i).length()-1; j++)
			{
				int n = numOfVisible(j, i, prev);
				if (prev.at(i)[j] == 'L')
				{
					//Case 1: Seat is unoccupied, and all the closet seats in the 8 directions are unoccupied - occupy seat, and increment numOfOccupied
					if (n == 0)
					{
						s += "#";
						numOfOccupied++;
					}
					//Case 2: Seat is unoccupied, some of the closest seats in the 8 directions are unoccupied - remain unoccupied
					else
					{
						s += "L";
					}
				}
				else if (prev.at(i)[j] == '#')
				{
					//Case 3: Seat is occupied, and 5 or more of the closest seats in the 8 directions are occupied - unoccupy seat
					if (n >= 5)
					{
						s += "L";
					}
					//Case 4: Seat is unoccupied, and less than 5 of the closest seats in the 8 directions are occuped - remain occupied, and increment numOfOccupied
					else
					{
						s += "#";
						numOfOccupied++;
					}
				}
				else
				{
					//Case 5: Floor seat, do not change
					s += ".";
				}
			}
			s += ".";
			current.push_back(s);
		}
		current.push_back(rowOfFloor);
	} while (prev != current);
	return numOfOccupied;
}

char* getSurroundingSeats(int i, string prev, string s, string next)
{
	/*
		Precond: i is of type int. prev, s, and next are all of type string. i is the current column, prev is the previous row of seats, s is the current row of seats, and next is the next row of seats.
		Postcond: An array of characters is generated, which stores the surrounding seats.
	*/
	static char arr[8];
	for (int j = 0; j < 3; j++)
	{
		arr[j] = prev[(i-1)+j];	
	}
	arr[3] = s[i-1];
	arr[4] = s[i+1];
	for (int j = 0; j < 3; j++)
	{
		arr[j+5] = next[(i-1)+j];
	}
	return arr;
}

int numOfVisible(int x, int y, const vector<string> v)
{
	int i = y, j = x, n = 0;
	//First, look for occupied seats to the left of the current seat
	x--;
	while (x >= 0)
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x--;
	}
	x = j;
	//Second, look for occupied seats to the top-left of the current seat
	x--;
	y--;
	while (x >= 0 && y >= 0)
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x--;
		y--;
	}
	x = j;
	y = i;
	//Third, look for occupied seats above the current seat
	y--;
	while (y >= 0)
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		y--;
	}
	y = i;
	//Fourth, look for occupied seats to the top-right of the current seat
	x++;
	y--;
	while (x < v.at(i).length() && y >= 0)
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x++;
		y--;
	}
	x = j;
	y = i;
	//Fifth, look for the occupied seats to the right of the current seat
	x++;
	while (x < v.at(i).length())
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x++;
	}
	x = j;
	//Sixth, look for the occupied seats to the bottom-right of the current seat
	x++;
	y++;
	while (x < v.at(i).length() && y < v.size())
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x++;
		y++;
	}
	x = j;
	y = i;
	//Seventh, look for occupuied seats below the current seat
	y++;
	while (y < v.size())
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		y++;
	}
	y = i;
	//Last, look for the occupied seats to the bottom-left of the current seat
	x--;
	y++;
	while (x >= 0 && y < v.size())
	{
		if (v.at(y)[x] == '#')
		{
			n++;
			break;
		}
		else if (v.at(y)[x] == 'L')
		{
			break;
		}
		x--;
		y++;
	}
	return n;
}

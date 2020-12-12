//Programmer: Anthony Montemuro
//Date: 12/12/2020
//Description: Solution to Day 12 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int manhattan_distance1(const vector<string>& v);
int manhattan_distance2(const vector<string>& v);
void swap_waypoints(int& x, int& y);

int main()
{
	//Declare variables
	ifstream puzzle_input;
	vector<string> v;
	//Open file - if unsuccessful, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input) return 1;
	//Loop through file, and store each direction into vector v
	while (!puzzle_input.eof()) {
		string s;
		puzzle_input >> s;
		v.push_back(s);
	}
	//Print results to console
	cout << manhattan_distance1(v) << endl;
	cout << manhattan_distance2(v);
	
	return 0;
}

int manhattan_distance1(const vector<string>& v)
{
	int vert = 0, hor = 0, dir = 0;
	for (int i = 0; i < v.size(); i++) {
		int num;
		char action = v.at(i)[0];
		string num_s = v.at(i).substr(1, v.at(i).length()-1);
		stringstream stream(num_s);
		stream >> num;
		switch (action)
		{
			case 'N':
				vert += num;
				break;
			case 'S':
				vert -= num;
				break;
			case 'E':
				hor -= num;
				break;
			case 'W':
				hor += num;
				break;
			case 'R':
				dir = (dir + 3 * (num / 90)) % 4;
				break;
			case 'L':
				dir = (dir + (num / 90)) % 4;
				break;
			case 'F':
				switch (dir)
				{
					case 0:
						hor -= num;
						break;
					case 1:
						vert += num;
						break;
					case 2:
						hor += num;
						break;
					case 3:
						vert -= num;
						break;
				}
				break;
		}
	}
	return abs(vert) + abs(hor);
}

int manhattan_distance2(const vector<string>& v)
{
	int waypoint_x = 10, waypoint_y = 1, hor = 0, vert = 0;
	for (int i = 0; i < v.size(); i++)
	{
		int num;
		char action = v.at(i)[0];
		string num_s = v.at(i).substr(1, v.at(i).length()-1);
		stringstream stream(num_s);
		stream >> num;
		switch (action) 
		{
			case 'N':
				waypoint_y += num;
				break;
			case 'S':
				waypoint_y -= num;
				break;
			case 'E':
				waypoint_x += num;
				break;
			case 'W':
				waypoint_x -= num;
				break;
			case 'L':
				switch (num)
				{
					case 90:
						swap_waypoints(waypoint_x, waypoint_y);
						waypoint_x *= -1;
						break;
					case 180:
						waypoint_x *= -1;
						waypoint_y *= -1;
						break;
					case 270:
						swap_waypoints(waypoint_x, waypoint_y);
						waypoint_y *= -1;
						break;
				}
				break;
			case 'R':
				switch (num)
				{
					case 90:
						swap_waypoints(waypoint_x, waypoint_y);
						waypoint_y *= -1;
						break;
					case 180:
						waypoint_x *= -1;
						waypoint_y *= -1;
						break;
					case 270:
						swap_waypoints(waypoint_x, waypoint_y);
						waypoint_x *= -1;
						break;
				}
				break;
			case 'F':
				for (int j = 0; j < num; j++) {
					hor += waypoint_x;
					vert += waypoint_y;
				}
				break;
		}
	}
	return abs(vert) + abs(hor);
}

void swap_waypoints(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

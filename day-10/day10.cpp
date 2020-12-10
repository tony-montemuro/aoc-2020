//Programmer: Anthony Montemuro
//Date: 12/10/2020
//Description: Solution to Day 10 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int result1(const vector<int>& v);
long long int result2(const vector<int>& v);
int numOfAdapters(int n, const vector<int>& v);

int main()
{
	//Declare variables
	ifstream puzzle_input;
	vector<int> v;
	v.push_back(0);
	//Open file - if unsuccessful, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through the file, and store each value into vector v
	while (!puzzle_input.eof())
	{
		int x;
		string str;
		puzzle_input >> str;
		stringstream stream(str);
		stream >> x;
		v.push_back(x);
	}
	//Sort v, and add final adapter
	sort(v.begin(), v.end());
	v.push_back(v.back()+3);
	//Print results to console
	cout << result1(v) << endl;
	cout << result2(v) << endl;
	return 0;
}

int result1(const vector<int>& v)
{
	/*
		Precond: v is of type vector<int>&. It stores each jolt measurement.
		Postcond: The number of 1 jolt differences multiplied by the number of 3 jolt differences is returned.
	*/
	//Declare variables
	int prev = 0, jolt1 = 0, jolt3 = 0;
	for (int i = 1; i < v.size(); i++)
	{
		//If difference is 1, increment jolt1
		if (v.at(i)-1 == prev)
		{
			jolt1++;
		}
		//Otherwise, increment jolt3
		else
		{
			jolt3++;
		}
		prev = v.at(i);
	}
	return jolt1 * jolt3;
}

long long int result2(const vector<int>& v)
{
	//Declare varaibles
	//v2 will store the number of combinations possible at a given index
	vector<long long int> v2(v.size());
	//First adapter only has one possible combination
	v2.at(0) = 1;
	for (int i = 1; i < v.size(); i++)
	{
		int n = numOfAdapters(i, v);
		//If n is one, this means that only the gap between the current adapter and the previous one is <= 3, meanining number of possible combinations remains unchanged
		if (n == 1)
		{
			v2.at(i) = v2.at(i-1);
		}
		//If n is two, this means that the gap between both the current adapter and the previous one, and the current adapter and 2 adapters before, is <= 3, meaning the number of possibilities is the sum of the previous two
		//recorded numbers of possibilites.
		else if (n == 2)
		{
			v2.at(i) = v2.at(i-1) + v2.at(i-2);
		}
		//If n is three, this means that the previous 3 adapters all increment by one, meaning the number of possibilities is the sum of the previous three recorded number of possibilites.
		else if (n == 3)
		{
			v2.at(i) = v2.at(i-1) + v2.at(i-2) + v2.at(i-3);
		}
	}
	//Return the last element in vector v2, which is the final number of combinations
	return v2.at(v.size()-1);
}

int numOfAdapters(int n, const vector<int>& v)
{
	/*
		Precond: n is of type int, v is of type vector<int>& v. n is the current index being checked, v is the vector of ints up to index n.
		Postcond: Return the number of adapters that are 3 or less away from the adapter at index n.
	*/
	int count = 0;
	//If the gap between the current adapter and the previous adapter is less than or equal to 3, increment count
	if (n-1 >= 0 && v.at(n)-v.at(n-1) <= 3)
	{
		count++;
	}
	//If the gap between the current adapter and 2 adapters back is less than or equal to 3, increment count
	if (n-2 >= 0 && v.at(n)-v.at(n-2) <= 3)
	{
		count++;
	}
	//If the gap between the current adapter and 3 adapters back is less than or equal to 3, increment count
	if (n-3 >= 0 && v.at(n)-v.at(n-3) <= 3)
	{
		count++;
	}
	return count;
}

//Programmer: Anthony Montemuro
//Date: 12/9/2020
//Description: Solution to Day 9 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int firstNonValid(vector<int>& p, const vector<int>& d);
bool isValid(const vector<int>& p, int key);
int findIndex(const vector<int>& d, int key);
int sumOf(const vector<int>& d, int index);
int contiguous(vector<int>& r, int key);
int sumOfVect(const vector<int>& v);

int main()
{
	//Declare variables
	int result1;
	ifstream puzzle_input;
	vector<int> data, preamble;
	int i = 0;
	//Open file - if unsuccessful, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Push all the elements of the file into vector data, as well as the first 25 numbers into preamble vector
	while (!puzzle_input.eof())
	{
		int x;
		string s;
		puzzle_input >> s;
		stringstream stream(s);
		stream >> x;
		data.push_back(x);
		//Pushes only the first 25 numbers into preamble vector
		if (i < 25)
		{
			preamble.push_back(x);
		}
		i++;
	}
	result1 = firstNonValid(preamble, data);
	//Print results to console
	cout << result1 << endl;
	cout << sumOf(data, findIndex(data, result1));
	return 0;
}

int firstNonValid(vector<int>& p, const vector<int>& d)
{
	/*
		Precond: d is a const integer vector, p is a integer vector. p stores the preamble, while d stores the entire dataset.
		Postcond: The first value found in vector d whose not the sum of two values in the preamble is returned.
	*/
	for (int i = 25; i < d.size(); i++)
	{
		if (!isValid(p, d.at(i)))
		{
			return d.at(i);
		}
		p.erase(p.begin());
		p.push_back(d.at(i));
	}
	return -1;
}

bool isValid(const vector<int>& p, int key)
{
	/*
		Precond: p is a const integer vectors, which stores the preamble. key is a number found in the dataset.
		Postcond: If key is the sum of two values in the dataset, true is returned. Otherwise, false is returned.
	*/
	for (int i = 0; i < p.size()-1; i++)
	{
		for (int j = i+1; j < p.size(); j++)
		{
			if (p.at(i) + p.at(j) == key)
			{
				return true;
			}
		}
	}
	return false;
}

int findIndex(const vector<int>& d, int key)
{
	/*
		Precond: d is of type const vector<int>&, and stores the entire dataset. key is of type int, and is contained within d.
		Postcond: Returns the index at which key is found within d.
	*/
	//Guessing that it occures after 500th element
	for (int i = 500; i < d.size(); i++)
	{
		if (d.at(i) == key)
		{
			return i;
		}
	}
}

int sumOf(const vector<int>& d, int index)
{
	/*
		Precond: d is of type const vector<int>&, and stores the entire dataset. index is the index of the first invalid element.
		Postcond: The sum of the smallest and the largest numbers of the contiguous set of at least two numbers whose sum is the invalid number from result1 is returned.
	*/
	//Declare variables
	int key = d.at(index);
	vector<int> range, set;
	//Initialize range
	for (int i = 0; i < index; i++)
	{
		range.push_back(d.at(i));
	}
	int last = contiguous(range, key);
	//Initialize set
	for (int i = 0; i < last; i++)
	{
		set.push_back(range.at(i));
	}
	//Sort set, and return the sum of the smallest and largest numbers within the set
	sort(set.begin(), set.end());
	return set.front() + set.back();
}

int contiguous(vector<int>& r, int key)
{
	/*
		Precond: r is of type const vector<int>&, and is the entire dataset before the first invalid number, key is that invalid number.
		Postcond: The index of the last element of the contiguous set is returned. (NOTE: r is modified using this function!)
	*/
	int sum, i;
	while (sum != key)
	{
		i = 0, sum = 0;
		//Removes first element of vector r
		r.erase(r.begin());
		while (sum < key)
		{
			sum += r.at(i);
			i++;
		}
	}
	return i;
	
}

int sumOfVect(const vector<int>& v)
{
	/*
		Precond: v is of type const vector<int>&.
		Postcond: The sum of the vector is returned.
	*/
	int sum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		sum += v.at(i);
	}
	return sum;
}

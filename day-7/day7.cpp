//Programmer: Anthony Montemuro
//Date: 12/7/2020
//Description: Solution to Day 7 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int numOfBags1(const vector<string>& rules, const vector<string>& bags, vector<int>& bagIndexes, string bag);
int numOfBags2(const vector<string>& rules, const vector<string>& bags, string bag);
bool isFound(int key, const vector<int>& v);

int main()
{
	//Declare variables
	ifstream puzzle_input;
	vector<string> v, bags;
	vector<int> bagIndexes;
	string targetBag = "shiny gold bag";
	//Open file - if unsuccessful, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through the entire file and add each line to vector v
	while (!puzzle_input.eof())
	{
		string str;
		getline(puzzle_input, str, '\n');
		v.push_back(str);
	}
	//Store each rule in map m
	for (int i = 0; i < v.size(); i++)
	{
		string rule = v.at(i);
		//Substring bagValue is the bag described
		int split = rule.find("contain") - 2;
		int substrLength = rule.length()-(rule.length()-split);
		string bagValue = rule.substr(0, substrLength);
		bags.push_back(bagValue);
	}
	//Print results to console
	cout << numOfBags1(v, bags, bagIndexes, targetBag) << endl;
	cout << numOfBags2(v, bags, targetBag) << endl;
	return 0;
}

int numOfBags1(const vector<string>& rules, const vector<string>& bags, vector<int>& bagIndexes, string bag)
{
	/*
		Precond: rules and bags are of type const vector<string>&, bagIndexes is of type vector<int>&, and bag is of type string. rules stores the rules about each bag.
				 bags stores the name of each bag, bagIndexes is initially empty, but fills up with the indexes of the bags that contain at least one shiny gold bag.
				 bag stores the target bag string. 
		Postcond: This function recursively searches through the rules to find which bags can contain at least one shiny gold bag, and returns that number of bags.
				  BASE CASE: bag is not contained in any other bags, or is contained in a bag that already is part of bagIndexes.
				  RECURSIVE CASE: bag is contained in another bag that is not yet containted in bagIndexes. This bag's index is pushed into bagIndexes, and recursion occurs.
	*/
	int n = 0;
	for (int i = 0; i < rules.size(); i++)
	{
		//Only search for bag after the word 'contain'
		int start = rules.at(i).find("contain");
		if (rules.at(i).find(bag, start) != string::npos && !isFound(i, bagIndexes))
		{
			bagIndexes.push_back(i);
			n += numOfBags1(rules, bags, bagIndexes, bags.at(i));
			n++;
		}
	}
	return n;
}

int numOfBags2(const vector<string>& rules, const vector<string>& bags, string bag)
{
	/*
		Precond: rules and bags are of type const vector<string>&, and bag is of type string. rules stores the rules about each bag.
				 bags stores the name of each bag, bag stores the target bag string.
		Postcond: This function recursively searches through the rules to find the target bag. Once it is found, it finds it's children bags, and how many of each can be stored in the parent bag.
				  Returns the number of bags that the parent bag can store.
				  BASE CASE: bag has no children bags.
				  RECURSIVE CASE: bag has children bags.
	*/
	int n = 0;
	for (int i = 0; i < rules.size(); i++)
	{
		string s = rules.at(i);
		//If the bag at i is equal to bag and bag contains other bags
		if (s.substr(0, bag.length()) == bag && s.find("no other bags") == string::npos)
		{
			for (int j = 0; j < bags.size(); j++)
			{
				//find is the position at which bag at index j is found in s
				int find = s.find(bags.at(j));
				//If find is within s, and j != i
				if (find != string::npos && j != i)
				{
					int num, recr;
					char num_c;
					find -= 2;
					//Convert num_s into an int
					num_c = s[find];
					num = num_c - '0';
					recr = numOfBags2(rules, bags, bags.at(j));
					n += num * ++recr;
				}
			}
		}
	}
	return n;
}

bool isFound(int key, const vector<int>& v)
{
	/*
		Precond: key is of type int, v is of type vector<int>&.
		Postcond: If key is found within vector v, true is returned. Otherwise, false is returned.
	*/
	for (int i = 0; i < v.size(); i++)
	{
		if (key == v.at(i))
		{
			return true;
		}
	}
	return false;
}

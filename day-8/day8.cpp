//Programmer: Anthony Montemuro
//Date: 12/8/2020
//Description: Solution to Day 8 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool isFixed = false;
int execute1(const vector<string>& v);
int execute2(vector<string>& v);
int exe(const vector<string>& v);

int main()
{
	//Declare variables
	ifstream puzzle_input;
	vector<string> instructions;
	//Open file - if unable to do so, return 1
	puzzle_input.open("puzzleInput.txt");
	if (!puzzle_input)
	{
		return 1;
	}
	//Loop through file to get each instruction
	while (!puzzle_input.eof())
	{
		string str;
		getline(puzzle_input, str, '\n');
		instructions.push_back(str);
	}
	//Print results to screen
	cout << execute1(instructions) << endl;
	cout << execute2(instructions) << endl;
	
	return 0;
}

int execute1(const vector<string>& v)
{
	/*
		Precond: v is a vector of strings, and stores the instructions of the handheld.
		Postcond: Returns the index of the first instruction that is ran twice.
 	*/
	return exe(v);
}

int execute2(vector<string>& v)
{
	/*
		Precond: v is a vector of strings, and stores the instructions of the handheld.
		Postcond: Returns the value of accumulator after the instructions have been fixed.
 	*/
 	//Initialize newInstruct, a hard copy of the original instructions. Will be modified to find the corrupted instruction.
 	vector<string> newInstruct;
 	for (int i = 0; i < v.size(); i++)
 	{
 		newInstruct.push_back(v.at(i));	
	}
	for (int i = 0; i < v.size(); i++)
	{
		//Initialize sub, which is equal to the instruction
		string sub = v.at(i).substr(0, 3);
		//If instruction is jmp, replace it with nop, and if instruction is nop, replace it with jmp
		if (sub == "jmp")
		{
			newInstruct.at(i).replace(0, 3, "nop");
		}
		if (sub == "nop")
		{
			newInstruct.at(i).replace(0, 3, "jmp");
		}
		int accum = exe(newInstruct);
		//When the corrupted instruction is replaced, return the accumulator
		if (isFixed)
		{
			return accum;
		}
		//Return newInstruct back to oringinal
		newInstruct.at(i) = v.at(i);
	}
}

int exe(const vector<string>& v)
{
	/*
		Precond: v is a vector of strings, which hold all the instructions.
		Postcond: The set of instructions are run until an instruction is run twice. If no instructions are run twice, isFixed is set equal to true. The value of the accumulator is returned.
	*/
	vector<bool> hasRun;
	for (int i = 0; i < v.size(); i++)
	{
		hasRun.push_back(false);
	}
	int accum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		//If instruction i has been run, return value of accum
		if (hasRun.at(i) == true)
		{
			return accum;
		}
		//Initialize variables
		hasRun.at(i) = true;
		string fullInstruct = v.at(i), instruct = fullInstruct.substr(0, 3), instructNum_s = fullInstruct.substr(4, fullInstruct.length() - 4);
		stringstream stream(instructNum_s);
		int instructNum;
		stream >> instructNum;
		//If instruction is acc, increment accum by instructNum. If jmp, increment i by the instructNum - 1. If nop, continue.
		if (instruct == "acc")
		{
			accum += instructNum;
		}
		if (instruct == "jmp")
		{
			i += instructNum - 1;
		}
	}
	isFixed = true;
	return accum;
}

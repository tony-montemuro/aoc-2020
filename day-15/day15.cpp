//Programmer: Anthony Montemuro
//Date: 12/15/2020
//Description: Solution to Day 15 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
long long int memGame(int* input, int n, int size);

#define log(x) cout << #x << " " << x << endl

int main()
{
    //Declare variables
    int input[] = {0,13,16,17,1,10,6};
    //Print results to console
    long long int result1 = memGame(input, 2020, 7);
    log(result1);
    long long int result2 = memGame(input, 30000000, 7);
    log(result2);
    return 0;
}

long long int memGame(int* input, int n, int size)
{
    /*
        Precond: input is of type int*, and is the array that stores the puzzle input. Size is of type int, and stores the size of the array.
        Postcond: The memory game is played, and the n-th number spoken is returned.
    */
    //Declare variables
    long long int current, lastSpoken;
    unordered_map<long long int, int> m;
    //On the first size turns, the starting numbers are spoken [Turns 1-(size-1)]
    for (int i = 1; i < size; i++) {
        m[input[i-1]] = i;
    }
    //[Turn size]
    lastSpoken = input[size-1];
    //Afterwards, the game is played [Turns (size+1)-n]
    for (int i = size+1; i <= n; i++) {
        //Case 1: The last number spoken was the first time the number had been spoken.
        if (m.find(lastSpoken) == m.end()) current = 0;
        //Case 2: The last number spoken was spoken before in the game. 
        else current = (i-1) - m[lastSpoken];
        m[lastSpoken] = i-1;
        lastSpoken = current;
    }
    //Return n-th turn of game
    return current;
}

//Programmer: Anthony Montemuro
//Date: 12/13/2020
//Description: Solution to Day 13 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

#define log(x) cout << #x << " " << x << endl;
int earliestBus(const vector<int>& v, int time);
long long int subsequent_index(const vector<int>& v, const vector<int>& c);

int main()
{
    //Declare variables
    ifstream puzzle_input;
    int time, result1;
    long long int result2;
    string str;
    vector<int> ids, constraints;
    //Open file - if unsuccessful, return 1
    puzzle_input.open("puzzleInput.txt");
    if (!puzzle_input) return 1;
    //Store timestamp in integer time, and the ids in string str
    puzzle_input >> time;
    puzzle_input >> str;
    //Parse through the string to get the ints and constraints, and push them into vector<int> ids and vector<int> constraints respectively
    int numOfConstraints = 0;
    for (int i = 0; i < str.length(); i++) {
        string sub = "";
        while (isdigit(str[i])) {
            sub += str[i];
            i++;
        }
        if (str[i] == 'x') numOfConstraints++;
        if (!sub.empty()) {
            int x;
            stringstream stream(sub);
            stream >> x;
            ids.push_back(x);
            constraints.push_back(numOfConstraints);
            numOfConstraints = 0;
        }
    }
    constraints.push_back(0);
    //Print results to console
    result1 = earliestBus(ids, time);
    log(result1);
    // vector<int> test_ids = {7, 13, 59, 31, 19};
    // vector<int> test_cons = {0, 0, 2, 1, 0};
    result2 = subsequent_index(ids, constraints);
    log(result2);
    return 0;
}

int earliestBus(const vector<int>& v, int time)
{
    /*
        Precond: v is of type const vector<int>&, and stores the ids of each bus. time is of type int, and stores the timestamp.
        Postcond: The ID of the earliest bus I can take to the airport is multiplied by the number of minutes needed to wait for the bus, and returned.
    */
   //Declare variables
   vector<int> firstTime;
   int index, timeToWait = INT_MAX;
   //Loop through the list of ids to determine which bus will arrive earliest.
   for (int i = 0; i < v.size(); i++) {
        firstTime.push_back(0);
        while (firstTime.at(i) < time)
        {
            firstTime.at(i) += v.at(i); 
        }
        int j = firstTime.at(i) - time;
        j %= firstTime.at(i);
        if (j < timeToWait)
        {
           index = i;
           timeToWait = j;
        }
   }
   //Return the id of the bus multipled by wait time
   return v.at(index) * timeToWait;
}

long long int subsequent_index(const vector<int>& v, const vector<int>& c)
{
    /*
        Precond: v is the const vector<int>& of ids. c is the const vector<int>& of constraints.
        Postcond: The first timestamp such that the first ubs ID departs at that time and each subsequent listed bust ID departs at that subsequent minute.
    */
    long long int index = 0, step = v.at(0);
    //numPassed is the number of times pos != 0 returns true
    int numPassed = 1;
    //Loop that runs until the first timestamp is found 
    while (1) {
        int i, totalCon = 0;
            for (i = 1; i < v.size(); i++) {
                totalCon += c.at(i);
                int pos = (index + i + totalCon) % v.at(i); 
                if (pos != 0) break;
            }
            //Multiply step by the timestamp at timestamp index
            if (i > numPassed) {
                step *= v.at(i-1);
                numPassed++;
            } 
            if (i == v.size()) return index;
        index += step;
    }
}

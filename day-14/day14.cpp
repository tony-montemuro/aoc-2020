//Programmer: Anthony Montemuro
//Date: 12/14/2020
//Description: Solution to Day 14 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cmath>

using namespace std;

#define log(x) cout << #x << " " << x << endl;
long long int sumOfVals(const vector<string>& b, const vector<vector<string>>& m);
long long int sumOfVals2(const vector<string>& b, const vector<vector<string>>& m);
string intToBin(int val);
void performBitmask(const string& bitmask, string& val);
long long int binToLong(const string& s);
void performBitmask2(const string& bitmask, string& address);
void genAddresses(string address, unordered_map<string, int>& mem, int val);

int main() 
{
    //Declare variables
    ifstream puzzle_input;
    string in;
    vector<string> bitmasks;
    vector<vector<string>> memAdresses;
    long long int result1, result2;
    //Open file - if unsuccessful, return 1
    puzzle_input.open("puzzleInput.txt");
    if (!puzzle_input) return 1;
    //Loop through the array to get each bitwise value and the memory addresses
    getline(puzzle_input, in, '\n');
    while (!puzzle_input.eof()) {
        bitmasks.push_back(in);
        vector<string> list;
        memAdresses.push_back(list);
        getline(puzzle_input, in, '\n');
        while (!puzzle_input.eof() && in.find("mem") != string::npos) {
            memAdresses.back().push_back(in);
            getline(puzzle_input, in, '\n');
        }
        if (puzzle_input.eof()) memAdresses.back().push_back(in);
    }
    //Print results to console
    result1 = sumOfVals(bitmasks, memAdresses);
    log(result1);
    result2 = sumOfVals2(bitmasks, memAdresses);
    log(result2);
    return 0;
}

long long int sumOfVals(const vector<string>& b, const vector<vector<string>>& m)
{
    /*
        Precond: b is of type const vector<string>&, and stores the bitmask values, m is of type const vector<vector<string>>&, and stores the values of each memory address.
        Postcond: The bitmask for each memory value modifies bits, and stores the new value at it's respective memory address. After this has been completed, the sum of these values is
        returned.
    */
    unordered_map<string, long long int> mem;
    long long int sum = 0;
    //Loop through all memory adress values, perform bitmask operation, and set memory adress equal to new value
    for (int i = 0; i < m.size(); i++) {
        //Initialize bitmask
        string line = b.at(i), bitmask;
        bitmask = line.substr(line.find(' ', 5)+1, 36);
        for (int j = 0; j < m.at(i).size(); j++) {
            //Initialize val and address
            int val;
            string line2 = m.at(i).at(j), address, val_s, val_b;
            address = line2.substr(4, line2.find("]")-4);
            int valStart = line2.find(" ")+3;
            val_s = line2.substr(valStart, line2.length()-valStart);
            stringstream stream(val_s);
            stream >> val;
            //Convert value to binary, perform bitmask operation, convert back to decimal, and store value at address in m
            val_b = intToBin(val);
            performBitmask(bitmask, val_b);
            mem[address] = binToLong(val_b);
        }
    }
    //Sum up all the values
    for (auto itr = mem.begin(); itr != mem.end(); itr++) {
        sum += itr->second;
    }
    return sum;
}

long long int sumOfVals2(const vector<string>& b, const vector<vector<string>>& m)
{
    /*
        Precond: b is of type const vector<string>&, and stores the bitmask values, m is of type const vector<vector<string>>&, and stores the values of each memory address.
        Postcond: The bitmask for each memory adress generates the new memory adresses, and stores the value at each of these new adresses. After this has been completed,
        the sum of these values is returned.
    */
    unordered_map<string, int> mem;
    long long int sum = 0;
    //Loop through all memory adresses, perform bitmask operation, and set each new memory adresses value equal to the value stored at the original memory adress
    for (int i = 0; i < m.size(); i++) {
        //Initialize bitmask
        string line = b.at(i), bitmask;
        bitmask = line.substr(line.find(' ', 5)+1, 36);
        for (int j = 0; j < m.at(i).size(); j++) {
            //Initialize val and address
            int val, add;
            string line2 = m.at(i).at(j), address, address_b, val_s;
            address = line2.substr(4, line2.find("]")-4);
            int valStart = line2.find(" ")+3;
            val_s = line2.substr(valStart, line2.length()-valStart);
            stringstream stream(address), stream2(val_s);
            stream >> add;
            stream2 >> val;
            //Convert address to binary, perform bitmask operation, and generate new addresses, initializing each to val
            address_b = intToBin(add);
            performBitmask2(bitmask, address_b);
            genAddresses(address_b, mem, val);
        }
    }
    //Sum up all the values
    for (auto itr = mem.begin(); itr != mem.end(); itr++) {
        sum += itr->second;
    }
    return sum;
}

string intToBin(int val)
{
    /*
        Precond: val is of type int, and is a positive integer.
        Postcond: A 36-bit binary representation of val is returned.
    */
    string b;
    while (val != 0) {
        int bit_i;
        string bit;
        //Get bit, convert to string, and append to b string.
        bit_i = val % 2;
        stringstream stream;
        stream << bit_i;
        bit = stream.str();
        b = bit + b;
        //Divide val by 2
        val /= 2;
    }
    int len = b.length();
    //Append additional 0 to front to make 36-bit binary digit
    for (int i = 0; i < 36 - len; i++) {
        b = "0" + b;
    }
    return b;
}

void performBitmask(const string& bitmask, string& val)
{
    /*
        Precond: bitmask is of type const string&, and is the mask. val is of type string&, is the value that will be modified.
        Postcond: val is updated after bitmask overrides the bits in val.
    */
    for (int i = 0; i < 36; i++) {
        //Bitmask overrides bite if the mask at i is not the same as val at i [and bitmask[i] != 'X']
        if (bitmask[i] != 'X' && bitmask[i] != val[i]) val[i] = bitmask[i];
    }
}

long long int binToLong(const string& s)
{
    /*
        Precond: s is of type const string&, and stores the 36-bit binary string.
        Postcond: s is converted into decimal, and returned as a long long int.
    */
    long long int x = 0;
    for (int i = 0, j = 35; i < 36; i++, j--) {
        int bit = s[i] - '0';
        x += bit * pow(2, j);
    }
    return x;
}

void performBitmask2(const string& bitmask, string& address)
{
    /*
        Precond: bitmask is of type const string&, and is the mask. address is of type string&, is the address that will be modified.
        Postcond: A memory address consisting of x, 0, and 1 is generated, and replaces the one stored in string address.
    */
    for (int i = 0; i < 36; i++) {
        //If the value of bitmask[i] is 1 or x, the value in address is overriden to this value
        if (bitmask[i] == '1' || bitmask[i] == 'X') address[i] = bitmask[i];
    }
}

void genAddresses(string address, unordered_map<string, int>& mem, int val)
{
    /*
        Precond: address is of type const string&, and stores the address after mainpulated by the bitmask. mem is of type unordered_map<string, int>&, and stores
        the map of all memory addresses and their values. val is of type int, and is the value of each memory address.
        Postcond: Given the mainpulated address, many new memory addresses are generated, added to mem, with values of val.
    */
    int xpos = address.find("X");
    //Base Case: address consists of no x values, meaning it is a complete memory address
    if (xpos == string::npos) mem[address] = val;
    //Recursive Case: address consists of some x values, meaning at least 2 more memory addresses can be generated
    else {
        address[xpos] = '0';
        genAddresses(address, mem, val);
        address[xpos] = '1';
        genAddresses(address, mem, val);
    }
}

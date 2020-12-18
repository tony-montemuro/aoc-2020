//Programmer: Anthony Montemuro
//Date: 12/18/2020
//Description: Solution to Day 16 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

#define log(x) cout << #x << " " << x << endl;
#define readFile() getline(puzzle_input, line, '\n');
#define skipLines(n) for (int i = 0; i < n; i++) readFile();

int* getRanges(string s);
long long int productOfDepartureFields2(const vector<string>& fields, vector<int*> ranges, const vector<string>& tickets);
int stringToInt(string s);
int errorRate(const vector<int*>& ranges, vector<string>& tickets);
int* getTicketValues(string s);
int determineCol(int n, const vector<bool>& v);
int getValidCol(const vector<int>& v);
bool finished(const vector<vector<int>>& v);

int main()
{
    //Declare variables
    ifstream puzzle_input;
    string line;
    vector<string> tickets, fields;
    vector<int*> ranges;
    //Open file - if unsuccessful, return 1
    puzzle_input.open("puzzleInput.txt");
    if (!puzzle_input) return 1;
    //Gather data from the puzzle input
    //First, gather all field rules
    readFile();
    while (line != "")
    {
        int split = line.find(":");
        string field = line.substr(0, split);
        split+=2;
        string range_s = line.substr(split, line.length()-split);
        fields.push_back(field);
        ranges.push_back(getRanges(range_s));
        readFile();
    }
    //Next, gather my ticket, which will be stored in the 0-th element of tickets vector
    skipLines(2);
    tickets.push_back(line);
    skipLines(3);
    //Finally, gather the remaining tickets
    while (!puzzle_input.eof()) {
        tickets.push_back(line);
        readFile();
    }
    tickets.push_back(line);
    //Print results to console
    int result1 = errorRate(ranges, tickets);
    log(result1);
    long long int result2 = productOfDepartureFields2(fields, ranges, tickets);
    log(result2);
    //Delete dynamic memory
    for (int i = 0; i < ranges.size(); i++) {
        delete[] ranges.at(i);
    }
    return 0;
}

int errorRate(const vector<int*>& ranges, vector<string>& tickets)
{
    /*
        Precond: fields is of type const unordered_map<string, string>&, and stores each fields valid range values, tickets is of type vector<string>&,
        and stores my ticket at position 0, and the tickets of the nearby passangers in the other positions.
        Postcond: The ticket scanning error rate is returned, which is the sum of all invalid values (not within the range defined by the rules). Also,
        tickets with invalid fields are removed from the list of tickets.
    */
    //Declare variables
    vector<int> invalidTickets;
    int errRate = 0;
    //Loop through each ticket, and sum up all the invalid values into errorRate
    //First loop: run through each ticket
    for (int i = 0; i < tickets.size(); i++) {
        int* ticketValues = getTicketValues(tickets.at(i));
        //Second Loop: Run through each individual value
        bool isValid = true;
        for (int j = 0; j < 20; j++) {
            int ticketValue = ticketValues[j];
            //Third Loop: Check to make sure ticketValue is within at least one of the ranges
            int k;
            for (k = 0; k < 20; k++) {
                //If the ticket is within a valid range, it is a valid ticket, meaning errorRate does not increment
                if ((ticketValue >= ranges.at(k)[0] && ticketValue <= ranges.at(k)[1]) || (ticketValue >= ranges.at(k)[2] && ticketValue <= ranges.at(k)[3])) {
                    break;
                }
            }
            //If ticket is not found to be valid, increment errRate by ticketValue
            if (k == 20) {
                errRate += ticketValue;
                isValid = false;
            }
        }
        //If a ticket is determined to be invalid, mark it as such
        if (!isValid) invalidTickets.push_back(i);
        //Delete dynamic memory
        delete[] ticketValues;
    }
    //Remove all invalid tickets
    for (int i = 0; i < invalidTickets.size(); i++) {
        tickets.erase(tickets.begin()+invalidTickets.at(i)-i);
    }
    return errRate;
}

long long int productOfDepartureFields2(const vector<string>& fields, vector<int*> ranges, const vector<string>& tickets) {
    //Declare variables
    long long int product = 1;
    int cols = 0;
    unordered_map<string, long long int> map;
    vector<int*> colsVect;
    vector<vector<int>> lists;
    int* myTicket = getTicketValues(tickets.at(0));
    //Initialize colsVect and lists
    for (int i = 0; i < tickets.size(); i++) {
        int* ticket = getTicketValues(tickets.at(i));
        colsVect.push_back(ticket);
        vector<int> list;
        lists.push_back(list);
    }
    //Find each field that cannot be valid for each column
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < colsVect.size(); j++) {
            int val = colsVect.at(j)[i];
            for (int k = 0; k < 20; k++) {
                int lower1 = ranges.at(k)[0], upper1 = ranges.at(k)[1], lower2 = ranges.at(k)[2], upper2 = ranges.at(k)[3];
                if ((val < lower1 || val > upper1 && val < lower2 || val > upper2)) lists.at(i).push_back(k);
            }
        }
    }
    while (!finished(lists)) {
        int validCol, colNum;
        //First, sort each list
        for (int i = 0; i < 20; i++) {
            sort(lists.at(i).begin(), lists.at(i).end());
        }
        //Next, find the column who has 19 invalid fields. This allows you to figure out the valid field.
        for (int i = 0; i < 20; i++) {
            if (lists.at(i).size() == 19) {
                validCol = getValidCol(lists.at(i));
                lists.at(i).push_back(validCol);
                colNum = i;
                break;
            }
        }
        //Map the valid field to it's correct colNum
        map[fields.at(validCol)] = colNum;
        //Push back the valid column number to all other columns who have not been figured out yet
        for (int i = 0; i < 20; i++) {
            if (lists.at(i).size() != 20) {
                lists.at(i).push_back(validCol);
            }
        }
    }
    //Determine the product
    string depArr[6] = {"departure location", "departure station", "departure platform", "departure track", "departure date", "departure time"};
    for (int i = 0; i < 6; i++) {
        product *= myTicket[map[depArr[i]]];
    }
    //Deallocate dymamic memory
    delete[] myTicket;
    for (int i = 0; i < colsVect.size(); i++) {
        delete[] colsVect.at(i);
    }
    return product;
}

bool finished(const vector<vector<int>>& v) {
    /*
        Precond: v is of type const vector<vector<int>>&, and stores the list of lists of invalid columns.
        Postcond: If all valid columns have been determine, meaning each list has a size of 20, return true. Otherwise, return false.
    */
    for (int i = 0; i < 20; i++) {
        if (v.at(i).size() != 20) return false;
    }
    return true;
}

int getValidCol(const vector<int>& v) {
    /*
        Precond: v is of type const vector<int>&, and is a list of sorted integers with a length of 19.
        Postcond: The missing number in the list is returned.
    */
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i) != i) return i;
    }
    return 19;
}

int* getRanges(string s) {
    /*
        Precond: s is of type string, and stores the date for the ranges.
        Postcond: This function converts the string value into 4 range values: range[0] = lower range 1, range[1] = upper range 1, range[2] = lower range 2, range[3] = upper range 3
    */
    int* range = new int[4];
    int split = s.find("-"), temp;
    range[0] = stringToInt(s.substr(0, split));
    temp = split+1;
    split = s.find(" ", temp);
    range[1] = stringToInt(s.substr(temp, split-temp));
    temp = s.find(" ", split+1)+1;
    split = s.find("-", temp);
    range[2] = stringToInt(s.substr(temp, split-temp));
    temp = split+1;
    range[3] = stringToInt(s.substr(temp, s.length()-temp));
    return range;
}

int* getTicketValues(string s) 
{
    /*
        Precond: s is of type string, and represents someones ticket.
        Postcond: This function converts this string into an integer array, and returns this array.
    */
    int* tickets = new int[20];
    int lower = 0, upper;
    for (int i = 0; i < 19; i++) {
        upper = s.find(",", lower+1);
        tickets[i] = stringToInt(s.substr(lower, upper-lower));
        lower = upper+1;
    }
    tickets[19] = stringToInt(s.substr(lower, s.length()-lower));
    return tickets;
}

int stringToInt(string s)
{
    /*
        Precond: s is of type string, which represents an integer.
        Postcond: Converts s to string, and returns the integer.
    */
    int x;
    stringstream stream(s);
    stream >> x;
    return x;
}

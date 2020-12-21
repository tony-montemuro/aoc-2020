//Programmer: Anthony Montemuro
//Date: 12/20/2020
//Description: Cleaned up Solution to Day 1 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#define logLine(x) std::cout << x << std::endl;

class ExpenseReport {
    private:
        std::vector<int> input;
    public:
        //Constructor
        ExpenseReport() {
            //Open file for reading
            std::ifstream in;
            in.open("puzzleInput.txt");
            if (!in) logLine("Error on file opening!");
            //Parse the input, and store each number in vector input
            while (!in.eof()) {
                std::string s;
                int i;
                in >> s;
                std::stringstream stream(s);
                stream >> i;
                input.push_back(i);
            }
            //Close file
            in.close();
        }
        //Methods
        //Solution to Part 1
        int productOfTwoEntries() {
            //Find the two numbers (i, j) that sum to 2020, and return the product
            for (int i = 0; i < input.size()-1; i++) {
                for (int j = i+1; j < input.size(); j++) {
                    if (input.at(i) + input.at(j) == 2020) return input.at(i) * input.at(j);
                }
            }
        }
        //Solution to Part 2
        int productOfThreeEntries() {
            //Find the three numbers (i, j, k) that sum to 2020, and return the product
            for (int i = 0; i < input.size()-2; i++) {
                for (int j = i+1; j < input.size()-1; j++) {
                    for (int k = j+1; k < input.size(); k++) {
                        if (input.at(i) + input.at(j) + input.at(k) == 2020) return input.at(i) * input.at(j) * input.at(k);
                    }
                }
            }
        }
};

void day1() {
    //Log solutions to day 1 to console
    ExpenseReport myExpenseReport;
    std::cout << myExpenseReport.productOfTwoEntries() << std::endl;
    std::cout << myExpenseReport.productOfThreeEntries() << std::endl;
}

int main() {
    day1();
    return 0;
}

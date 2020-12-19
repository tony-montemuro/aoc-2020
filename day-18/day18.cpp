//Programmer: Anthony Montemuro
//Date: 12/18/2020
//Description: Solution to Day 18 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;

#define log(x) cout << #x << " " << x << endl;

long long int sumOfProblems(const vector<string>& v, bool isAdvanced);
string infixToPostfix(string infix, bool isAdvanced);
long long int postExp(string s, bool isAdvanced);

int main()
{
    //Declare variables
    ifstream puzzle_input;
    vector<string> problems;
    //Open file - if not found, return 1
    puzzle_input.open("puzzleInput.txt");
    if (!puzzle_input) return 1;
    //Loop through file, and store each problem in vector problems
    while (!puzzle_input.eof()) {
        string s;
        getline(puzzle_input, s, '\n');
        //Erase all spaces
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        problems.push_back(s);
    }
    long long int result1 = sumOfProblems(problems, false);
    log(result1);
    long long int result2 = sumOfProblems(problems, true);
    log(result2);
    return 0;
}

long long int sumOfProblems(const vector<string>& v, bool isAdvanced)
{
    /*
        Precond: v is of type const vector<string>&, and stores the list of homework problems. isAdvanced is of type bool, and determines whether or not
        to solve the problems using expression precedence or not.
        Postcond: The sum of all the answers to the questions is returned.
    */
    long long int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += postExp(v.at(i), isAdvanced);
    }
    return sum;
}

string infixToPostfix(string infix, bool isAdvanced)
{
    /*
        Precond: infix is of type string, and is a mathematical expression consisting of numbers, operators * and +, and parathesis, in infix order.
        isAdvanced is of type bool, and determines whether or not to solve the problems using expression precedence or not.
        Postcond: The expression is converted from infix order to postfix order. If isAdvanced is true, include precedence of operations.
    */
    string postfix;
    stack<char> s;
    for (int i = 0; i < infix.length(); i++) {
        //If infix i is a number, push into postfix
        if (isdigit(infix[i])) {
            postfix += infix[i];
        }
        //If infix i is an open paranthesis, push it into stack
        else if (infix[i] == '(') {
            s.push(infix[i]);
        }
        //If infix i is a closing paranthesis, pops all operators that appear before the first open paranthesis and pushes them into postfix.
        //If infix i is + or *, different things will occur whether isAdvanced is true or not. Current operator is always pushed into the stack.
        else {
            if (infix[i] == ')') {
                while (s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
            }
            else {
                //If not considering operator precedence, if the top of the stack is not a parenthesis, the top of stack is popped and pushed into
                //postfix, and the current operator is pushed into stack.
                if (!isAdvanced) {
                    if (!s.empty() && s.top() != '(') {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
                //If considering operator precedence, if the top of the stack is plus, the top of the stack is popped and pushed into postfix, and the current operator is
                //pushed into stack. Otherwise, simply push current operator into stack.
                else {
                    if (!s.empty() && s.top() == '+') {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }    
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

long long int postExp(string s, bool isAdvanced)
{
    /*
        Precond: s is of type string, and represents a mathematical expression in infix order.
        Postcond: The expression is converted to postfix order so that it can be easily solved, and the result is returned.
    */
    string postfix = infixToPostfix(s, isAdvanced);
    stack<long long int> st;
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] == '+') {
            long long int sum = st.top();
            st.pop();
            sum += st.top();
            st.pop();
            st.push(sum);
        }
        else if (postfix[i] == '*') {
            long long int prod = st.top();
            st.pop();
            prod *= st.top();
            st.pop();
            st.push(prod);
        }
        else {
            st.push(postfix[i] - '0');
        }
    }
    return st.top();
}

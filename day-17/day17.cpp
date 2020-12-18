//Programmer: Anthony Montemuro
//Date: 12/18/2020
//Description: Solution to Day 17 in Advent of Code 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define log(x) cout << #x << " " << x << endl;

int simulateBoot(vector<string> v);
int simulateBoot_4d(vector<string> v);
int numOfActive(const vector<vector<vector<string>>>& hyperspace, int a, int z, int x, int y);
int numOfActive_space(const vector<vector<string>>& space, int z, int x, int y, bool isMiddle);
int numOfActive_plane(const vector<string>& plane, int x, int y, bool isMiddle);

int main()
{
    //Declare variables
    ifstream puzzle_input;
    vector<string> v;
    //Open file - if unsuccessful, return 1
    puzzle_input.open("puzzleInput.txt");
    if (!puzzle_input) return 1;
    //Push puzzle input into vector v
    while (!puzzle_input.eof()) {
        string s;
        puzzle_input >> s;
        v.push_back(s);
    }
    //Print results to console
    int result1 = simulateBoot(v);
    log(result1);
    int result2 = simulateBoot_4d(v);
    log(result2);
    return 0;
}

int simulateBoot(vector<string> v)
{
    /*
        Precond: v is of type vector<string>, and stores the initial state of the cubes.
        Postcond: A six cycle boot-process is simulated on the initial state, and the number of active cubes (#) is returned.
    */
    //Setup space
    vector<vector<string>> space;
    vector<string> emptyPlane;
    string inactiveRow, dots = "..";
    for (int i = 0; i < v.at(0).length()+4; i++) {
        inactiveRow += ".";
    }
    for (int i = 0; i < 2; i++) {
        v.insert(v.begin(), inactiveRow);
        v.push_back(inactiveRow);
    }
    for (int i = 2; i < v.size()-2; i++) {
        v.at(i) = dots + v.at(i) + dots;
    }
    for (int i = 0; i < v.size(); i++) {
        emptyPlane.push_back(inactiveRow);
    }
    space.push_back(emptyPlane);
    space.push_back(emptyPlane);
    space.push_back(v);
    space.push_back(emptyPlane);
    space.push_back(emptyPlane);
    //Perform simulation 6 times
    vector<vector<string>> newSpace;
    int ctr;
    for (int a = 0; a < 6; a++) {
        ctr = 0;
        for (int i = 1; i < space.size()-1; i++) {
            vector<string> newPlane;
            newPlane.push_back(inactiveRow);
            for (int j = 1; j < space.at(i).size()-1; j++) {
                string s = ".";
                for (int k = 1; k < space.at(i).at(j).length()-1; k++) {
                    int n = numOfActive_space(space, i, k, j, true);
                    if (space.at(i).at(j)[k] == '#') {
                        //Case 1: Current cube is active, and 2 or 3 of it's neighbors are active.
                        if (n == 2 || n == 3) {
                            s += '#';
                            ctr++;
                        }
                        //Case 2: Current cube is active, and less than 2 or more than 3 of it's neighbors are active.
                        else {
                            s += ".";
                        }
                    }
                    else {
                        //Case 3: Current cube is inactive, and exactly 3 of it's neighbors are also active.
                        if (n == 3) {
                            s += "#";
                            ctr++;
                        }
                        //Case 4: Current cube is inactive, and less than 3 or greater than 3 of it's neighbors are also active.
                        else {
                            s += ".";
                        }
                    }
                }
                s += ".";
                newPlane.push_back(s);
            }
            newPlane.push_back(inactiveRow);
            newSpace.push_back(newPlane);
        }
        //Setup space for next iteration
        inactiveRow += dots;
        for (int i = 0; i < newSpace.size(); i++) {
            newSpace.at(i).insert(newSpace.at(i).begin(), inactiveRow);
            newSpace.at(i).push_back(inactiveRow);
            for (int j = 1; j < newSpace.at(i).size()-1; j++) {
                newSpace.at(i).at(j) = "." + newSpace.at(i).at(j) + ".";
            }
        }
        emptyPlane.clear();
        for (int i = 0; i < newSpace.at(0).size(); i++) {
            emptyPlane.push_back(inactiveRow);
        }
        for (int i = 0; i < 2; i++) {
            newSpace.insert(newSpace.begin(), emptyPlane);
            newSpace.push_back(emptyPlane);
        }
        space = newSpace;
        newSpace.clear();
    }
    return ctr;
}

int simulateBoot_4d(vector<string> v)
{
    /*
        Precond: v is of type vector<string>, and stores the initial state of the cubes.
        Postcond: A six cycle boot-process is simulated on the initial state, and the number of active cubes (#) is returned.
    */
    //Setup hyperspace
    string emptyRow, dots = "..";
    vector<string> emptyPlane;
    vector<vector<string>> emptySpace, initialSpace;
    vector<vector<vector<string>>> hyperspace;
    //Initialize emptyRow
    for (int i = 0; i < v.at(0).length()+4; i++) {
        emptyRow += ".";
    }
    //Initialize v
    for (int i = 0; i < 2; i++) {
        v.insert(v.begin(), emptyRow);
        v.push_back(emptyRow);
    }
    for (int i = 2; i < v.size()-2; i++) {
        v.at(i) = dots + v.at(i) + dots;
    }
    //Initialize emptyPlane
    for (int i = 0; i < v.size(); i++) {
        emptyPlane.push_back(emptyRow);
    }
    //Initialize emptySpace
    for (int i = 0; i < 5; i++) {
        emptySpace.push_back(emptyPlane);
    }
    //Initialize initialState
    initialSpace.push_back(emptyPlane);
    initialSpace.push_back(emptyPlane);
    initialSpace.push_back(v);
    initialSpace.push_back(emptyPlane);
    initialSpace.push_back(emptyPlane);
    //Initialize hyperspace
    hyperspace.push_back(emptySpace);
    hyperspace.push_back(emptySpace);
    hyperspace.push_back(initialSpace);
    hyperspace.push_back(emptySpace);
    hyperspace.push_back(emptySpace);
    //Run simulation 6 times
    vector<vector<vector<string>>> newHyperspace;
    int ctr;
    for (int a = 0; a < 6; a++) {
        ctr = 0;
        for (int i = 1; i < hyperspace.size()-1; i++) {
            vector<vector<string>> newSpace;
            newSpace.push_back(emptyPlane);
            for (int j = 1; j < hyperspace.at(i).size()-1; j++) {
                vector<string> newPlane;
                newPlane.push_back(emptyRow);
                for (int k = 1; k < hyperspace.at(i).at(j).size()-1; k++) {
                    string s = ".";
                    for (int l = 1; l < hyperspace.at(i).at(j).at(k).length()-1; l++) {
                        int n = numOfActive(hyperspace, i, j, l, k);
                        if (hyperspace.at(i).at(j).at(k)[l] == '#') {
                            //Case 1: Current cube is active, and 2 or 3 of it's neighbors are active.
                            if (n == 2 || n == 3) {
                                s += '#';
                                ctr++;
                            }
                            //Case 2: Current cube is active, and less than 2 or more than 3 of it's neighbors are active.
                            else {
                                s += ".";
                            }
                        }
                        else {
                            //Case 3: Current cube is inactive, and exactly 3 of it's neighbors are also active.
                            if (n == 3) {
                                s += "#";
                                ctr++;
                            }
                            //Case 4: Current cube is inactive, and less than 3 or greater than 3 of it's neighbors are also active.
                            else {
                                s += ".";
                            }
                        }
                    }
                    s += ".";
                    newPlane.push_back(s);
                }
                newPlane.push_back(emptyRow);
                newSpace.push_back(newPlane);
            }
            newSpace.push_back(emptyPlane);
            newHyperspace.push_back(newSpace);
        }
        //Setup hyperspace for next simulation
        //Initialize emptyRow
        emptyRow += "..";
        //Pad each plane
        for (int i = 0; i < newHyperspace.size(); i++) {
            for (int j = 0; j < newHyperspace.at(i).size(); j++) {
                newHyperspace.at(i).at(j).insert(newHyperspace.at(i).at(j).begin(), emptyRow);
                newHyperspace.at(i).at(j).push_back(emptyRow);
                for (int k = 1; k < newHyperspace.at(i).at(j).size(); k++) {
                    newHyperspace.at(i).at(j).at(k) = "." + newHyperspace.at(i).at(j).at(k) + ".";
                }
            }
        }
        //Initialize new emptyPlane
        emptyPlane.clear();
        for (int i = 0; i < newHyperspace.at(0).at(0).size(); i++) {
            emptyPlane.push_back(emptyRow);
        }
        //Pad each space
        for (int i = 0; i < newHyperspace.size(); i++) {
            for (int j = 0; j < 2; j++) {
                newHyperspace.at(i).insert(newHyperspace.at(i).begin(), emptyPlane);
                newHyperspace.at(i).push_back(emptyPlane);
            }
        }
        //Initialize new emptySpace
        emptySpace.clear();
        for (int i = 0; i < newHyperspace.at(0).size(); i++) {
            emptySpace.push_back(emptyPlane);
        }
        //Pad the hyperspace
        for (int i = 0; i < 2; i++) {
            newHyperspace.insert(newHyperspace.begin(), emptySpace);
            newHyperspace.push_back(emptySpace);
        }
        hyperspace = newHyperspace;
        newHyperspace.clear();
    }
    return ctr;
}

int numOfActive(const vector<vector<vector<string>>>& hyperspace, int a, int z, int x, int y)
{
    /*
        Precond: hyperspace is of type vector<vector<vector<string>>>&, and stores a hyperspace of cubes. a, z, x, y are all of type int.
        Each represents a different coordinate axis.
        Postcond: The number of active cubes surrounding the current cube in hyperspace is returned.
    */
    int n = 0;
    n += numOfActive_space(hyperspace.at(a-1), z, x, y, false);
    n += numOfActive_space(hyperspace.at(a), z, x, y, true);
    n += numOfActive_space(hyperspace.at(a+1), z, x, y, false);
    return n;
}

int numOfActive_space(const vector<vector<string>>& space, int z, int x, int y, bool isMiddle)
{
    /*
        Precond: Space is of type vector<vector<string>>, which stores a three-dimensional space of active and inactive cubes. z, x, y are all of type int.
        Each represents a different coordinate axis.
        Postcond: The number of active cubes surrounding the current cube in space is returned.
    */
    int n = 0;
    n += numOfActive_plane(space.at(z-1), x, y, false);
    if (isMiddle) {
       n += numOfActive_plane(space.at(z), x, y, true);
    } else {
        n += numOfActive_plane(space.at(z), x, y, false);
    }
    n += numOfActive_plane(space.at(z+1), x, y, false);
    return n;
}

int numOfActive_plane(const vector<string>& plane, int x, int y, bool isMiddle)
{
    /*
        Precond: Plane is of type const vector<string>&, and represents a plane of cubes. j and k are of type int, which store the x and y position. isMiddle is of type
        bool, and stores whether or not this particular plane contains the cube being checked.
        Postcond: The number of active cubes in the plane is returned.
    */
    int n = 0;
    for (int i = x; i < x+3; i++) {
        if (plane.at(y-1)[i-1] == '#') n++;
    }
    if (isMiddle) {
        if (plane.at(y)[x-1] == '#') n++;
        if (plane.at(y)[x+1] == '#') n++;
    } else {
        for (int i = x; i < x+3; i++) {
            if (plane.at(y)[i-1] == '#') n++;
        }
    }
    for (int i = x; i < x+3; i++) {
        if (plane.at(y+1)[i-1] == '#') n++;
    }
    return n;
}

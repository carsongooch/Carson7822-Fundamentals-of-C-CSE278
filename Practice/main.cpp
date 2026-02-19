// Not homework or class related purley for 
// sharpening C++ skills.
// Copyright Carson Gooch


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cctype>



using namespace std;

int main() {
    // problem one
    int a = 5;
    int b = 10;
    int sum = a + b;

    cout << sum << endl;

    // problem 2 even or odd
    int x = 42;
    if (x % 2 == 0) {
        cout << "true" << endl;
    }

    // problem 3 length of string
    string s = "Hello my name is bob";
    int length = s.length();
}


// methods
// is even?
bool isEven(int n) {
    if (n % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

// swap ints
void swapInts(int& a, int& b) {
    int temp = a;
    b = temp;
    a = b;
}

// default parm
void greet(string name = "World") {
    cout << "Hello, " << name << endl;
}

// find largest value in a vector
int findLargest(const vector<int>& nums) {
    int largest = nums[0];
    for (int n : nums) {
        if (n > largest) {
            largest = n;
        }
    }
    return largest;
}

//Fill in the method to read all lines of a text file into a vector of strings.
vector,string. readLines(const string& filename) {
    vector<string> lines;
    ifstream inFile(filename);
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }



    return lines;
}
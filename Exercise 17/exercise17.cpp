/* 
 * File:   exercise17.cpp
 * Author: Carson Gooch
 * Copyright goochcj@miamioh.edu 2025
 *
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// A pre-defined constant that indicates the last-sentinel value in 
// a given list/array.
const unsigned LastValue = -1U;

/** Method to print the numbers in a given list/array of values. The
 * last value in the list will be -1 -- e.g., {1, 2, 3, -1U}. 
 * 
 * Note: Instead of -1 use LastValue (a named constant) in your code
 *
 * @param ptr Pointer to the first number in the list/array 
 */
void print(const unsigned *ptr) {
    if (ptr == nullptr) {
        return;
    }
    // Implement rest of the method here.

    for (; *ptr != LastValue; ptr++) {
        cout << *ptr << endl;
    }
}

/**
 * Method to find the minimum value (other than LastVal) in a given list/array
 * of values. The last entry in the list will be -1U
 * 
 * Note: Instead of -1 use LastValue (a named constant) in your code
 * 
 * @param ptr Pointer to the first element in a list/array 
 * @return  The smallest value in the list
 */
unsigned findMin(const unsigned *ptr) {
    unsigned minValue = *ptr;
    for (; *ptr != LastValue; ptr++) {
        if (*ptr < minValue) {
            minValue = *ptr;
        }
    }
    return minValue;
}

/** Insert a value at a given position with the last-but-one number
 * being removed from the list. The last number should continue to
 * remain -1.  For example, if ptr is pointing to {1, 2, 3, -1} and
 * val is 4, the resulting list should be {4, 1, 2, -1}.
 * 
 * Note: Instead of -1 use LastValue (a named constant) in your code
 * 
 * Note: This method is under 6 lines of code, when done right.
 * 
 * @param ptr Pointer to list of numbers to be modified.
 * 
 * @param val The value to be inserted in the first position.
 */
void insert(unsigned *ptr, unsigned val) {
    unsigned prev = val;
    for (; *ptr != LastValue; ptr++) {
        unsigned tempVar = *ptr;
        *ptr = prev;
        prev = tempVar;
    }
}

/** Convert a 1-D list to a 2-D ragged array of numbers. For example 
 * given a list of numbers: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
 * this method should setup sublist as:
 * 
 * subList[0] = {1, 2, 3, -1}
 * subList[1] = {5, 6, -1}
 * subList[3] = {8, -1}
 * 
 * Notes: Instead of -1 use LastValue (a named constant) in your code
 *      : Use (list + n) to get pointer to nth element
 *      : Use (subList + n) to get pointer to nth element
 * 
 * @param list The list of numbers to be redistributed to a 2-d ragged
 * array.
 * 
 * @param subList A sublist with exactly 3 entries 
 */
void distribute(unsigned* list, unsigned** subList) {
    // Simple assignment statements is sufficient for this problem.
    // Don't write loops etc. Don't forget to set -1s at appropriate
    // spots in list to logically end each subList
    *subList = list;
    *(list + 3) = LastValue;
    *(subList + 1) = list + 4;
    *(list + 6) = LastValue;
    *(subList + 2) = list + 7;
    *(list + 8) = LastValue;
}

//----------------------------------------------------------------------
//       DO  NOT  MODIFY  CODE  BELOW  THIS  LINE. BUT STUDY IT
//----------------------------------------------------------------------

// A convenience shortcut for a vector of integers
using NumVec = std::vector<unsigned>;

/** Helper method to load numbers from a given input file.
 * 
 * This is a convenience method to load numbers from a given data file.
 * If the file could not be read, this method throws an exception.
 * 
 * @param[in] filePath The path to the file to be modified.
 * 
 * @return The list of numbers loaded from the specified file.
 */
NumVec load(const std::string& filePath) {
    std::ifstream data(filePath);
    if (!data.good()) {
        throw std::runtime_error("Unable to open " + filePath);
    }

    // Load numbers into a vector using stream iterators
    std::istream_iterator<unsigned> in(data), eof;
    // Create and return list of numbers back to the caller
    return NumVec(in, eof);
}

/*
 * The main method that coordinates the testing operations in this
 * class.
 * 
 * @param[in] argc The number of command-line arguments for main
 * 
 * @param[in] argv The actual command-line arguments. The first argument 
 * must be path to a file with numbers in it.
 *
 */
int main(int argc, char** argv) {
    // Check and load data from data file.
    const std::string fileName = (argc > 1 ? argv[1] : 
        "'You have not specified a valid file as command-line argument'");
    NumVec numList = load(fileName);
    // Get pointer to numbers for convenience reference below
    unsigned *numbers = numList.data();

    // Print the numbers loaded
    std::cout << "Testing print method:\n";
    print(numbers);

    // Print the minimum value in the list
    const unsigned min = findMin(numbers);
    std::cout << "Testing findMin method:\n";
    std::cout << "Minimum value: " << min << std::endl;

    // Insert a value at a given location.
    std::cout << "Testing insert method:\n";
    insert(numbers + 3, 101);
    print(numbers);

    // Test distribute method
    std::cout << "Testing distribute method:\n";
    unsigned* subList[3] = {nullptr, nullptr, nullptr};
    distribute(numbers, subList);
    std::cout << "subList[0]:\n"; print(subList[0]); 
    std::cout << "subList[1]:\n"; print(subList[1]);
    std::cout << "subList[2]:\n"; print(subList[2]);

    // All done
    return 0;
}

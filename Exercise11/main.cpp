/**
 * @file main.cpp
 * @author DJ Rao (dj@djrao.com)
 * @brief A top-level tester class to test 4 different methods
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include "Person.h"

// It is ok to use the following namespace delarations in C++ source
// files only. They must never be used in header files.
using namespace std;
using namespace std::string_literals;

// Prototype declarations 
std::vector<Person> get(const std::string& host, const std::string& path);
std::vector<std::string> findDuplicateNames(const std::vector<Person>& list);
float getTotalSalary(const std::unordered_map<int, Person>& list);

/**
 * @brief A simple helper method to unit test methods in the person class.
 * 
 */
void testPerson() {
    Person p1, p2(10, "test", 25);
    std::cout << p2.to_string() << std::endl;
    std::istringstream is("10\tMaddona\t100\n-2\t\"one two three\"\t-20.5");
    is >> p1 >> p2;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
}

void testGet(const std::string& host = "ceclnx01.cec.miamioh.edu",
    const std::string& path = "/~harveysd/exam1/persons.txt") {
    const std::vector<Person> list = get(host, path);
    for (const auto& per : list) {
        std::cout << per << std::endl;
    }
}

/** This is a simple list of person data for testing */
const std::vector<Person> list = 
{{9082, "Neha O\"Connor", 77000},
 {1023, "Vinay Rajan Desai", 68000},
 {2048, "Yang Ming Zhou", 71000},
 {357, "Emily Rose Thompson", 64000},
 {8765, "Anjali Mehta Kapoor", 76000},
 {4321, "Superman", 69000},
 {9982, "Neha O\"Connor", 72000},
 {567, "Kevin Daniel Roberts", 67000},
 {1208, "Xin Yue Li", 74000},
 {7854, "Siddharth Anil Choudhury", 63000},
 {3490, "Feng Lei Huang", 70000},
 {2208, "Xin Yue Li", 81000}};

void testFindDuplicates() {
    auto results = findDuplicateNames(list);
    std::sort(results.begin(), results.end());
    for (const auto& name : results) {
        std::cout << name << std::endl;
    }
}

/**
 * @brief A simple method for testing the total salary method.
 * 
 */
void testTotal() {
    std::unordered_map<int, Person> db;
    for (const auto& per : list) {
        db[per.getId()] = per;
    }
    std::cout << "Total salary = " << getTotalSalary(db) << std::endl;
}

/**
 * @brief Calls the different test methods in this class based on command-line
 * arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv The actual command-line arguments. The first argument is of the
 * form "q1", "q2", etc.
 * @return int This method always returns zero.
 */
int main(int argc, char *argv[]) {
    const std::string test = (argc > 1 ? argv[1] : "q2");
    if (test == "q1") {
        testPerson();
    } else if (test == "q2") {
        if (argc > 2) {
            testGet("ceclnx01.cec.miamioh.edu",
                "/~harveysd/exam1/persons_list.tsv");
        } else {
            testGet();
        }
    } else if (test == "q3") {
        testFindDuplicates();
    } else if (test == "q4") {
        testTotal();
    }
    return 0;
}

// End of source code

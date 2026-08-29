/**
 * @file practice_exam.cpp
 * @author your name (Carson Gooch)
 * @brief 
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <boost/asio.hpp>
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

// Convenience to refer to different methods
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

/**
 * @brief Returns a list of persons using data downloaded from a given
 * HTTP web-server.
 * 
 * This method must perform an GET request to obtain the data from the given
 * path. For example if the url is http://ceclnx01.cec.miamioh.edu/~raodm/exam1/persons.txt
 * the host will be "ceclnx01.cec.miamioh.edu" and path will be "/~raodm/exam1/persons.txt"
 * 
 * @param host The host name of the web-server. Example "ceclnx01.cec.miamioh.edu"
 * @param path The path to the file. Example "/~raodm/exam1/persons.txt"
 * 
 * @return std::vector<Person> The list of person objects returned by the
 * web-server.
 */
std::vector<Person> get(const std::string& host, 
                        const std::string& path) {
    std::vector<Person> persons;
    // Create a tcp socket to the host in order to make a GET request
    tcp::iostream sock(host, "80");
    
    sock << "GET " << path << " HTTP/1.1\r\n";
    sock << "Host: " << host << "\r\n";
    sock << "Connection: close\r\n\r\n";


    std::string line;
    while (std::getline(sock, line)) {
        if (line.empty() || line == "\r") {
            break;
        }
    }

    Person person;
    while (sock >> person) {
        persons.push_back(person);
    }
    
    // Remove this dummy return statement
    return persons;
}

/**
 * @brief Return list of duplicate names from a given list
 * 
 * For example if the list is:
 *     {{10, "Bob", 10}, {20, "Mary", 25.5}, {30, "Bob", 9.99}}
 * then this method must return the list
 *     {"Bob"}
 * 
 * \note Hint: Use unordered_map<std::string, int> to track 
 *       occurrences of each name. Of course, in the exams or
 *       job/internship interviews this hint will not be provided
 * 
 * @param list The list of persons to be search to find duplicate 
 * names.
 * 
 * @return std::vector<std::string> The list of duplicate names.
 */
std::vector<std::string>
findDuplicateNames(const std::vector<Person>& list) {
    std::unordered_map<std::string, int> countName;
    std::vector<std::string> duplicate;
    for (const Person& p : list) {
        countName[p.getName()]++;
    }

    for (const auto& entry : countName) {
        if (entry.second > 1) {
            duplicate.push_back(entry.first);
        }
    }

    return duplicate;
}

/**
 * @brief Get the Total Salary of all persons 
 * 
 * \note Hint: Extract salary from the string representation and use
 *       std::stof() to convert string-to-float.
 * 
 * @param list An unordered map of persons, with the id of the
 * person as the key
 * 
 * @return float The total salary of all persons in the list
 */
float
getTotalSalary(const std::unordered_map<int, Person>& list) {
    float total = 0; 
    for (const auto& entry : list) {
        std::string personString = entry.second.to_string();
        std::stringstream personStream(personString);
        int id;
        std::string name;
        float salary;
        personStream >> id;
        personStream >> std::quoted(name);
        personStream >> salary;
        total += salary;
    }

    return total;
}


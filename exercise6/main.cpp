/* 
 * File:   raodm_exercise6.cpp
 * Author: raodm
 *
 * Copyright (C) 2025 goochcj@miamioh.edu
 */

#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Person.h"

using namespace std;

// A shortcut to a map of People. The key into this map is the 
// Person's numeric ID
using PersonMap = std::unordered_map<int, Person>;

/**
 * Method to person entries from a given file into an 
 * unordered map.
 * 
 * @param filePath Path to the file from where data is to be read.
 * @return An unordered map containing the data.
 */
PersonMap load(const std::string& filePath) {
    // Create the entry for the file to be read
    std::ifstream data(filePath);
    if (!data.good()) {
        throw std::runtime_error("Unable to read file " + filePath);
    }
    // Create the map to be populated and returned
    PersonMap db;

    // Load person information into the DB by reading 
    // entry-by-entry and then add them to the unordered_map using
    // operator[].  Use the ID of the person as the key.
    Person per;  // temporary object
    while (data >> per) {
        db[per.getID()] = per;     
    }
    // Return the map of people back
    return db;
}

/**
 * Read ID and print information about a person, if the ID is valid.
 * 
 * This method uses the find method in unordered_map to quickly
 * find if the ID is valid. Note that the find method can be used
 * only to search based on the key/index (or "first") for the
 * unordered_map.  This method has O(1) time complexity!
 * 
 * @param db The unordered_map of people to be used by this method.
 */
void findPerson(const PersonMap& db) {
    // Prompt and obtain ID from the user.
    std::cout << "Enter ID: ";
    int id;
    std::cin >> id;
    // Ignore newline after reading an integer
    cin.ignore();

    if (db.find(id) != db.end()) {
        std::cout << db.at(id) << std::endl;
        return;
    } else {
        std::cout << "Sorry. Person with ID " << id << 
            " not found. ";
    }
}

/**
 * This method search for a given sub-string in all person entries
 * and prints matching entries. Since this method has to iterate
 * over each entry it has a O(n) time complexity.
 * 
 * @param db The unordered_map of people to be used by this method.
 */
void searchPerson(const PersonMap& db) {
    // Prompt and obtain info to search for.
    std::cout << "Enter info to search: ";
    std::string searchStr;  // Information to search for
    std::getline(std::cin, searchStr);
    // Search the full info of a person to see if data is in there.
    // use the range-based for loop (as discussed in lecture slides)!
    for (const auto& [id, person] : db) {
        std::string personInfo = to_string(person);
        if (personInfo.find(searchStr) != std::string::npos) {
            std::cout << personInfo << std::endl;
        }
    }
}
    // For each entry convert the value (i.e., second) for each element 
    // using the to_string method and then use std::string::find method 
    // to see if searchStr is a substring. If so, print the value.
/*
 * A simple main method to load and list of employees into a given 
 */
int main(int argc, char** argv) {
    // First load the person database from a given file.
    PersonMap db = load("person_db.txt");
    // Let the user search by ID
    findPerson(db);
    // Let the user search by ID once more (for testing)
    findPerson(db);
    // Let the user search based on some information
    searchPerson(db);
    // All one.
    return 0;
}

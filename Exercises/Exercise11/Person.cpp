/**
 * @file Person.cpp
 * @author Carson Gooch(goochcj@miamioh.edu)
 * @brief Implementation of methods in Person
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PERSON_CPP
#define PERSON_CPP

#include <iomanip>
#include <sstream>
#include <string>
#include "Person.h"

// Implement the different methods and operators in this source file
// Test the operations of this class first before proceeding with the
// rest of the questions.

Person::~Person() { 
}

Person::Person(const int id, const std::string& name, const float salary)
    : id(id), name(name), salary(salary) {
}

std::ostream& operator << (std::ostream& output, const Person& person) {
    output << person.id << " " << std::quoted(person.name) << " " 
        << person.salary;
    return output;
}

std::istream& operator >> (std::istream& input, Person& person) {
    input >> person.id >> std::quoted(person.name) >> person.salary;
    return input;
}

std::string Person::to_string() const {
    std::ostringstream output;
    output << id << " " << std::quoted(name) << " " << salary;
    return output.str();
}
#endif

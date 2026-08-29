/* 
 * File:   Person.cpp
 * Author: raodm
 * 
 * Copyright (C) 2025 goochcj@miamioh.edu
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Person.h"

// Note that the default values for parameters are set in header file.
// The values should not be repeated in the source file. Here you should
// code as-if you don't have default values -- i.e., code defensively.
Person::Person(int id, const std::string& name, 
               const std::string& email) : id(id), name(name), email(email) {
    // Notice how the instance variables are directly initialized. This is
    // the preferred way to initialize values in C++
}

// The destructor.
Person::~Person() {
    // Nothing to be done here for now.
}

// Stream insertion operator used to print a person's information.
std::ostream& operator<<(std::ostream& os, const Person& per) {
    // Implement this method to print id, name, and email for per.
    // For name and email used std::quoted to automatically add quotes
    // about them.

    std::ostream& operator<<(std::ostream& os, 
        const Person& per);

    os << per.id << " " << std::quoted(per.name) << " "
    << std::quoted(per.email);
    
    // Never forget to return the stream back.
    return os;
}

// Stream insertion operator used to print a person's information.
std::istream& operator>>(std::istream& is, Person& per) {
    // Implement this method to read id, name, and email for per.
    // For name and email used std::quoted to automatically handle quotes
    // in inputs
    is >> per.id >> std::quoted(per.name) >> std::quoted(per.email);;
    // Never forget to return the stream back.
    return is;
}

// A simple to_string method to convert a person's info to a string.
// It would be handy to use a ostringstream to implement this method!
std::string to_string(const Person& per) {
    std::ostringstream os;
    os << per;
    return os.str();
}

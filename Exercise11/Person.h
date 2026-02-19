/**
 * @file Person.h 
 * @author DJ Rao (raodm@miamioh.edu)
 * @brief A simple person class
 * @version 0.1
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

/**
 * @brief A simple class to encapsulate attributes for a Person
 * 
 */
class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& per);
    friend std::istream& operator>>(std::istream& os, Person& per);
public:
    /**
     * @brief Construct a new Person object
     * 
     * @param id The ID to be set. Default value is -1
     * @param name The name to be set. Default value is ""
     * @param salary The salary to be set. Default value is 0.
     */
    Person(const int id = -1, const std::string& name = "",
            const float salary = 0);
    
    /**
     * @brief Destroy the Person object
     * 
     * Currently the destructor is simply an empty method.
     */
    ~Person();

    /**
     * @brief Get the Id of the person.
     * 
     * @return int The id associated with this person.
     */
    int getId() const { return id; }

    /**
     * @brief Get the Name of the person.
     * 
     * @return std::string The name of the person
     */
    std::string getName() const { return name; }

    /**
     * @brief Returns a string representation of this person
     * by using an std::ostringstream and the stream insertion operator 
     * -- i.e., os << *this.
     * 
     * @return std::string The string representation of the person's data.
     */
    std::string to_string() const;

private:
    /** An unique ID associated with each person. */
    int id;

    /** The full name of the person */
    std::string name;

    /** The person's salary */
    float salary;
};

#endif

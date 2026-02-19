/* 
 * File:   Person.h
 * Author: raodm
 *
 * Copyright (C) 2019 raodm@miamiOH.edu
 */

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
    // Stream insertion operator to write/print Person object
    friend std::ostream& operator<<(std::ostream& os, const Person& per);
    // Stream extraction operator to read/populate a Person object.
    friend std::istream& operator>>(std::istream& is, Person& per);

public:
    /** Convenience constructor.
     * 
     * This constructor already has default values setup for the parameters.
     * So it can also be used as a default constructor to create objects,
     * but initialized to dummy/invalid values.
     */
    Person(int id = -1, const std::string& name = "", 
            const std::string& email = "");
    
    /** 
     * The destructor (converse of a constructor).
     */
    virtual ~Person();

    /** A simple getter method. NOTE: It is a constant method!
     * 
     * @return Returns the id of this person
     */
    int getID() const { return id; }
    
private:
    /** A unique ID for the person */
    int id;
    
    /** The persons name. */
    std::string name;
    
    /** The Person's email address. */
    std::string email;
};

/**
  * Convenience global to_string method to return a person's information
  * as a string.
  *
  * @param per The person to be converted to a string. This method just
  * uses an ostringstream to convert a person to a string.
  *
  * @return The full information about a person returned as a string.
  */
std::string to_string(const Person& per);

#endif /* PERSON_H */

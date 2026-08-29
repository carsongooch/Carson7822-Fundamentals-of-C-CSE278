#ifndef MOVIE_CPP
#define MOVIE_CPP

/** This file contains the implementation for various methods in the 
 * movie class.  See Javadoc for the methods in the header which is
 * where interface documentation belongs.
 * 
 * Copyright (C) 2024 raodm@miamioh.edu
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Movie.h"

// See Javadoc for this method in the header which is
// where interface documentation belongs.
// The default (and only) constructor for this class.
Movie::Movie() {
    // The instance variables are initialized in the header file. Consequently,
    // this constructor is empty.
}

// See Javadoc for this method in the header which is
// where interface documentation belongs.
// The destructor
Movie::~Movie() {
    // Currently, the destructor does not have any special tasks to do.
}

// See Javadoc for this method in the header which is
// where interface documentation belongs.
// Stream-extraction operator.
std::istream& operator>>(std::istream& is, Movie& m) {
    // Read the values from an entry in the stream/file in the correct order.
    is >> m.movieID >> std::quoted(m.title) >> m.year >> std::quoted(m.genres)
       >> m.imdbId  >> m.rating >> m.numRaters;
    // Return the stream as per the API requirement.
    return is;
}

// See Javadoc for this method in the header which is
// where interface documentation belongs.
// The stream insertion operator.
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    // Read the values from an entry in the stream/file in the correct order.
    os << m.movieID << " " << std::quoted(m.title) << " " << m.year   << " " 
       << std::quoted(m.genres) << " " << m.imdbId << " " << m.rating << " "
       << m.numRaters;
    // Return the stream as per the API requirement.
    return os;    
}

// See Javadoc for this method in the header which is
// where interface documentation belongs.
// A simple to-string method.
std::string to_string(const Movie& m) {
    std::ostringstream os;
    os << m;
    return os.str();
}

// See Javadoc for this method in the header which is
// where interface documentation belongs. This is a
// simple method that returns value for a given column
std::string
Movie::getCol(const std::string& col) const {
    std::ostringstream ss;
    if (col == "movieid") {
        ss << movieID;
    } else if (col == "title") {
        ss << std::quoted(title);
    } else if (col == "year") {
        ss << year;
    } else if (col == "genres") {
        ss << std::quoted(genres);
    } else if (col == "imdbid") {
        ss << imdbId;
    } else if (col == "rating") {
        ss << rating;
    } else if (col == "raters") {
        ss <<  numRaters;
    }
    // Return column info or an empty string if the
    // column name was not valid.
    return ss.str();
}

#endif

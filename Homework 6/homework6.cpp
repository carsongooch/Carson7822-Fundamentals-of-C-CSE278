/* 
 * File:   homework5.cpp
 * Copyright (C) 2025 goochcj@miamioh.edu
 */

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "Movie.h"

// A couple of namespaces to streamline code
using namespace std;
using namespace boost::asio::ip;

// Alias to a vector-of-strings
using StrVec = std::vector<std::string>;

/** Helper method to split a given string into separate words based on spaces.
 * Note that this method does the following 1 extra operations:
 *    2. Removes all commas (',') characters
 */


// Check to match if the value matches
bool valueCheck(const std::string& value, 
    const std::string& substring) {
        return value.find(substring) != std::string::npos;
    }

// Processes and prints movies 
void printMovies(const std::vector<Movie>& movies, const StrVec& column, 
        const std::string& colOfWhere, const std::string valueOfWhere) {
    for (size_t i = 0; (i < movies.size()); i++) {
        bool isEqual = true;
        if (!colOfWhere.empty()) {
            std::string columnValue = movies[i].getCol(colOfWhere);
            isEqual = valueCheck(columnValue, valueOfWhere);
        }
        if (isEqual == true) {
            for (size_t j = 0; (j < column.size()); j++) {
                std::cout << movies[i].getCol(column[j]);
                if (j < column.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

// Downloads the movies
std::vector<Movie> getMovies(const std::string& 
        host, const std::string& path) {
        Movie movie;
        std::vector<Movie> movies;
        tcp::iostream socket(host, "80");

        socket << "GET " << path << " HTTP/1.1\r\n";
        socket << "HOST: " << host << "\r\n";
        socket << "Connection: close\r\n\r\n";

        std::string line;
        while (std::getline(socket, line)) {
            if (line.empty() || line == "\r") {
                break;
            }
        }

        std::getline(socket, line);
        while (socket >> movie) {
            movies.push_back(movie);
        }
        return movies;
    }
// Extracts different parts of a link like the
// slash or host
void parseLink(const std::string& link, 
        std::string& linkHost, std::string& path) {
    std::string temp = link.substr(7);
    size_t slashIndex = temp.find("/");
    if (slashIndex != std::string::npos) {
        linkHost = temp.substr(0, slashIndex);
        path = temp.substr(slashIndex);
    } else {
        linkHost = temp;
        path = "/";
    }
}

// Helper method to find the index in a vector
int find(const StrVec& words, const std::string& value) {
    for (size_t i = 0; i < words.size(); i++) {
        if (words[i] == value) {
            return i;
        }
    }
    return -1;
}

StrVec split(std::string str) {
    // Change all ',' to spaces
    std::replace(str.begin(), str.end(), ',', ' ');
    // Now use a istringstream to extract words into a vector
    std::istringstream is(str);
    StrVec wordList;
    std::string word;
    while (is >> std::quoted(word)) {
        wordList.push_back(word);
    }
    // Return the list of words back to the caller.
    return wordList;
}

// This method processes a SQL query to retrive and display movie data
void processQuery(const std::string& query) {
    StrVec word = split(query);

    int selectIndex = find(word, "select");
    int fromIndex = find(word, "from");
    int whereIndex = find(word, "where");
    int likeIndex = find(word, "like");

    if (selectIndex == -1 || fromIndex == -1) {
        return;
    }

    StrVec row;
    for (int i = selectIndex + 1; i < fromIndex; i++) {
        row.push_back(word[i]);
    }
    std::string link = word[fromIndex + 1];
    std::string colOfWhere;
    std::string valueOfWhere;
    if (whereIndex != -1 && likeIndex != -1) {
        colOfWhere = word[whereIndex + 1];
        valueOfWhere = word[likeIndex + 1];
    }
    std::string linkHost;
    std::string linkPath;
    parseLink(link, linkHost, linkPath);

    const std::vector<Movie> movies = getMovies(linkHost, linkPath);
    printMovies(movies, row, colOfWhere, valueOfWhere);
}

/**
 * @brief processes queries from a typical input
 * 
 * This method reads queries from the user and processess them
 * to display movie data from web servers. 
 * 
 * @return int 0 to show the program ran.
 */
int main() {
    std::string query;
    while (true) {
        std::cout << "query> ";
        getline(cin, query);
        if (query == "exit") {
            break;
        }
        processQuery(query);
    }
    return 0;
}

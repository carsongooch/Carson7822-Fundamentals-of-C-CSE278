// Copyright (C) 2025 Carson Gooch (goochcj@miamioh.edu)
// Homework 3

#include <iostream>
#include <string>
#include <fstream>
#include "Movie.h"
#include <unordered_map>
#include <iomanip>

    /**
     * @brief this function fills an unordered_map with all
     * the movies from the text file using an input stream.
     * 
     * @param key Input stream that reads the data
     * @param db The unordered map that stores the movie data
     */
    void movieLoad(std::istream& key,
                    std::unordered_map<int, Movie>& map) {
        std::string firstLine;
        std::getline(key, firstLine);

        Movie m;
        while (key >> m) {
            map[m.getID()] = m;
        }
    }

    /**
     * @brief This method is called if "serach" is inputted in the console.
     * This method searches through all movies in the unordered map and
     * if the input for the search is found, then the movie is printed to
     * the console. At the end the total amount of movies found is also printed.
     * 
     * 
     * @param passed_movies This is the unordered map where all the movies are
     * stored 
     */
    void searchCommand(std::unordered_map<int, Movie> 
        passed_movies) {
        std::string searchInput;
        std::cin >> std::quoted(searchInput);

        int totalMovies = 0;
        for (const auto& [id, movie] : passed_movies) {
            if (to_string(movie).find(searchInput) != std::string::npos) {
                 std::cout << movie << std::endl;
                totalMovies++;
            }
        }
        std::cout << "Found " << totalMovies << " matche(s)." << std::endl;
    }

    /**
     * @brief This method is for the find command.
     * The user will enter find and then the id number.
     * This method scans through the unordered map and
     * finds the id number the user entered, and prints
     * the assoicated movie to the console. If no id
     * number is found, then it prints that no movie
     * was found.
     * 
     * @param passedNum passed id number from main
     * @param passed_movies passed unordered map from main
     * @param passedPrintCommand passed boolean that determines
     * if "Enter a command" needs to be printed after the function.
     */
    void findCommand(int passedNum, std::unordered_map<int, 
        Movie> passed_movies, bool passedPrintCommand) {
         std::cin >> passedNum;  

        bool foundCheck = false;
        for (auto& [id, movie] : passed_movies) {
            if (id == passedNum) {
                std::cout << movie << std::endl;
                foundCheck = true;
                break;
            }
        }
        if (!foundCheck) {
            std::cout << "Movie with ID " << passedNum << 
                " not found in database." << std::endl;
        }
        passedPrintCommand = true;
    }

/*
 * The main method that processses command-line argument and calls
 * the processFile method to do the actual processing.
 */
int main(int argc, char** argv) {
    std::ifstream movie_file("./movies_db.txt");
    std::unordered_map<int, Movie> movies;
    movieLoad(movie_file, movies);
    std::string input;
    int id_num = 0;
    bool printCommand = true;

    while (input != "exit") {
            if (printCommand == true) {
            std::cout << "Enter a command:" << std::endl;
            std::cin >> input;
        }

        if (input == "exit") {
            break;
        }

        if (input == "search") {
            searchCommand(movies);
        }

        if (input == "find") {
            findCommand(id_num, movies, printCommand);
        }
    } 
}

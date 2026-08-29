/* 
 * File:   homework2.cpp
 *
// Copyright (C) goochcj@miamioh.edu
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "Dictionary.h"
#include <fstream>
#include <vector>


using namespace std;
using namespace std::string_literals;

/** A simple string to print the HTML header. */
const std::string HTML_HEADER =
        "<html>\n"
        "  <body>\n"
        "    <table border=\"1\">\n"
        "      <tr><td>First and last line</td><td>Word counts</td></tr>";

/** A simple string to finish the HTML. */
const std::string HTML_TRAILER =
        "    </table>\n"
        "  </body>\n"
        "</html>";

/**
 * @brief Counts and returns the total number of words in a paragraph
 * 
 * @param list List of the total number of lines within the paragraph
 * @return int the number of words within the paragraph
 */
int wordCount(std::vector<std::string>& list) {
    int wordCount = 0;
    for (const std::string& line : list) {
        std::istringstream keyboard(line);
        std::string word;
        while (keyboard >> word) {
            wordCount++;
        }
    }
    return wordCount;
}

/**
 * @brief Similar to word count, but goes through an extra step to see if the 
 * word is a valid english word or not
 * 
 * @param list list of the total number of lines within the paragraph
 * @param dict Dictonary value used to determine if the word is a english word
 * or not
 * @return int total number of english words
 */
int engWordCount(std::vector<std::string>& list, const Dictionary& dict) {
    int englishWords = 0;
    for (const std::string& line : list) {
        std::istringstream keyboard(line);
        std::string word;
         while (keyboard >> word) {
            word = dict.toEngWord(word);

            if (dict.isEnglishWord(word)) {
                englishWords++;
            }
         }
    }
    return englishWords;
}

/**
 * @brief This method prints the html format for each line
 * that is printed to the terminal.
 * 
 * @param line the line that is being printed
 * @param lines the list of lines within the paragraph. Used
 * for the word count.
 * @param dictionary Dictonary value that can be passed to the word count 
 * methods.
 */
void printHelperMethod1(const std::string& line, 
    std::vector<std::string>& lines, const Dictionary& dictionary) {
    std::cout << "      <tr><td>" << line << 
        "<br></td><td>Words: " << wordCount(lines) << 
            "<br>English words: " << engWordCount(lines, dictionary) 
                << "</td></tr>" <<std::endl;
}

/**
 * @brief This helper method is very similar to printHelperMethod1, but this
 * method prints the two different first and last lines.
 * 
 * @param f_line the first line of the paragraph
 * @param l_line the last line of the paragraph
 * @param lines the list of lines within the paragraph
 * @param dictionary Dictonary value that can be passed to the word count
 * methods.
 */
void printHelperMethod2(const std::string f_line, std::string 
    l_line, std::vector<std::string>& lines, const Dictionary& dictionary) {
    
    std::cout << "      <tr><td>" << f_line << 
        "<br>" << l_line << 
            "</td><td>Words: " << wordCount(lines) << 
                "<br>English words: " << engWordCount(lines, dictionary) 
                    << "</td></tr>" << std::endl;
}

/**
 * @brief This method is used to help trim lines
 * 
 * @param line The string that is being trimmed
 */
void trimHelper(std::string& line) {
    line.erase(0, line.find_first_not_of(" \t\r\n"));
    line.erase(line.find_last_not_of(" \t\r\n") + 1);
}

/**
 * @brief This method reads lines until a blank line is reached. Used to skip
 * over the first few unnecessary lines.
 * 
 * @param key This is the scanner used in the main method and it is passed to
 * this method to read from the file.
 */
void setUpHelperMethod(std::istream& key) {
    std::string line;
    while (std::getline(key, line)) {
        trimHelper(line);

        if (line.empty()) {
            break;
        }
    }
}


/**
 * @brief This method decides which printer method to use depending on if the 
 * first and last lines are equal to each other.
 * 
 * @param f_line first line of the paragraph
 * @param l_line last line of the paragraph
 * @param lines list of lines in the paragraph
 * @param dictionary Dictionary value that is passed to other helper methods
 * to determine english words.
 */
void processParaHelper(const std::string& f_line, const std::string& l_line,
     std::vector<std::string>& lines, const Dictionary& dictionary) {
    if (lines.empty()) {
        return;
    }

    if (f_line == l_line) {
        printHelperMethod1(f_line, lines, dictionary);
    } else {
        printHelperMethod2(f_line, l_line, lines, dictionary);
    }
    lines.clear();
}




/**
 * The top-level method (to be implemented by student) to perform
 * the necessary operation to: 1. count words, 2. count valid English
 * words, and 3. print required output in HTML format. This method
 * is called from main.
 * 
 * \param[in] input The input stream (similar to std::cin) from where
 * lines are to be read (using std::getline) and processed line-by-line.
 * 
 */
void processFile(std::istream& input, const Dictionary& dictionary) {
    // Track word counts:
    //    wordCount[0]: Assume/use as total number of words
    //    wordCount[1]: Assume/use as total valid English words
    // Pass wordCount to the 2 helper methods in this file.

    // Implement rest of this method to do the necessary processing.
    std::cout << HTML_HEADER << std::endl;

    std::string lastLine, firstLine, line;
    setUpHelperMethod(input);

    std::vector<std::string> totalLines;
    while (std::getline(input, line)) {
        trimHelper(line);
        
        if (line.empty() && !firstLine.empty()) {
            processParaHelper(firstLine, lastLine, totalLines, dictionary);
            firstLine.clear(); lastLine.clear(); totalLines.clear();
        } else if (firstLine.empty()) {
            firstLine = line;
            lastLine = line;
        }
        if (!line.empty()) {
            lastLine = line;
            totalLines.push_back(line);
        }
    }
    if (!firstLine.empty() && firstLine == lastLine) {
        printHelperMethod1(firstLine, totalLines, dictionary);
    } else {
        printHelperMethod2(firstLine, lastLine, totalLines, dictionary);
    }
    cout << HTML_TRAILER << std::endl;
}

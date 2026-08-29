/**
 * A simple program to explore the use of vectors and files.
 *
 * Copyright (C) 2019 raodm@miamiOH.edu
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// A named-constant to print the HTML header for this exercise
const std::string HTMLHeader = "<!DOCTYPE html>\n"
    "<html>\n"
    "  <head>\n"
    "    <link rel='stylesheet' href='simple.css'>\n"
    "  </head>\n"
    "  <body>\n";

// A named-constant to print the HTML footer for this exercise
const std::string HTMLFooter = "  </body>\n"
    "</html>\n";

// A convenience type alias to refer to a vector strings
using StrVec = std::vector<std::string>;

/** Method to print each line in a given vector in HTML format to an
    output stream.  This method prints each entry in vec in the
    following manner:

    os << "    <div class='line'>"  << line << "</div>\n";

    @param[in] vec The vector of strings to be processed.

    @param[out] os The output stream to where the formatting string is
    to be written.
*/
void htmlFormatLines(const StrVec& vec, std::ostream& os) {
    // This method should use a range-based for-loop to write each
    // entry in the vector formatted as an HTML.  NOTE: This method
    // requires only 3 lines of code.
    for (const std::string& line : vec) {
        os << "     <div class = 'line'>" << line << "</div>\n";
    }
}

/** Method to read each line from a given file into a vector and
    return the vector for further processing.

    @param[in] filePath The path to the text file to be read. The path
    maybe a relative or absolute path.

    @return A vector-of-strings containing each line from the line as
    a separate entry in the vector.
*/
StrVec load(const std::string filePath) {
    // Create a std::ifstream to read from the file specified by filePath

    // This method should read line-by-line from the specified file
    // and push_back the line to a vector and return it.
    // load lines from the file into a std::vector
    std::vector<std::string> file_lines;
    std::ifstream file(filePath);
    std::string word;
    while (std::getline(file, word)) {
        file_lines.push_back(word);
    }

    
    
    // Return the newly created vector instead of the dummy return below
    return file_lines;
}

//--------------------------------------------------------------------
//         ONLY FIX STYLE/FORMATTING IN THE CODE BELOW  
//--------------------------------------------------------------------

/** The main method that calls different methods for testing.
 *
 * \param[in] argc The number of command-line arguments supplied to
 * this program.
 *
 * \param[in] argv The array of C-strings that contain the actual
 * command-line arguments.
 */
int main(int argc, char* argv[]) {
    // Print the common HTML header to format output
    std::cout << HTMLHeader;

    // Process inputs from a file, if a command-line argument is
    // specified.
    if (argc < 2) {
        // Do a simple loop to echo every line of input from std::cin to
        // std::cout, if no argument has been specified.
        for (std::string line; std::getline(std::cin, line);) {
            std::cout << line << std::endl;
        }
    } else {
        // The latter part of the exercise uses command-line arguments.
        // We assume that the first command-line arguments is path to
        // the text file from where lines are to be read.
        StrVec lines = load(argv[1]);
        // Print each line in HTML formatted output
        htmlFormatLines(lines, std::cout);
    }

    // Print the common HTML footer
    std::cout << HTMLFooter;
    // Return zero tell the OS that our program completed successfully
    return 0;
}

// End of source code.

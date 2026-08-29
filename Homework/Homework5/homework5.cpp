// Copyright Carson Gooch goochcj@miamioh.edu 2025
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "Movie.h"

/** A fixed HTML header that is printed at the beginning of output to ensure
 * the output is displayed correct.
 */
const std::string HTMLHeader = 
    "Content-Type: text/html\r\n\r\n"
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "<link type='text/css' rel='stylesheet' href='movie.css'/>\n"
    "</head>\n"
    "<body>\n";

/** A fixed HTML footer that is printed at the end of output to ensure
 * correct HTML formatting
 */
const std::string HTMLFooter = "</body>\n</html>";

/** Convenience method to decode HTML/URL encoded strings.

    This method must be used to decode query string parameters
    supplied along with GET request.  This method converts URL encoded
    entities in the from %nn (where 'n' is a hexadecimal digit) to
    corresponding ASCII characters.

    \param[in] str The string to be decoded.  If the string does not
    have any URL encoded characters then this original string is
    returned.  So it is always safe to call this method!

    \return The decoded string.
*/
std::string url_decode(std::string str) {
    // Decode entities in the from "%xx"
    size_t pos = 0;
    while ((pos = str.find_first_of("%+", pos)) != std::string::npos) {
        switch (str.at(pos)) {
            case '+': str.replace(pos, 1, " ");
            break;
            case '%': {
                std::string hex = str.substr(pos + 1, 2);
                char ascii = std::stoi(hex, nullptr, 16);
                str.replace(pos, 3, 1, ascii);
            }
        }
        pos++;
    }
    return str;
}

/**
* The top-level main method that must be extended/modified by the student.
* The main method just provides the connection information to connect to the
* database.
*/

void checkQueryCondition(mysqlpp::Query& query, 
    std::string& sYear, std::string& eYear) {
        if (!sYear.empty() && !eYear.empty()) {
        query << " AND year between %2 and %3";
    } else if (!sYear.empty()) {
        query << " AND year >= %2";
    } else if (!eYear.empty()) {
        query << " AND year <= %2";
    } 
}

mysqlpp::StoreQueryResult buildQuery(mysqlpp::Query& query, std::string& 
    titleSetUp, std::string& genreSetUp, std::string& sYear, 
         std::string& eYear) {
        if (!sYear.empty() && !eYear.empty()) {
            return query.store(titleSetUp, genreSetUp, sYear, eYear);
        } else if (!sYear.empty()) {
            return query.store(titleSetUp, genreSetUp, sYear);
        } else if (!eYear.empty()) {
            return query.store(titleSetUp, genreSetUp, eYear);
        } else {
            return query.store(titleSetUp, genreSetUp);
        }
    }

void showQuery(mysqlpp::Connection& myDB, std::string title, std::string genre, 
    std::string sYear, std::string eYear) {
    std::string titleSetUp = "%" + title + "%";
    std::string genreSetUp = "%" + genre + "%";
    mysqlpp::Query query = myDB.query();
    query << "SELECT id, title, year, genres, imdb_id, rating, raters " 
    << "FROM Movies " << "WHERE title LIKE %0q and genres like %1q";
    checkQueryCondition(query, sYear, eYear);
    query.parse();

    mysqlpp::StoreQueryResult result = buildQuery(query, 
        titleSetUp, genreSetUp, sYear, eYear);
    std::cout <<HTMLHeader;
    for (size_t i = 0; i < result.num_rows(); ++i) {
        Movie m;  m.setMovieID(result[i]["id"]);
        std::string titleString = result[i]["title"].c_str();
        m.setTitle(titleString); 
        m.setYear(result[i]["year"]);
        std::string genresString = result[i]["genres"].c_str();
        m.setGenres(genresString); 
        m.setimdbId(result[i]["imdb_id"]);
        m.setRating(result[i]["rating"]);
        m.setNumRaters(result[i]["raters"]); m.printAsHtml(std::cout);
    } 
    std::cout << HTMLFooter;
}


int main() {
    // The database connection that *must* be used in this project
    mysqlpp::Connection myDB("cse278s19", "os1.csi.miamioh.edu", "cse278s19",
            "rbHkqL64VpcJ2ezj");
    // Create a query
    mysqlpp::Query query = myDB.query();
    std::string input;
    std::getline(std::cin, input);
    std::string title, genre, sYear, eYear, param, value;
    std:: istringstream stream(input);

    while (std::getline(stream, param, '=')) {
        if (param == "title") {
            std::getline(stream, value, '&');
            title = url_decode(value);
        } else if (param == "genre") {
            std::getline(stream, value, '&');
            genre = url_decode(value);
        } else if (param == "startYear") {
            std::getline(stream, value, '&');
            sYear = url_decode(value);
        } else if (param == "endYear") {
            std::getline(stream, value, '&');
            eYear = url_decode(value);
        }
    }
    showQuery(myDB, title, genre, sYear, eYear);
}


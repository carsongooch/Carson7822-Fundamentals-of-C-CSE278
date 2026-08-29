// Copyright (C) 2019 raodm@miamioh.edu

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>

/** Convenience method to print result from a SQL query formatted as an 
 * HTML table.
 *
 * @param result The SQL query results to be printed by this method.
 */
void printResultInHtml(const mysqlpp::StoreQueryResult& result) {
  // Results is a 2D vector of mysqlpp::String objects.
  // Print the results.
  std::cout << "Content-Type: text/html\r\n\r\n";
  std::cout << "<table border=1>\n";
  for (const auto& row : result) {
    std::cout << "<tr>";
    for (const auto& col : row) {
      std::cout << "<td>" << col << "</td>";
    }
    std::cout << "</tr>\n";
  }
  std::cout << "</table>\n";    
}

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

/** The main method that processes CGI input data from standard input
 * The input will be in the format category=c%2B%2B&price=1%323
 * Ensure you URL decode each value prior to using it.
 *
 * Tip: Using std::getline(std::cin, param1, '=') and
 * std::getline(std::cin, value1, '&') is handy to read parameter and
 * value pairs that are separated by '=' and '&' characters.
 */
int main() {
    // Currently, this program is using a hard coded category and price.
    // Instead, you should modify the program to obtain category and
    // price from GGI inputs of the form: category=c%2B%2B&price=1%323
    std::string input;
    std::getline(std::cin, input);
    std::string category;
    int price = 0;

    std::string param1, value;
    std::istringstream stream(input);

    while (std::getline(stream, param1, '=')) {
      if (param1 == "category") {
        std::getline(stream, value, '&');
        category = url_decode(value);
      } else if (param1 == "price") {
        std::getline(stream, value, '&');
        value = url_decode(value);
        price = std::stoi(value);
      }
    }
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection myDB("cse278s19", "localhost", "cse278s19",
            "rbHkqL64VpcJ2ezj");
    // Create a query
    mysqlpp::Query query = myDB.query();
    query << "SELECT pname, price, category, manufacturer FROM Product "
          << "WHERE price <= %0 and category LIKE '%%%1%%';";
    query.parse();  // check to ensure query is correct
    // Run the query and get stored results
    mysqlpp::StoreQueryResult result = query.store(price, category);
    // Print results from query as an HTML table
    printResultInHtml(result);
    // All done
    return 0;
}

// Copyright (C) 2025 goochcj@miamioh.edu

#include <iostream>
#include <string>

int main() {
  const char QS[] = "QUERY_STRING";
  // Get query string (if any) from environment
  std::string queryStr = getenv(QS) != NULL ? getenv(QS) : "";
  // Get 1 line of POST data from std::cin (for printing)
  std::string postData;
  std::getline(std::cin, postData);
  // Echo/print the inputs this program got in HTML format
  std::cout << "Content-type: text/html\r\n\r\n";

  std::cout << "<!DOCTYPE html>\n<html>\n<body>\n";
  std::cout << "<p>query string : " << queryStr << "</p>\n";
  std::cout << "<p>Raw POST data: " << postData << "</p>\n";
  std::cout << "</body>\n</html>\n";
  return 0;
}


// Copyright (C) harveysd@miamiOH.edu
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

void parseHtmlInput(const std::string& data) {
    // Since input cannot have blank spaces, we replace 
    // = and & with blank spaces and then use an std::istringstream to
    // read out the name value pairs. 
    std::string input = data;
    std::replace(input.begin(), input.end(), '&', ' ');
    std::replace(input.begin(), input.end(), '=', ' ');

    std::istringstream letter(input);
    std::string name;
    std::string value;

    while (letter >> name >> value) {
        std::cout << name << value << std::endl;
    }
}

int main() {
    std::string values = "name=Harvey&course=278&sem=Fall25";
    parseHtmlInput(values);
    return 0;
}



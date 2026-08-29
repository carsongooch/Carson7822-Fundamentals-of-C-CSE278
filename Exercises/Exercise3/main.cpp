// Copyright 2025 goochcj@miamiOH.edus

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

// It is ok to use the following namespace delarations in C++ source
// files only. They must never be used in header files.
using namespace std;
using namespace std::string_literals;


int main() {
    std::string line, prevLine;
    // Read & process line-by-line until EOF

    bool inLine = false;

    while (std::getline(std::cin, line)) {
        if (std::string::empty()) {
            if (inLine) {
                std::cout << prevLine << std::endl;
                inLine = false;
            }
        } else {
            inLine = true;
            prevLine = line;
        }
    }
    if (inLine) {
        std::cout << prevLine << std::endl;
    }
    return 0;
}


// End of source code

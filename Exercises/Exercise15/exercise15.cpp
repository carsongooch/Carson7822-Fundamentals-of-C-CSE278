/* 
 * File:   simple.cpp
 * Author: raodm
 *
 * Copyright (C) 2025 goochcj@miamiOH.edu
 */

#include <iostream>

// Only globals show up in symbol table. So we have 2 global variables
// to ensure they show up in the symbol table.
int  variable1 = 10;
long variable2 = 20;

/** A simple method to test mapping of C++ to assembly. */
void doSomething() {
    variable1 += 10;
    variable2 += 20;
}


/*
 * A simple main function.
 */
int main() {
    // Call the doSomething method
    doSomething();
    return 0;
}


/* 
 * File:   main.cpp
 * Author: raodm
 *
 * Copyright (C) raodm@miamioh.edu
 */

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "Shapes.h"

using namespace std;

// Shortcut to shared pointer to shape(s)
using ShapePtr = std::shared_ptr<Shape>;

// A list of polymorphic Shape objects.
using ShapeList = std::vector<ShapePtr>;

/**
 * Method to compute total area of a given list of shapes.
 * 
 * @param shpList The list of shapes (actually shape pointers) whose 
 * area is to be computed.
 * 
 * @return The sum of areas of all shapes in the shape list.
 */
int getArea(const ShapeList& shpList) {
    double area = 0;
    for (const ShapePtr& shp : shpList) {
        area += shp ->getArea();
    }
    return area;
}

void print(const ShapeList& shpList) {
    for (const ShapePtr& shape : shpList) {
        std::cout << *shape << std::endl;
    }
}

//------------------------------------------------------
//    DO  NOT  MODIFY  CODE  BELOW  THIS  METHOD
//------------------------------------------------------

ShapeList loadShapes(std::istream& shapeData) {
    ShapeList shpList;  // List of shapes to be returned
    char type = 0;
    ShapePtr shape = nullptr;  // Shape to be created below.
    while (shapeData >> type) {
        switch (type) {
            case 'S':  // Create a square
                shape = std::make_shared<Square>();
                break;
            case 'C':  // Create a circle
                shape = std::make_shared<Circle>();
        }
        // Have the shape load its data
        shapeData >> *shape;
        // Add it to the vector to be returned by this method
        shpList.push_back(shape);
    }
    // Return the list of shapes created
    return shpList;
}

/*
 * A simple main method to create a variety of objects.
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Specify input shape file to process.\n";
        return 1;
    }
    // Create a input stream to load data from file.
    std::ifstream shapeFile(argv[1]);
    if (!shapeFile.good()) {
        std::cerr << "Unable to open shape data " << argv[1] << std::endl;
        return 2;
    }
    // Load all the shapes in the input file.
    ShapeList list = loadShapes(shapeFile);
    // Print all the of the shapes in the input file
    print(list);
    // Print their total area
    std::cout << "Total area: " << getArea(list) << std::endl;
    return 0;
}

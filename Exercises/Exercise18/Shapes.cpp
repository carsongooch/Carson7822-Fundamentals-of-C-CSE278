/* 
 * File:   Shapes.cpp
 * Author: raodm
 * 
 * Copyright (C) raodm@miamiOH.edu
 */

#include "Shapes.h"
#include <iostream>

//-------------------[ Square methods ]----------------------------

Square::Square(double side) : side(side) {
    // Nothing else to be done here.
}

Square::~Square() {
    // Nothing else to be done here.
}

double Square::getArea() const {
    double area = side * side;
    return area;
}

void Square::print(std::ostream& os) const {
    os << "Square(" << side << ")";
}

void Square::read(std::istream& is)  {
    is >> side;
}

//------------------------------------------------------------------
//                  DO  NOT  MODIFY  CODE  BELOW  THIS
//-------------------------[ Shape methods ]------------------------

Shape::Shape() {
    // Nothing else to be done here.
}

Shape::~Shape() {
    // Nothing else to be done here.
}

double
Shape::getArea() const {
    std::cerr << "Shape::getArea() should not be called!\n";
    return -1;
}

void 
Shape::print(std::ostream& os) const {
    // Nothing to be done.
}

void 
Shape::read(std::istream& is) {
    // Nothing to be done.
}

std::ostream& operator<<(std::ostream& os, const Shape& shp) {
    shp.print(os);  // call polymorphic print method
    return os;
}

std::istream& operator>>(std::istream& is, Shape& shp) {
    shp.read(is);  // call polymorphic method.
    return is;
}

//-------------------[ Circle methods ]----------------------------

Circle::Circle(double radius) : radius(radius) {
    // Nothing else to be done here.
}

Circle::~Circle() {
    // Nothing else to be done here.
}

double
Circle::getArea() const {
    return (3.142 * radius * radius);
}

void 
Circle::print(std::ostream& os) const {
    os << "Circle(" << radius << ")";
}

void 
Circle::read(std::istream& is) {
    is >> radius;
}

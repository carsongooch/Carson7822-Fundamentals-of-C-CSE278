/* 
 * File:   Shapes.h
 * Author: raodm/harveysd
 *
 * Copyright (C) raodm@miamioh.edu / harveysd@miamoih.edu
 */

#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

class Shape {
    friend std::ostream& operator<<(std::ostream& os, const Shape& shp);
    friend std::istream& operator>>(std::istream& is, Shape& shp);
public:
    Shape();
    virtual ~Shape();
    virtual double getArea() const;
    
protected:
    virtual void print(std::ostream& os) const;
    virtual void read(std::istream& is);
};

class Circle : public Shape {
public:
    Circle(double radius = 0.0);
    ~Circle() override;
    double getArea() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

private:
    double radius;
};

class Square : public Shape {
public:
    Square(double side = 0.0);
    ~Square() override;
    double getArea() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;


private:
    double side;
};

#endif /* SHAPES_H */


/*
* Copyright 2025 harvyesd@miamioh.edu
*/

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Base Vehicle Class
class Vehicle{
public:
    virtual void drive() const {
        cout << "Vehicle goes ... \n";
    }
    
    virtual ~Vehicle() = default;
};

// Car class 
class Car : public Vehicle {
public:
    void drive() const override {
        cout << "Car goes vroom \n";
    }
};

// Truck class
// Car class 
class Truck : public Vehicle {
public:
    void drive() const override {
        cout << "Car goes rumble \n";
    }
};

// Motorcyle class
class Motorcycle : public Vehicle {
public:
    void drive() const override {
        cout << "Motorcycle goes WEEEE \n";
    }
};

// Factory Function
shared_ptr<Vehicle> vehicleFactory(char choice) {
    switch (choice) {
        case 'c' : return make_shared<Car>();
        case 't' : return make_shared<Truck>();
        case 'm' : return make_shared<Motorcycle>();
        default : return make_shared<Vehicle>();
    }
}




int main(int argc, char* argv[]) {
    // Create a car and a truck via raw pointers
    shared_ptr<Vehicle> v1 = make_shared<Car>();
    shared_ptr<Vehicle> v2 = make_shared<Truck>();

    // vector<shared_ptr<Vehicle>> garage;
    // garage.push_back(make_shared<Car>());
    // garage.push_back(make_shared<Truck>());
    // garage.push_back(make_shared<Car>());

     vector<shared_ptr<Vehicle>> garage;
    garage.push_back(vehicleFactory('c'));
    garage.push_back(vehicleFactory('t'));
    garage.push_back(vehicleFactory('m'));
    garage.push_back(vehicleFactory('v'));


    vector<Vehicle> wrongGarage;
    wrongGarage.push_back(Car());
    wrongGarage.push_back(Truck());
    wrongGarage.push_back(Motorcycle());
    wrongGarage.push_back(Vehicle());

    // Make them drive!
    for (const auto& v : garage) {
        v->drive();
    }

    cout << "Your garage...\n";
    for (const auto& v : wrongGarage) {
        v.drive();
    }

    return 0;
}

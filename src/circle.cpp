// Copyright 2024 Skotin Alexander

#include "circle.h"
#include <cmath>
#include <iostream>


const double PI = 3.14159265358979323846;

void Circle::updateFromRadius() {
    ference = 2 * PI * radius;
    area = PI * radius * radius;
}

void Circle::updateFromFerence() {
    if (ference < 0) {
        std::cerr << "Ference cannot be negative. Setting to zero."
            << std::endl;
        ference = 0;
    }
    radius = ference / (2 * PI);
    area = PI * radius * radius;
}

void Circle::updateFromArea() {
    if (area < 0) {
        std::cerr << "Area cannot be negative. Setting to zero." << std::endl;
        area = 0;
    }
    radius = sqrt(area / PI);
    ference = 2 * PI * radius;
}

Circle::Circle(double r) : radius(r < 0 ? 0 : r) {
    updateFromRadius();
}

void Circle::setRadius(double r) {
    if (r < 0) {
        std::cerr << "Radius cannot be negative. Setting to zero." << std::endl;
        r = 0;
    }
    radius = r;
    updateFromRadius();
}

void Circle::setFerence(double f) {
    if (f < 0) {
        std::cerr << "Ference cannot be negative. Setting to zero."
            << std::endl;
        f = 0;
    }
    ference = f;
    updateFromFerence();
}

void Circle::setArea(double a) {
    if (a < 0) {
        std::cerr << "Area cannot be negative. Setting to zero." << std::endl;
        a = 0;
    }
    area = a;
    updateFromArea();
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}

double Circle::getArea() const {
    return area;
}

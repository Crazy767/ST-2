// Copyright 2024 Skotin Alexander
#include <cstdint>
#include "circle.h"

const double PI = 3.14159265358979323846;

void Circle::updateFromRadius() {
    ference = 2 * PI * radius;
    area = PI * radius * radius;
}

void Circle::updateFromFerence() {
    radius = ference / (2 * PI);
    area = PI * radius * radius;
}

void Circle::updateFromArea() {
    radius = sqrt(area / PI);
    ference = 2 * PI * radius;
}

Circle::Circle(double r) : radius(r) {
    updateFromRadius();
}

void Circle::setRadius(double r) {
    radius = r;
    updateFromRadius();
}

void Circle::setFerence(double f) {
    ference = f;
    updateFromFerence();
}

void Circle::setArea(double a) {
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

// Copyright 2024 Skotin Alexander

#include "circle.h"
#include "tasks.h"

double calculateRopeGap() {
    Circle earth(6378100.0);
    earth.setFerence(earth.getFerence() + 1.0);
    return earth.getRadius() - 6378100.0;
}

double calculatePoolCosts(double poolRadius, double pathWidth) {
    Circle pool(poolRadius);
    Circle poolWithPath(poolRadius + pathWidth);
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double fenceLength = poolWithPath.getFerence();

    return pathArea * 1000.0 + fenceLength * 2000.0;
}

// Copyright 2024 Skotin Alexander
#include "circle.h"
#include "tasks.h"

double calculateRopeGap() {
    Circle earth(6378100.0);  // радиус Земли в метрах
    earth.setFerence(earth.getFerence() + 1.0);
    return earth.getRadius() - 6378100.0;
}

double calculatePoolCosts() {
    Circle pool(3.0);
    Circle poolWithPath(4.0);  // радиус с дорожкой
    
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double fenceLength = poolWithPath.getFerence();

    return pathArea * 1000.0 + fenceLength * 2000.0;
}

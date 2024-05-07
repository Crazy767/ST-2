// Copyright 2024 Skotin Alexander
#include <gtest/gtest.h>
#include "circle.h"
#include "tasks.h"

// Тесты для класса Circle
class CircleTest : public ::testing::Test {
 protected:
    Circle* circle;

    void SetUp() override {
        circle = new Circle(10.0);  // начальный радиус 10
    }

    void TearDown() override {
        delete circle;
    }
};

// Тестирование начальных значений
TEST_F(CircleTest, InitialValues) {
    EXPECT_NEAR(circle->getRadius(), 10.0, 1e-5);
    EXPECT_NEAR(circle->getFerence(), 2 * M_PI * 10.0, 1e-5);
    EXPECT_NEAR(circle->getArea(), M_PI * 10.0 * 10.0, 1e-5);
}

// Тестирование изменения радиуса
TEST_F(CircleTest, SetRadius) {
    circle->setRadius(20.0);
    EXPECT_NEAR(circle->getRadius(), 20.0, 1e-5);
    EXPECT_NEAR(circle->getFerence(), 2 * M_PI * 20.0, 1e-5);
    EXPECT_NEAR(circle->getArea(), M_PI * 20.0 * 20.0, 1e-5);
}

// Тестирование изменения длины окружности
TEST_F(CircleTest, SetFerence) {
    circle->setFerence(62.83185307);  // 2*π*10
    EXPECT_NEAR(circle->getRadius(), 10.0, 1e-5);
}

// Тестирование изменения площади
TEST_F(CircleTest, SetArea) {
    circle->setArea(314.15926536);  // π*10^2
    EXPECT_NEAR(circle->getRadius(), 10.0, 1e-5);
}

// Контрольные значения с другими начальными данными
TEST(CircleControlTest, CustomInitialValues) {
    Circle smallCircle(1.0);
    EXPECT_NEAR(smallCircle.getFerence(), 2 * M_PI * 1.0, 1e-5);
    EXPECT_NEAR(smallCircle.getArea(), M_PI * 1.0 * 1.0, 1e-5);

    Circle largeCircle(100.0);
    EXPECT_NEAR(largeCircle.getFerence(), 2 * M_PI * 100.0, 1e-5);
    EXPECT_NEAR(largeCircle.getArea(), M_PI * 100.0 * 100.0, 1e-5);
}

// Проверка целостности после последовательных изменений
TEST(CircleSequentialChangesTest, SequentialUpdates) {
    Circle circle(10.0);
    circle.setRadius(5.0);
    circle.setFerence(circle.getFerence() + 10.0);
    circle.setArea(circle.getArea() - 20.0);

    double expectedRadius = sqrt(circle.getArea() / M_PI);
    EXPECT_NEAR(circle.getRadius(), expectedRadius, 1e-5);
}

// Тесты для задачи "Земля и верёвка"
TEST(TaskTests, RopeGapExact) {
    double gap = calculateRopeGap();
    double expectedGap = 1.0 / (2 * M_PI);
    EXPECT_NEAR(gap, expectedGap, 1e-5);
}

// Тесты для задачи "Бассейн"
TEST(TaskTests, PoolCostsExact) {
    double poolRadius = 3.0;
    double pathWidth = 1.0;

    double costs = calculatePoolCosts(poolRadius, pathWidth);

    double expectedCosts = 72256.57;
    EXPECT_NEAR(costs, expectedCosts, 0.1);
}

// Тестирование с различными изменениями длины верёвки
TEST(TaskTests, DifferentRopeLengths) {
    Circle earth(6378100.0);
    double originalFerence = earth.getFerence();

    earth.setFerence(originalFerence + 10.0);
    double gap1 = earth.getRadius() - 6378100.0;

    earth.setFerence(originalFerence + 100.0);
    double gap2 = earth.getRadius() - 6378100.0;

    earth.setFerence(originalFerence + 1000.0);
    double gap3 = earth.getRadius() - 6378100.0;

    EXPECT_GT(gap2, gap1);
    EXPECT_GT(gap3, gap2);
}

// Тесты на крайние значения
TEST(CircleExtremeValuesTest, VerySmallRadius) {
    Circle tinyCircle(0.000001);
    EXPECT_NEAR(tinyCircle.getFerence(), 2 * M_PI * 0.000001, 1e-9);
    EXPECT_NEAR(tinyCircle.getArea(), M_PI * 0.000001 * 0.000001, 1e-12);
}

TEST(CircleExtremeValuesTest, VeryLargeRadius) {
    Circle hugeCircle(1000000.0);
    EXPECT_NEAR(hugeCircle.getFerence(), 2 * M_PI * 1000000.0, 1e-5);
    EXPECT_NEAR(hugeCircle.getArea(), M_PI * 1000000.0 * 1000000.0, 1e-5);
}

// Тест на отрицательное значение радиуса
TEST(CircleInvalidValuesTest, NegativeRadius) {
    Circle circle(-10.0);
    EXPECT_NEAR(circle.getRadius(), 0.0, 1e-5);
    EXPECT_NEAR(circle.getFerence(), 0.0, 1e-5);
    EXPECT_NEAR(circle.getArea(), 0.0, 1e-5);
}

// Тесты на изменение с очень маленькими значениями
TEST(CircleMicroAdjustmentsTest, TinyChanges) {
    Circle circle(10.0);
    circle.setRadius(circle.getRadius() + 0.000001);
    EXPECT_NEAR(circle.getRadius(), 10.000001, 1e-9);
    EXPECT_NEAR(circle.getFerence(), 2 * M_PI * 10.000001, 1e-9);
}

// Тесты с точностью до множества изменений
TEST(CircleSequentialChangesTest, MultipleAdjustments) {
    Circle circle(10.0);
    circle.setRadius(5.0);
    circle.setFerence(circle.getFerence() + 3.14159265358979323846);
    circle.setArea(circle.getArea() - 10.0);

    double expectedRadius = sqrt(circle.getArea() / M_PI);
    EXPECT_NEAR(circle.getRadius(), expectedRadius, 1e-5);
}

TEST(TaskTests, RopeGapMinimalChange) {
    Circle earth(6378100.0);
    double originalFerence = earth.getFerence();
    earth.setFerence(originalFerence + 0.0001);
    double gap = earth.getRadius() - 6378100.0;
    double expectedGap = 0.0001 / (2 * M_PI);

    EXPECT_NEAR(gap, expectedGap, 1e-5);
}

// Тесты, проверяющие расчеты стоимости с нулевым и отрицательным радиусом
TEST(TaskTests, PoolCostsZeroRadius) {
    double poolRadius = 0.0;
    double pathWidth = 1.0;
    double expectedCost = calculatePoolCosts(poolRadius, pathWidth);

    Circle pool(poolRadius);
    Circle poolWithPath(poolRadius + pathWidth);
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double fenceLength = poolWithPath.getFerence();
    double manuallyCalculatedCost = pathArea * 1000.0 + fenceLength * 2000.0;

    EXPECT_NEAR(expectedCost, manuallyCalculatedCost, 1e-5);
}

// Проверка задачи с нулевым радиусом Земли
TEST(TaskTests, RopeGapZeroEarthRadius) {
    Circle earth(0.0);
    earth.setFerence(earth.getFerence() + 1.0);
    double gap = earth.getRadius();
    EXPECT_NEAR(gap, 1.0 / (2 * M_PI), 1e-5);
}

// Тест на максимально возможные значения
TEST(CircleExtremeValuesTest, MaximumPossibleRadius) {
    Circle enormousCircle(1e16);
    EXPECT_NEAR(enormousCircle.getFerence(), 2 * M_PI * 1e16, 1e10);
    EXPECT_NEAR(enormousCircle.getArea(), M_PI * 1e16 * 1e16, 1e32);
}

// Тестирование обновления через площадь с крайне маленьким значением
TEST(CircleMicroAdjustmentsTest, UpdateFromTinyArea) {
    Circle circle(10.0);
    circle.setArea(1e-12);
    EXPECT_NEAR(circle.getRadius(), sqrt(1e-12 / M_PI), 1e-15);
    EXPECT_NEAR(circle.getFerence(), 2 * M_PI * sqrt(1e-12 / M_PI), 1e-15);
}

// Тест задачи "Бассейн" с экстремальными условиями
TEST(TaskTests, PoolCostsLargeRadius) {
    double poolRadius = 1000.0;
    double pathWidth = 1.0;

    double expectedCost = calculatePoolCosts(poolRadius, pathWidth);

    Circle pool(poolRadius);
    Circle poolWithPath(poolRadius + pathWidth);
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double fenceLength = poolWithPath.getFerence();
    double manuallyCalculatedCost = pathArea * 1000.0 + fenceLength * 2000.0;

    EXPECT_NEAR(expectedCost, manuallyCalculatedCost, 1e-5);
}

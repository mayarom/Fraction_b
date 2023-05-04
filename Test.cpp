#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/Fraction.hpp"
#include <stdbool.h>
#include <string>
#include <ctime>

using namespace ariel;
using namespace std;

TEST_CASE("Basic functionality tests")
{
    // Initialize srand for randomized tests
    srand(time(nullptr));

    // Test constructors
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    Fraction f3(0.5);
    CHECK(f3 == f1);

    // Test addition
    Fraction sum = f1 + f2;
    CHECK(sum == Fraction(5, 4));

    // Test subtraction
    Fraction diff = f2 - f1;
    CHECK(diff == Fraction(1, 4));

    // Test multiplication
    Fraction prod = f1 * f2;
    CHECK(prod == Fraction(3, 8));

    // Test division
    Fraction quot = f1 / f2;
    CHECK(quot == Fraction(2, 3));

    // Test reduction
    Fraction f4(2, 4);
    CHECK(f4 == Fraction(1, 2));

    // Test pre-fix and post-fix increment operators
    Fraction f5(1, 2);
    Fraction f6 = ++f5;
    CHECK(f5 == Fraction(3, 2));
    CHECK(f6 == Fraction(3, 2));
    Fraction f7(1, 2);
    Fraction f8 = f7++;
    CHECK(f7 == Fraction(3, 2));
    CHECK(f8 == Fraction(1, 2));

    // Division by zero
    Fraction a(1, 2);
    Fraction b(0, 1);
    CHECK_THROWS_AS(a / b, std::invalid_argument);
}

TEST_CASE("Randomized tests")
{
    // Test addition, subtraction, multiplication, and division
    for (int i = 0; i < 100; i++)
    {
        int a = rand() % 100;
        int b = rand() % 100 + 1;
        int c = rand() % 100;
        int d = rand() % 100 + 1;
        Fraction f1(a, b);
        Fraction f2(c, d);
        Fraction sum = f1 + f2;
        Fraction diff = f1 - f2;
        Fraction prod = f1 * f2;
        Fraction quot = f1 / f2;
        CHECK(sum == Fraction(a * d + b * c, b * d));
        CHECK(diff == Fraction(a * d - b * c, b * d));
        CHECK(prod == Fraction(a * c, b * d));
        CHECK(quot == Fraction(a * d, b * c));
    }

    // Test comparison operators
    for (int i = 0; i < 100; i++)
    {
        int a = rand() % 100;
        int b = rand() % 100 + 1;
        int c = rand() % 100;
        int d = rand() % 100 + 1;
        Fraction f1(a, b);
        Fraction f2(c, d);
        if (a * d < b * c)
        {
            CHECK(f1 < f2);
            CHECK(f2 > f1);
            CHECK(f1 <= f2);
            CHECK(f2 >= f1);
        }
        else if (a * d > b * c)
        {
            CHECK(f1 > f2);
            CHECK(f2 < f1);
            CHECK(f1 >= f2);
            CHECK(f2 <= f1);
        }
        else
        {
            CHECK(f1 == f2);
            CHECK(f2 == f1);
            CHECK(f1 <= f2);
            CHECK(f2 <= f1);
            CHECK(f1 >= f2);
            CHECK(f2 >= f1);
        }
    }
}


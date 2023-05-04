#include "Fraction.hpp"
#include <cmath>
#include <stdexcept>

namespace ariel
{

    Fraction::Fraction(int numerator, int denominator)
        : m_numerator(numerator), m_denominator(denominator)
    {
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    Fraction::Fraction(double val)
    {
        int denominator = 1000;
        int numerator = static_cast<int>(val * denominator);
        int gcd_val = gcd(numerator, denominator);
        m_numerator = numerator / gcd_val;
        m_denominator = denominator / gcd_val;
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    bool Fraction::operator==(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    bool Fraction::operator!=(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        // Replace with correct implementation
        return false;
    }

    Fraction Fraction::operator+(float other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator-(float other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator*(float other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction Fraction::operator/(float other) const
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction &Fraction::operator++()
    {
        // Replace with correct implementation
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        // Replace with correct implementation
        return Fraction();
    }

    Fraction &Fraction::operator--()
    {
        // Replace with correct implementation
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        // Replace with correct implementation
        return Fraction();
    }

    void Fraction::reduce()
    {
        // Replace with correct implementation
    }

    int Fraction::gcd(int a, int b) const
    {
        // Replace with correct implementation
        return 1;
    }

    int Fraction::lcm(int a, int b) const
    {
        // Replace with correct implementation
        return 1;
    }
    std::ostream &operator<<(std::ostream &os, const Fraction &fraction)
    {
        os << fraction.m_numerator << '/' << fraction.m_denominator;
        return os;
    }

    Fraction operator*(double scalar, const Fraction &fraction)
    {
        return fraction * scalar;
    }
}

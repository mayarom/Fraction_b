#pragma once
#include <iostream>

namespace ariel
{
    class Fraction
    {
    public:
        Fraction(int numerator = 0, int denominator = 1);
        Fraction(double val);

        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;

        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;

        Fraction operator+(float other) const;
        Fraction operator-(float other) const;
        Fraction operator*(float other) const;
        Fraction operator/(float other) const;

        friend Fraction operator+(int lhs, const Fraction &rhs);
        friend Fraction operator-(int lhs, const Fraction &rhs);
        friend Fraction operator*(int lhs, const Fraction &rhs);
        friend Fraction operator/(int lhs, const Fraction &rhs);

        friend Fraction operator+(float lhs, const Fraction &rhs);
        friend Fraction operator-(float lhs, const Fraction &rhs);
        friend Fraction operator*(float lhs, const Fraction &rhs);
        friend Fraction operator/(float lhs, const Fraction &rhs);

        friend Fraction operator+(double lhs, const Fraction &rhs);
        friend Fraction operator-(double lhs, const Fraction &rhs);
        friend Fraction operator*(double lhs, const Fraction &rhs);
        friend Fraction operator/(double lhs, const Fraction &rhs);

        Fraction &operator++();
        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);

        friend std::ostream &operator<<(std::ostream &os, const Fraction &fraction);
        friend std::istream &operator>>(std::istream &is, Fraction &fraction);

    private:
        int m_numerator;
        int m_denominator;

        void reduce();
        int gcd(int a, int b) const;
        int lcm(int a, int b) const;
    };
}

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <stdbool.h>
#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <unistd.h>
#include <numeric>
#include <limits>
#include <algorithm>

using namespace std;
namespace ariel
{

    float const devider = 1000;

    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        // Constructors and destructors
        Fraction(int numerator, int denominator);
        Fraction(float numerator);
        Fraction(double numerator);
        Fraction(Fraction const &other);
        Fraction();
        Fraction(Fraction &&other) noexcept; // move constructor


        ~Fraction() = default;

        // Operators for equlity (=)
        Fraction &operator=(Fraction &&other) noexcept; // move assignment operator
        Fraction &operator=(const Fraction &other);
        Fraction &operator=(float other);

        // Operators for addition (+)
        Fraction operator+(const Fraction &other) const;
        Fraction operator+(float other);
        Fraction operator+=(const Fraction &other);
        Fraction operator+=(float other);
        Fraction &operator++();
        const Fraction operator++(int);
        friend Fraction operator+(float other, const Fraction &fraction)
        {
            float tmp1 = round(other * devider) / devider;
            float tmp2 = round(fraction.to_float() * devider) / devider;
            Fraction tmp(tmp1 + tmp2);
            return tmp;
        }

        // Operators for subtraction (-)
        Fraction operator-(const Fraction &other) const;
        Fraction operator-(float other);
        Fraction operator-=(const Fraction &other);
        Fraction operator-=(float other);
        Fraction &operator--();
        const Fraction operator--(int);
        friend Fraction operator-(float other, const Fraction &fraction)
        {
            float tmp1 = round(other * devider) / devider;
            float tmp2 = round(fraction.to_float() * devider) / devider;
            Fraction tmp(tmp1 - tmp2);
            return tmp;
        }

        // Operators for multiplication (*)
        Fraction operator*(const Fraction &other) const;
        Fraction operator*(float other);
        Fraction operator*=(const Fraction &other);
        Fraction operator*=(float other);
        friend Fraction operator*(float other, const Fraction &fraction)
        {
            Fraction tmp(other);
            return tmp * fraction;
        }

        // Operators for division (/)
        Fraction operator/(const Fraction &other) const;
        Fraction operator/(float other);
        Fraction operator/=(const Fraction &other);
        Fraction operator/=(float other);
        friend Fraction operator/(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                throw std::runtime_error("Can't divide by zero");
            }
            Fraction tmp(other);
            return tmp / fraction;
        }

        // Operators for equality-checking (==, !=)
        bool operator==(const Fraction &other) const;
        bool operator==(float other);
        friend bool operator==(float other, const Fraction &fraction)
        {
            return other == fraction.to_float();
        }

        bool operator!=(const Fraction &other) const;
        bool operator!=(float other);
        friend bool operator!=(float other, const Fraction &fraction)
        {
            return other != fraction.to_float();
        }

        // Operators for inequality (>, <, >=, <=)
        bool operator>(const Fraction &other) const;
        bool operator>(float other);
        friend bool operator>(float other, const Fraction &fraction)
        {
            return other > fraction.to_float();
        }

        bool operator<(const Fraction &other) const;
        bool operator<(float other);
        friend bool operator<(float other, const Fraction &fraction)
        {
            return other < fraction.to_float();
        }

        bool operator>=(const Fraction &other) const;
        bool operator>=(float other);
        friend bool operator>=(float other, const Fraction &fraction)
        {
            return other >= fraction.to_float();
        }

        bool operator<=(const Fraction &other) const;
        bool operator<=(float other);
        friend bool operator<=(float other, const Fraction &fraction)
        {
            return other <= fraction.to_float();
        }

        // To string
        operator std::string() const;

        // Stream operators
        friend std::ostream &operator<<(std::ostream &ostrm, const Fraction &fraction)
        {
            int num = fraction.getNumerator();
            int denom = fraction.getDenominator();
            if (num > 0 && denom < 0 || num < 0 && denom < 0)
            {
                num *= -1;
                denom *= -1;
            }

            ostrm << num << "/" << denom;
            return ostrm;
        }

        friend std::istream &operator>>(std::istream &istrm, Fraction &fraction)
        {
            int numerator = 0;
            int denominator = 1;
            char slash = 0;
            istrm >> numerator;
            if (istrm.fail() || denominator == 0)
            {
                throw std::runtime_error("Invalid input");
            }
            if (istrm.peek() == '/')
            {
                istrm >> slash >> denominator;
                if (istrm.fail() || denominator == 0)
                {
                    throw std::runtime_error("Invalid input");
                }
            }
            else
            {
                istrm >> denominator;
                if (istrm.fail() || denominator == 0)
                {
                    throw std::runtime_error("Invalid input");
                }
            }
            fraction = Fraction(numerator, denominator);
            return istrm;
        }

        // Getters
        int getNumerator() const
        {
            return numerator;
        }

        int getDenominator() const
        {
            return denominator;
        }

        // Other methods

        static void reduce(int &numerator, int &denominator)
        {
            bool nflag = numerator < 0;
            bool dflag = denominator < 0;

            if (nflag)
            {
                numerator *= -1;
            }
            if (dflag)
            {
                denominator *= -1;
            }

            int gcd = std::__gcd(numerator, denominator);

            numerator /= gcd;
            denominator /= gcd;

            if (nflag)
            {
                numerator *= -1;
            }
            if (dflag)
            {
                denominator *= -1;
            }
        }

        float to_float() const
        {
            return static_cast<float>(numerator) / static_cast<float>(denominator);
        }
    };

}

#endif
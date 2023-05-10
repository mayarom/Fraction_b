
/*The Fraction Calculator Library is an efficient and comprehensive C++ library designed to perform arithmetic
and comparison operations on fractions. This library simplifies the process of working with fractions by
providing a user-friendly Fraction class that encapsulates a fraction as a numerator and a denominator. This
versatile class allows users to create Fraction objects using integer, float, or double values, and supports
copy or move constructors for seamless manipulation.

Author: Maya Rom
ID: 207485251
*/

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <numeric>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace std;

namespace ariel
{
    float const FACTOR = 1000;

    class Fraction
    {
    private:
        // Private methods - used by the class only
        int numerator;                        // The numerator of the fraction - always positive
        bool is_negative;                     // Is the fraction negative - true if negative, false if positive
        int denominator;                      // The denominator of the fraction - always positive
        void log(const std::string &message); // Prints a message to the console

    public:
        // Constructors and destructor - used by the user
        Fraction(int numerator, int denominator); // int constructor
        Fraction(float numerator);                // float constructor
        Fraction(double numerator);               // double constructor
        Fraction(Fraction const &other);          // copy constructor
        Fraction();                               // default constructor
        Fraction(Fraction &&other) noexcept;      // move constructor
        ~Fraction() = default;                    // destructor

        // Operators for equality (=)
        Fraction &operator=(Fraction &&other) noexcept; // move assignment operator
        Fraction &operator=(const Fraction &other);     // copy assignment operator
        Fraction &operator=(float other);               // float assignment operator

        // Operators for addition (+)
        Fraction operator+(const Fraction &other) const;                 // Fraction addition operator
        Fraction operator+(float other);                                 // float addition operator
        Fraction operator+=(const Fraction &other);                      // Fraction addition assignment operator
        Fraction operator+=(float other);                                // float addition assignment operator
        Fraction &operator++();                                          // Fraction prefix increment operator
        const Fraction operator++(int);                                  // Fraction postfix increment operator
        friend Fraction operator+(float other, const Fraction &fraction) // float + Fraction operator
        {
            float tmp1 = round(other * FACTOR) / FACTOR;               // round to 3 digits after the decimal point
            float tmp2 = round(fraction.to_float() * FACTOR) / FACTOR; // round to 3 digits after the decimal point
            Fraction tmp(tmp1 + tmp2);                                 // create a new Fraction object
            return tmp;
        }

        // Operators for subtraction (-)
        Fraction operator-(const Fraction &other) const;                 // Fraction subtraction operator
        Fraction operator-(float other);                                 // float subtraction operator
        Fraction operator-=(const Fraction &other);                      // Fraction subtraction assignment operator
        Fraction operator-=(float other);                                // float subtraction assignment operator
        Fraction &operator--();                                          // Fraction prefix decrement operator
        const Fraction operator--(int);                                  // Fraction postfix decrement operator
        friend Fraction operator-(float other, const Fraction &fraction) // float - Fraction operator
        {
            float tmp1 = round(other * FACTOR) / FACTOR;
            float tmp2 = round(fraction.to_float() * FACTOR) / FACTOR;
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
                error_zero();
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
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other != fraction.to_float();
        }

        // Operators for inequality (>, <, >=, <=)
        bool operator>(const Fraction &other) const;
        bool operator>(float other);
        friend bool operator>(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other > fraction.to_float();
        }

        bool operator<(const Fraction &other) const;
        bool operator<(float other);
        friend bool operator<(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other < fraction.to_float();
        }

        bool operator>=(const Fraction &other) const;
        bool operator>=(float other);
        friend bool operator>=(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other >= fraction.to_float();
        }

        bool operator<=(const Fraction &other) const;
        bool operator<=(float other);
        friend bool operator<=(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other <= fraction.to_float();
        }

        // Getters
        int getNumerator() const
        {
            if (denominator == 0)
            {
                error_zero();
            }
            return numerator;
        }

        int getDenominator() const
        {
            if (denominator == 0)
            {
                error_zero();
            }
            return denominator;
        }
        // To string
        operator std::string() const;

        // Stream operators
        friend std::ostream &operator<<(std::ostream &ostrm, const Fraction &fraction)
        {
            if (fraction.getDenominator() == 0)
            {
                error_zero();
            }
            int num = fraction.getNumerator();
            int denom = fraction.getDenominator();

            if (denom < 0)
            {
                num = -num;
                denom = -denom;
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
                error_invalid();
            }
            if (istrm.peek() == '/')
            {
                istrm >> slash >> denominator;
                if (istrm.fail() || denominator == 0)
                {
                    error_invalid();
                }
            }
            else
            {
                istrm >> denominator;
                if (istrm.fail() || denominator == 0)
                {
                    error_invalid();
                }
            }
            fraction = Fraction(numerator, denominator);
            return istrm;
        }

        // Other methods
        static void reduce(int &numerator, int &denominator)
        {
            if (denominator == 0)
            {
                error_zero();
            }

            bool nflag = numerator < 0;
            bool dflag = denominator < 0;

            numerator *= (nflag) ? -1 : 1;
            denominator *= (dflag) ? -1 : 1;

            int gcd = std::__gcd(numerator, denominator);

            numerator /= gcd;
            denominator /= gcd;

            numerator *= (nflag) ? -1 : 1;
            denominator *= (dflag) ? -1 : 1;
        }
        //"CANT DIVIDE BY ZERO" EXCEPTION
        static void error_zero()
        {
            throw std::runtime_error("Can't divide by zero");
        }
        static void error_invalid()
        {
            throw std::runtime_error("Invalid input");
        }
        static void error_overflow()
        {
            throw std::overflow_error("Overflow");
        }

        float to_float() const
        {
            if (denominator == 0)
            {
                error_zero();
            }
            return static_cast<float>(numerator) / static_cast<float>(denominator);
        }
    };
}

#endif




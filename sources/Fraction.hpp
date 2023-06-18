/**
 * @file Fraction.hpp
 * @brief Header file for the Fraction class.
 *
 * This file was written by Maya Rom, ID: 207485251. It contains the declaration of the Fraction class,
 * which represents a fraction with numerator and denominator. It provides various arithmetic and comparison
 * operations, as well as conversion functions to float and integer values. The class handles error cases
 * such as division by zero, overflow, and invalid input, and provides appropriate exception handling. The
 * Fraction class is designed to be used for precise fractional calculations and provides methods for
 * simplifying fractions to their simplest form.
 */

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <algorithm> // For algorithmic operations
#include <iostream>  // For input/output streams
#include <limits>    // For numeric limits
#include <math.h>    // For mathematical functions
#include <numeric>   // For numeric operations
#include <stdexcept> // For standard exceptions
#include <string>    // For string operations
#include <unistd.h>  // For POSIX API
#include <chrono>    // For time-related functions

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
        ~Fraction() = default;

        // Operators for equality (=)
        Fraction &operator=(Fraction &&other) noexcept; // move assignment operator
        Fraction &operator=(const Fraction &other);     // copy assignment operator
        Fraction &operator=(float other);               // float assignment operator

        // Operators for addition (+)
        Fraction operator+(const Fraction &other) const; // Fraction addition operator
        Fraction operator+(float other);                 // float addition operator
        Fraction operator+=(const Fraction &other);      // Fraction addition assignment operator
        Fraction operator+=(float other);                // float addition assignment operator
        Fraction &operator++();                          // Fraction prefix increment operator
        const Fraction operator++(int);                  // Fraction postfix increment operator
                                                         // Declaration of friend function

        /**
         * @brief Addition operator for adding a float value to a Fraction.
         *
         * This operator adds a float value to a Fraction object.
         *
         * @param other The float value to be added.
         * @param fraction The Fraction object to add to.
         * @return The result of the addition as a Fraction object.
         */
        friend Fraction operator+(float other, const Fraction &fraction)
        {
            // Calculate the addition of the float and the Fraction
            float tmp1 = round(other * FACTOR) / FACTOR;
            float tmp2 = round(fraction.to_float() * FACTOR) / FACTOR;
            Fraction tmp(tmp1 + tmp2);

            // Return the resulting Fraction
            return tmp;
        }

        // Operators for subtraction (-)
        Fraction operator-(const Fraction &other) const; // Fraction subtraction operator
        Fraction operator-(float other);                 // Float subtraction operator
        Fraction operator-=(const Fraction &other);      // Fraction subtraction assignment operator
        Fraction operator-=(float other);                // Float subtraction assignment operator
        Fraction &operator--();                          // Fraction prefix decrement operator
        const Fraction operator--(int);                  // Fraction postfix decrement operator

        /**
         * @brief Operator overload for subtraction of a float from a fraction.
         *
         * @param other The float value to subtract.
         * @param fraction The fraction to subtract from.
         * @return The result of the subtraction operation as a new Fraction.

         */
        /**
         * @brief Operator overload for subtraction of a float from a fraction.
         *
         * @param other The float value to subtract.
         * @param fraction The fraction to subtract from.
         * @return The result of the subtraction operation as a new Fraction.
         */
        friend Fraction operator-(float other, const Fraction &fraction)
        {
            // Calculate the subtraction of the float from the fraction
            float tmp1 = round(other * FACTOR) / FACTOR;
            float tmp2 = round(fraction.to_float() * FACTOR) / FACTOR;
            Fraction tmp(tmp1 - tmp2);

            // Return the resulting Fraction
            return tmp;
        }

        // time func
        /**
         * @brief Get the current time in milliseconds.
         *
         * @return The current time in milliseconds.
         */
        long long int get_time();

        /**
         * @brief Get the current time in microseconds.
         *
         * @return The current time in microseconds.
         */
        long long int get_time_micro();

        /**
         * @brief Print a message to the standard output.
         *
         * @param message The message to be printed.
         */
        void print_message(std::string message);

        // Operators for multiplication (*)
        Fraction operator*(const Fraction &other) const; // Fraction multiplication operator
        Fraction operator*(float other);                 // Float multiplication operator
        Fraction operator*=(const Fraction &other);      // Fraction multiplication assignment operator
        Fraction operator*=(float other);                // Float multiplication assignment operator
        /**
         * @brief Multiplication operator for multiplying a float value by a Fraction.
         *
         * This operator multiplies a float value by a Fraction object.
         *
         * @param other The float value to be multiplied.
         * @param fraction The Fraction object to multiply with.
         * @return The result of the multiplication as a Fraction object.
         */
        friend Fraction operator*(float other, const Fraction &fraction)
        {
            // Create a temporary Fraction object from the float value
            Fraction tmp(other);

            // Perform the multiplication and return the result
            return tmp * fraction;
        }

        // Operators for division (/)

        /**
         * @brief Operator overload for dividing a Fraction object by another Fraction object.
         */
        Fraction operator/(const Fraction &other) const;

        /**
         * @brief Operator overload for dividing a Fraction object by a float value.
         */
        Fraction operator/(float other);

        /**
         * @brief Operator overload for dividing a Fraction object by another Fraction object and assigning the result to the current object.
         */
        Fraction operator/=(const Fraction &other);

        /**
         * @brief Operator overload for dividing a Fraction object by a float value and assigning the result to the current object.
         */
        Fraction operator/=(float other);

        /**
         * @brief Friend function for dividing a float value by a Fraction object.
         */
        friend Fraction operator/(float other, const Fraction &fraction)
        {
            // Check if the fraction is zero
            if (fraction.to_float() == 0)
            {
                error_zero();
            }

            // Create a temporary Fraction object from the float value
            Fraction tmp(other);

            // Perform the division and return the result
            return tmp / fraction;
        }

        // Operators for equality-checking (==, !=)

        /**
         * @brief Operator overload for checking if two Fraction objects are equal.
         */
        bool operator==(const Fraction &other) const;

        /**
         * @brief Operator overload for checking if a Fraction object is equal to a float value.
         */
        bool operator==(float other);

        /**
         * @brief Operator overload for checking if a float value is equal to a Fraction object.
         */
        friend bool operator==(float other, const Fraction &fraction)
        {
            return other == fraction.to_float();
        }

        /**
         * @brief Operator overload for checking if two Fraction objects are not equal.
         */
        bool operator!=(const Fraction &other) const;

        /**
         * @brief Operator overload for checking if a Fraction object is not equal to a float value.
         */
        bool operator!=(float other);

        /**
         * @brief Operator overload for checking if a float value is not equal to a Fraction object.
         */
        friend bool operator!=(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other != fraction.to_float();
        }

        // Operators for inequality (>, <, >=, <=)

        /**
         * @brief Operator overload for the greater than operator (>) between two fractions.
         *
         * This operator compares the current fraction with another fraction to determine if the current fraction
         * is greater than the other fraction. It uses the float representation of the fractions for the comparison.
         *
         * @param other The other fraction to compare to.
         * @return true if the current fraction is greater than the other fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator>(const Fraction &other) const;

        /**
         * @brief Operator overload for the greater than operator (>) between a fraction and a float.
         *
         * This operator compares the current fraction with a float value to determine if the current fraction
         * is greater than the float value. It uses the float representation of the current fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @return true if the current fraction is greater than the float value, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator>(float other);

        /**
         * @brief Friend operator overload for the greater than operator (>) between a float and a fraction.
         *
         * This operator compares a float value with a fraction to determine if the float value is greater than the fraction.
         * It uses the float representation of the fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @param fraction The fraction to compare with the float value.
         * @return true if the float value is greater than the fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        friend bool operator>(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other > fraction.to_float();
        }

        /**
         * @brief Operator overload for the less than operator (<) between two fractions.
         *
         * This operator compares the current fraction with another fraction to determine if the current fraction
         * is less than the other fraction. It uses the float representation of the fractions for the comparison.
         *
         * @param other The other fraction to compare to.
         * @return true if the current fraction is less than the other fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator<(const Fraction &other) const;

        /**
         * @brief Operator overload for the less than operator (<) between a fraction and a float.
         *
         * This operator compares the current fraction with a float value to determine if the current fraction
         * is less than the float value. It uses the float representation of the current fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @return true if the current fraction is less than the float value, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator<(float other);

        /**
         * @brief Friend operator overload for the less than operator (<) between a float and a fraction.
         *
         * This operator compares a float value with a fraction to determine if the float value is less than the fraction.
         * It uses the float representation of the fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @param fraction The fraction to compare with the float value.
         * @return true if the float value is less than the fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        friend bool operator<(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other < fraction.to_float();
        }

        /**
         * @brief Operator overload for the greater than or equal to operator (>=) between two fractions.
         *
         * This operator compares the current fraction with another fraction to determine if the current fraction
         * is greater than or equal to the other fraction. It uses the float representation of the fractions for the comparison.
         *
         * @param other The other fraction to compare to.
         * @return true if the current fraction is greater than or equal to the other fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator>=(const Fraction &other) const;

        /**
         * @brief Operator overload for the greater than or equal to operator (>=) between a fraction and a float.
         *
         * This operator compares the current fraction with a float value to determine if the current fraction
         * is greater than or equal to the float value. It uses the float representation of the current fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @return true if the current fraction is greater than or equal to the float value, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator>=(float other);

        /**
         * @brief Friend operator overload for the greater than or equal to operator (>=) between a float and a fraction.
         *
         * This operator compares a float value with a fraction to determine if the float value is greater than or equal to the fraction.
         * It uses the float representation of the fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @param fraction The fraction to compare with the float value.
         * @return true if the float value is greater than or equal to the fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        friend bool operator>=(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other >= fraction.to_float();
        }

        /**
         * @brief Operator overload for the less than or equal to operator (<=) between two fractions.
         *
         * This operator compares the current fraction with another fraction to determine if the current fraction
         * is less than or equal to the other fraction. It uses the float representation of the fractions for the comparison.
         *
         * @param other The other fraction to compare to.
         * @return true if the current fraction is less than or equal to the other fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator<=(const Fraction &other) const;

        /**
         * @brief Operator overload for the less than or equal to operator (<=) between a fraction and a float.
         *
         * This operator compares the current fraction with a float value to determine if the current fraction
         * is less than or equal to the float value. It uses the float representation of the current fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @return true if the current fraction is less than or equal to the float value, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        bool operator<=(float other);

        /**
         * @brief Friend operator overload for the less than or equal to operator (<=) between a float and a fraction.
         *
         * This operator compares a float value with a fraction to determine if the float value is less than or equal to the fraction.
         * It uses the float representation of the fraction for the comparison.
         *
         * @param other The float value to compare to.
         * @param fraction The fraction to compare with the float value.
         * @return true if the float value is less than or equal to the fraction, false otherwise.
         * @throws std::runtime_error if the denominator is zero.
         */
        friend bool operator<=(float other, const Fraction &fraction)
        {
            if (fraction.to_float() == 0)
            {
                error_zero();
            }
            return other <= fraction.to_float();
        }

        // Getters
        int getNumerator() const;
        int getDenominator() const;
        // To string
        operator std::string() const;
        // To double
        double to_double() const;
        // To int
        int to_int() const;
        // Stream operators

        /**
         * @brief Overload of the stream insertion operator (<<) for Fraction objects.
         *
         * This operator allows a Fraction object to be inserted into an output stream, such as std::cout,
         * in the format "numerator/denominator". The fraction is displayed in its simplest form, with the
         * negative sign applied to the numerator if the denominator is negative.
         *
         * @param ostrm The output stream to insert the Fraction into.
         * @param fraction The Fraction object to insert.
         * @return The modified output stream after inserting the Fraction.
         * @throws std::runtime_error if the denominator is zero.
         */
        friend std::ostream &operator<<(std::ostream &ostrm, const Fraction &fraction)
        {
            // Check if the denominator is zero
            if (fraction.getDenominator() == 0)
            {
                error_zero();
            }

            int num = fraction.getNumerator();
            int denom = fraction.getDenominator();

            // Adjust the sign of the numerator if the denominator is negative
            if (denom < 0)
            {
                num = -num;
                denom = -denom;
            }

            // Output the fraction in the format "numerator/denominator"
            ostrm << num << "/" << denom;
            return ostrm;
        }

        /**
         * @brief Overload of the stream extraction operator (>>) for Fraction objects.
         *
         * This operator allows a Fraction object to be extracted from an input stream, such as std::cin,
         * in the format "numerator/denominator". The numerator and denominator are read from the input
         * stream and used to construct a new Fraction object. The Fraction is then assigned to the provided
         * fraction variable.
         *
         * @param istrm The input stream to extract the Fraction from.
         * @param fraction The Fraction variable to assign the extracted value to.
         * @return The modified input stream after extracting the Fraction.
         * @throws std::runtime_error if the input is invalid or the denominator is zero.
         */
        friend std::istream &operator>>(std::istream &istrm, Fraction &fraction)
        {
            int numerator = 0;
            int denominator = 1;
            char slash = 0;

            // Read the numerator from the input stream
            istrm >> numerator;

            // Check for input failure or a zero denominator
            if (istrm.fail() || denominator == 0)
            {
                error_invalid();
            }

            // Check if the next character is a slash ('/')
            if (istrm.peek() == '/')
            {
                // Read the slash and the denominator from the input stream
                istrm >> slash >> denominator;

                // Check for input failure or a zero denominator
                if (istrm.fail() || denominator == 0)
                {
                    error_invalid();
                }
            }
            else
            {
                // If the next character is not a slash, assume the denominator is provided separately
                istrm >> denominator;

                // Check for input failure or a zero denominator
                if (istrm.fail() || denominator == 0)
                {
                    error_invalid();
                }
            }

            // Create a new Fraction object with the extracted numerator and denominator
            fraction = Fraction(numerator, denominator);
            return istrm;
        }

        // Other methods

        /**
         * @brief Reduces the numerator and denominator of a fraction to their simplest form.
         *
         * This method reduces the fraction to its simplest form by dividing both the numerator and denominator
         * by their greatest common divisor (GCD). It modifies the numerator and denominator variables in place.
         *
         * @param numerator The numerator of the fraction.
         * @param denominator The denominator of the fraction.
         */
        static void reduce(int &numerator, int &denominator);

        /**
         * @brief Throws a runtime_error with the message "Can't divide by zero".
         */
        static void error_zero();

        /**
         * @brief Throws a runtime_error with the message "Invalid input".
         */
        static void error_invalid();

        /**
         * @brief Throws an overflow_error with the message "Overflow".
         */
        static void error_overflow();

        /**
         * @brief Converts the fraction to a float value.
         *
         * @return The float representation of the fraction.
         *
         * @throws std::runtime_error if the denominator is zero.
         */
        float to_float() const;
    };

};

#endif

#include "Fraction.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <math.h>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace ariel;

// MAXINT and MININT are used for overflow error handling
int MAXINT = std::numeric_limits<int>::max();
int MININT = std::numeric_limits<int>::min();

// log function for debugging - prints the message to the console
void Fraction::log(const std::string &message)
{
    std::cout << "[Fraction]: " << message << std::endl;
}

// Constructors and destructors

/**
 * @brief Constructs a new Fraction object with the given numerator and denominator.
 *
 * @param input_numerator The numerator of the fraction.
 * @param input_denominator The denominator of the fraction.
 *
 * @throws std::invalid_argument if the denominator is zero.
 */
Fraction::Fraction(int input_numerator, int input_denominator)
{
    if (input_denominator == 0)
    {
        throw std::invalid_argument("Denominator can't be zero");
    }
    // error handling for overflow
    if (input_numerator > MAXINT || input_numerator < MININT || input_denominator > MAXINT || input_denominator < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    log("Creating fraction from int numerator and denominator");
    reduce(input_numerator, input_denominator);
    numerator = input_numerator;
    denominator = input_denominator;
}

/**
 * @brief Constructs a new Fraction object from a double value.
 *
 * @param value The value to convert to a fraction.
 */
Fraction::Fraction(double value)
{
    // error handling for overflow
    if (value > MAXINT || value < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    log("Creating fraction from double value");
    numerator = value * FACTOR;
    denominator = FACTOR;
    reduce(numerator, denominator);
};

/**
 * @brief Constructs a new Fraction object from a float value.
 *
 * @param value The value to convert to a fraction.
 */
Fraction::Fraction(float value)
{
    // error handling for overflow
    if (value > MAXINT || value < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    log("Creating fraction from float value");
    numerator = value * FACTOR;
    denominator = FACTOR;
    reduce(numerator, denominator);
};

/**
 * @brief Copy constructor for Fraction objects.
 *
 * @param other The Fraction object to copy.
 */
Fraction::Fraction(const Fraction &other)
{
    if (this == &other)
    {
        return;
    }
    // error handling for overflow
    if (other.getNumerator() > MAXINT || other.getNumerator() < MININT || other.getDenominator() > MAXINT || other.getDenominator() < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    log("Creating fraction from copy constructor");
    numerator = other.getNumerator();
    denominator = other.getDenominator();
};

/**
 * @brief Default constructor for Fraction objects.
 *
 * Sets the numerator to 0 and the denominator to 1.
 */
Fraction::Fraction()
{
    // error handling for overflow
    if (0 > MAXINT || 0 < MININT || 1 > MAXINT || 1 < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    // error handling for zero division
    if (1 == 0)
    {
        throw std::invalid_argument("Denominator can't be zero");
    }
    log("Creating fraction from default constructor");
    numerator = 0;
    denominator = 1;
};

/**
 * @brief Move constructor for Fraction objects.
 *
 * @param other The Fraction object to move.
 */
Fraction::Fraction(Fraction &&other) noexcept
{

    log("Creating fraction from move constructor");
    numerator = other.getNumerator();
    denominator = other.getDenominator();
};

// Operators for equality (=)

Fraction &Fraction::operator=(Fraction &&other) noexcept
{
    if (this == &other)
    {
        log("Move assignment operator called on itself");
        return *this;
    }
    numerator = other.getNumerator();
    denominator = other.getDenominator();
    log("Move assignment operator called");
    return *this;
};

Fraction &Fraction::operator=(const Fraction &other)
{
    if (this == &other)
    {
        log("Copy assignment operator called on itself");
        return *this;
    }
    // error handling for overflow
    if (other.getNumerator() > MAXINT || other.getNumerator() < MININT || other.getDenominator() > MAXINT || other.getDenominator() < MININT)
    {
        throw std::overflow_error("Overflow");
    }
    log("Copy assignment operator called");
    numerator = other.getNumerator();
    denominator = other.getDenominator();
    return *this;
};

Fraction &Fraction::operator=(float other)
{
    Fraction tmp = Fraction(other);
    numerator = tmp.getNumerator();
    denominator = tmp.getDenominator();
    // error handling for overflow
    if (numerator > MAXINT || numerator < MININT || denominator > MAXINT || denominator < MININT)
    {
        log("Overflow error");
        throw std::overflow_error("Overflow");
    }
    return *this;
};

// Operators for addition (+)
Fraction Fraction::operator+(const Fraction &other) const
{

    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.denominator) +
                        static_cast<long long int>(other.numerator) * static_cast<long long int>(denominator);

    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        error_overflow();
    }

    return Fraction(num, denom);
};

Fraction Fraction::operator+(float other)
{
    float tmp = to_float();
    tmp = round(tmp * FACTOR) / FACTOR;
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp + tmp2) * FACTOR) / FACTOR;
    log("Addition operator called");
    return Fraction(tmp3);
}

Fraction Fraction::operator+=(const Fraction &other)
{
    if (this == &other)
    {
        log("Addition assignment operator called on itself");
        return *this;
    }
    *this = *this + other;
    return *this;
};

Fraction Fraction::operator+=(float other)
{

    log("Addition assignment operator called");
    *this = *this + other;
    return *this;
};

Fraction &Fraction::operator++()
{
    numerator += denominator;
    reduce(numerator, denominator);
    return *this;
};

const Fraction Fraction::operator++(int)
{

    Fraction cpy(*this);
    numerator += denominator;
    reduce(numerator, denominator);
    return cpy;
};

// Operators for subtraction (-)

Fraction Fraction::operator-(const Fraction &other) const
{
    if (this == &other)
    {

        return *this;
    }
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.denominator) -
                        static_cast<long long int>(other.numerator) * static_cast<long long int>(denominator);

    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        throw std::overflow_error("Overflow error");
    }

    return Fraction(num, denom);
};

Fraction Fraction::operator-(float other)
{
    float tmp = to_float();
    tmp = round(tmp * FACTOR) / FACTOR;
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp - tmp2) * FACTOR) / FACTOR;
    return Fraction(tmp3);
};

/**
 * @brief Operator overload for in-place subtraction of another fraction from this fraction.
 *
 * @param other The other fraction to subtract from this fraction.
 * @return A reference to the modified Fraction object after the subtraction.
 */
Fraction Fraction::operator-=(const Fraction &other)
{
    *this = *this - other;
    return *this;
    log("Subtraction assignment operator called");
};

/**
 * @brief Operator overload for in-place subtraction of a float from this fraction.
 *
 * @param other The float to subtract from this fraction.
 * @return A reference to the modified Fraction object after the subtraction.
 */
Fraction Fraction::operator-=(float other)
{
    log("Subtraction assignment operator called");
    *this = *this - other;
    return *this;
};

/**
 * @brief Operator overload for the pre-decrement of this fraction (subtract the denominator from the numerator).
 *
 * @return A reference to the modified Fraction object after the pre-decrement.
 */
Fraction &Fraction::operator--()
{
    log("Pre-decrement operator called");
    numerator -= denominator;
    reduce(numerator, denominator);
    return *this;
};

/**
 * @brief Operator overload for the post-decrement of this fraction (subtract the denominator from the numerator).
 *
 * @param An int, typically 0, used as a placeholder to differentiate between pre and post-decrement.
 * @return A copy of the Fraction object before the post-decrement.
 */
const Fraction Fraction::operator--(int)
{
    Fraction cpy(*this);
    numerator -= denominator;
    reduce(numerator, denominator);
    return cpy;
};

// ********** Operators for multiplication (*) **********
Fraction Fraction::operator*(const Fraction &other) const
{
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.numerator);
    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    if (num > MAXINT || num < MININT)
    {
        error_overflow();
    }
    if (denom > MAXINT || denom < MININT)
    {
        error_overflow();
    }

    return Fraction(num, denom);
}

/**
 * @brief Operator overload for multiplication of a fraction and a float.
 *
 * @param other The float to multiply the fraction by.
 * @return A new Fraction object that is the result of the multiplication.
 */
Fraction Fraction::operator*(float other)
{
    return *this * Fraction(other);
};

/**
 * @brief Operator overload for in-place multiplication of a fraction by another fraction.
 *
 * @param other The other fraction to multiply this fraction by.
 * @return A reference to the modified Fraction object after the multiplication.
 */
Fraction Fraction::operator*=(const Fraction &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief Operator overload for in-place multiplication of a fraction by a float.
 *
 * @param other The float to multiply the fraction by.
 * @return A reference to the modified Fraction object after the multiplication.
 */
Fraction Fraction::operator*=(float other)
{
    *this = *this * other;
    return *this;
}

// ********** Operators for division (/) **********
Fraction Fraction::operator/(const Fraction &other) const
{
    if (other.getNumerator() == 0)
    {
        error_zero();
    }

    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.getDenominator());
    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.getNumerator());

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {

        error_overflow();
    }

    return Fraction(num, denom);
};

Fraction Fraction::operator/(float other)
{
    if (other == 0)
    {
        error_zero();
    }
    float tmp = to_float();
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp / tmp2) * FACTOR) / FACTOR;
    return Fraction(tmp3);
};

Fraction Fraction::operator/=(const Fraction &other)
{
    if (other.getNumerator() == 0)
    {
        error_zero();
    }
    *this = *this / other;
    return *this;
};

Fraction Fraction::operator/=(float other)
{
    if (other == 0)
    {
        error_zero();
    }
    *this = *this / other;
    return *this;
};

// ********** Operators for equality-checking (==, !=) **********
bool Fraction::operator==(const Fraction &other) const
{
    float val = to_float();
    float otherVal = other.to_float();
    return round(val * FACTOR) / FACTOR == round(otherVal * FACTOR) / FACTOR;
};

bool Fraction::operator==(float other)
{
    float val = to_float();
    return round(val * FACTOR) / FACTOR == round(other * FACTOR) / FACTOR;
};

bool Fraction::operator!=(const Fraction &other) const
{
    if (other.getNumerator() == 0)
    {
        error_zero();
    }
    return !(*this == other);
};

bool Fraction::operator!=(float other)
{
    if (other == 0)
    {
        error_zero();
    }
    return !(*this == other);
};

/**
 * @brief Operator overload for comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if this fraction is greater than the other fraction, false otherwise.
 */
bool Fraction::operator>(const Fraction &other) const
{
    if (other.getNumerator() == 0)
    {
        error_zero();
    }
    float val = to_float();
    if (val == 0)
    {
        return false;
    }

    float otherVal = other.to_float();
    return (val > otherVal);
}

/**
 * @brief Operator overload for comparison of a fraction and a float.
 *
 * @param other The float to compare to.
 * @return true if this fraction is greater than the float, false otherwise.
 */
bool Fraction::operator>(float other)
{
    if (other == 0)
    {
        error_zero();
    }
    float val = to_float();
    return (val > other);
}

/**
 * @brief Operator overload for comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if this fraction is less than the other fraction, false otherwise.
 */
bool Fraction::operator<(const Fraction &other) const
{
    float val = to_float();
    float otherVal = other.to_float();
    return (val < otherVal);
}

/**
 * @brief Operator overload for comparison of a fraction and a float.
 *
 * @param other The float to compare to.
 * @return true if this fraction is less than the float, false otherwise.
 */
bool Fraction::operator<(float other)
{
    float val = to_float();
    return (val < other);
}

/**
 * @brief Operator overload for comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if this fraction is greater than or equal to the other fraction, false otherwise.
 */
bool Fraction::operator>=(const Fraction &other) const
{
    float val = to_float();
    float otherVal = other.to_float();
    return (val >= otherVal);
}

/**
 * @brief Operator overload for comparison of a fraction and a float.
 *
 * @param other The float to compare to.
 * @return true if this fraction is greater than or equal to the float, false otherwise.
 */
bool Fraction::operator>=(float other)
{
    if (denominator == 0)
    {
        error_zero();
    }

    float val = to_float();
    return (val >= other);
}

/**
 * @brief Operator overload for comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if this fraction is less than or equal to the other fraction, false otherwise.
 */
bool Fraction::operator<=(const Fraction &other) const
{
    if (denominator == 0 || other.denominator == 0)
    {
        error_zero();
    }

    float val = to_float();
    float otherVal = other.to_float();
    return (val <= otherVal);
}

/**
 * @brief Operator overload for comparison of a fraction and a float.
 *
 * @param other The float to compare to.
 * @return true if this fraction is less than or equal to the float, false otherwise.
 */
bool Fraction::operator<=(float other)
{
    if (denominator == 0)
    {
        error_zero();
    }

    float val = to_float();
    return (val <= other);
}

/**
 * @brief Converts the fraction to a string representation.
 *
 * @return A string representation of the fraction in the format "numerator/denominator".
 */
Fraction::operator std::string() const
{

    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

// help functions
// timing functions
/**
 * @brief Returns the current time in milliseconds.
 *
 * @return The current time in milliseconds.
 */
long long int Fraction::get_time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/**
 * @brief Returns the current time in microseconds.
 *
 * @return The current time in microseconds.
 */
long long int Fraction::get_time_micro()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// print message
/**
 * @brief Prints a message to the console.
 *
 * @param message The message to print.
 */
void Fraction::print_message(std::string message)
{
    std::cout << message << std::endl;
}


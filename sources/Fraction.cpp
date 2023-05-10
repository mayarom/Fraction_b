#include "Fraction.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <math.h>
#include <stdexcept>

using namespace ariel;

int MAXINT = std::numeric_limits<int>::max();
int MININT = std::numeric_limits<int>::min();

/********** Constructors and destructors **********/

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
    numerator = value * devider;
    denominator = devider;
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
    numerator = value * devider;
    denominator = devider;
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

    numerator = other.getNumerator();
    denominator = other.getDenominator();
};

// ********** Operators for equality (=) **********
Fraction &Fraction::operator=(Fraction &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    numerator = other.getNumerator();
    denominator = other.getDenominator();
    return *this;
};

Fraction &Fraction::operator=(const Fraction &other)
{
    if (this == &other)
    {
        return *this;
    }
    // error handling for overflow
    if (other.getNumerator() > MAXINT || other.getNumerator() < MININT || other.getDenominator() > MAXINT || other.getDenominator() < MININT)
    {
        throw std::overflow_error("Overflow");
    }
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
        throw std::overflow_error("Overflow");
    }
    return *this;
};

// ********** Operators for addition (+) **********
Fraction Fraction::operator+(const Fraction &other) const
{
    
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.denominator) +
                        static_cast<long long int>(other.numerator) * static_cast<long long int>(denominator);

    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        throw std::overflow_error("Overflow error");
    }
    return Fraction(num, denom);
};

Fraction Fraction::operator+(float other)
{
    float tmp = to_float();
    tmp = round(tmp * devider) / devider;
    float tmp2 = round(other * devider) / devider;
    float tmp3 = round((tmp + tmp2) * devider) / devider;
    return Fraction(tmp3);
};

Fraction Fraction::operator+=(const Fraction &other)
{
    *this = *this + other;
    return *this;
};

Fraction Fraction::operator+=(float other)
{
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

// ********** Operators for subtraction (-) **********
Fraction Fraction::operator-(const Fraction &other) const
{
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
    tmp = round(tmp * devider) / devider;
    float tmp2 = round(other * devider) / devider;
    float tmp3 = round((tmp - tmp2) * devider) / devider;
    return Fraction(tmp3);
};

Fraction Fraction::operator-=(const Fraction &other)
{
    *this = *this - other;
    return *this;
};

Fraction Fraction::operator-=(float other)
{
    *this = *this - other;
    return *this;
};

Fraction &Fraction::operator--()
{
    numerator -= denominator;
    reduce(numerator, denominator);
    return *this;
};

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

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        throw std::overflow_error("Overflow error");
    }

    return Fraction(num, denom);
}

Fraction Fraction::operator*(float other)
{
    return *this * Fraction(other);
};

Fraction Fraction::operator*=(const Fraction &other)
{
    *this = *this * other;
    return *this;
}

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
        throw std::runtime_error("Can't divide by zero");
    }

    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.getDenominator());
    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.getNumerator());

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        throw std::overflow_error("Overflow error");
    }
    return Fraction(num, denom);
};

Fraction Fraction::operator/(float other)
{
    if (other == 0)
    {
        throw std::runtime_error("Can't divide by zero");
    }
    float tmp = to_float();
    float tmp2 = round(other * devider) / devider;
    float tmp3 = round((tmp / tmp2) * devider) / devider;
    return Fraction(tmp3);
};

Fraction Fraction::operator/=(const Fraction &other)
{
    if (other.getNumerator() == 0)
    {
        throw std::runtime_error("Can't divide by zero");
    }
    *this = *this / other;
    return *this;
};

Fraction Fraction::operator/=(float other)
{
    if (other == 0)
    {
        throw std::runtime_error("Can't divide by zero");
    }
    *this = *this / other;
    return *this;
};

// ********** Operators for equality-checking (==, !=) **********
bool Fraction::operator==(const Fraction &other) const
{
    float val = to_float();
    float otherVal = other.to_float();
    return round(val * devider) / devider == round(otherVal * devider) / devider;
};

bool Fraction::operator==(float other)
{
    float val = to_float();
    return round(val * devider) / devider == round(other * devider) / devider;
};

bool Fraction::operator!=(const Fraction &other) const
{
    return !(*this == other);
};

bool Fraction::operator!=(float other)
{
    if (other == 0)
    {
        throw std::runtime_error("Can't divide by zero");
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
    float val = to_float();
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
        throw std::runtime_error("Division by zero in comparison");
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
        throw std::runtime_error("Division by zero in comparison");
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
        throw std::runtime_error("Division by zero in comparison");
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

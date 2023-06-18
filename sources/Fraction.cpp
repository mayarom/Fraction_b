/**
 * @file Fraction.cpp
 * @brief Implementation file for the Fraction class.
 *
 * This file was written by Maya Rom, ID: 207485251. It contains the implementation of the Fraction class,
 * which represents a fraction with numerator and denominator. It provides various arithmetic and comparison
 * operations, as well as conversion functions to float and integer values. The class handles error cases
 * such as division by zero, overflow, and invalid input, and provides appropriate exception handling. The
 * Fraction class is designed to be used for precise fractional calculations and provides methods for
 * simplifying fractions to their simplest form.
 */

#include "Fraction.hpp"

using namespace ariel;

// MAXINT and MININT are used for overflow error handling
const int MAXINT = std::numeric_limits<int>::max();
const int MININT = std::numeric_limits<int>::min();

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
        // Throw an exception if the denominator is zero
        throw std::invalid_argument("Denominator can't be zero");
    }

    // Error handling for overflow
    if (input_numerator > MAXINT || input_numerator < MININT || input_denominator > MAXINT || input_denominator < MININT)
    {
        // Throw an exception if overflow occurs
        throw std::overflow_error("Overflow");
    }

    // Log a message indicating the creation of a fraction from integer numerator and denominator
    log("Creating fraction from int numerator and denominator");

    // Reduce the fraction to its simplest form
    reduce(input_numerator, input_denominator);

    // Assign the numerator and denominator to the object's member variables
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
    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (value > static_cast<float>(MAXINT) || value < static_cast<float>(MININT))
    {
        // Throw an exception if overflow occurs
        throw std::overflow_error("Overflow");
    }

    // Log a message indicating the creation of a fraction from a double value
    log("Creating fraction from double value");

    // Convert the double value to a fraction by multiplying it by a suitable factor
    numerator = value * FACTOR;
    denominator = FACTOR;

    // Reduce the fraction to its simplest form
    reduce(numerator, denominator);
}

/**
 * @brief Constructs a new Fraction object from a float value.
 *
 * @param value The value to convert to a fraction.
 */
Fraction::Fraction(float value)
    : is_negative(false) // Initialize is_negative to false
{
    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (value > static_cast<float>(MAXINT) || value < static_cast<float>(MININT))
    {
        // Throw an exception if overflow occurs
        throw std::overflow_error("Overflow");
    }

    // Log a message indicating the creation of a fraction from a float value
    log("Creating fraction from float value");

    // Convert the float value to a fraction by multiplying it by a suitable factor
    numerator = value * FACTOR;
    denominator = FACTOR;

    // Reduce the fraction to its simplest form
    reduce(numerator, denominator);
}

/**
 * @brief Copy constructor for Fraction objects.
 *
 * @param other The Fraction object to copy.
 */
Fraction::Fraction(const Fraction &other)
{
    // Check if the object is being copied to itself
    if (this == &other)
    {
        return; // No need to perform the copy
    }

    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (other.getNumerator() > MAXINT || other.getNumerator() < MININT || other.getDenominator() > MAXINT || other.getDenominator() < MININT)
    {
        // Throw an exception if overflow occurs
        throw std::overflow_error("Overflow");
    }

    // Log a message indicating the creation of a fraction from the copy constructor
    log("Creating fraction from copy constructor");

    // Copy the numerator and denominator from the other Fraction object
    numerator = other.getNumerator();
    denominator = other.getDenominator();
}

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
    // Log a message indicating the creation of a fraction from the move constructor
    log("Creating fraction from move constructor");

    // Move the numerator and denominator from the other Fraction object
    numerator = other.getNumerator();
    denominator = other.getDenominator();
}

// Operators for equality (=)
Fraction &Fraction::operator=(Fraction &&other) noexcept
{
    // Check if the object is being move-assigned to itself
    if (this == &other)
    {
        log("Move assignment operator called on itself");
        return *this;
    }

    // Move the numerator and denominator from the other Fraction object
    numerator = other.getNumerator();
    denominator = other.getDenominator();

    // Log a message indicating the move assignment operator has been called
    log("Move assignment operator called");

    return *this;
}

Fraction &Fraction::operator=(const Fraction &other)
{
    // Check if the object is being copy-assigned to itself
    if (this == &other)
    {
        log("Copy assignment operator called on itself");
        return *this;
    }

    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (other.getNumerator() > MAXINT || other.getNumerator() < MININT || other.getDenominator() > MAXINT || other.getDenominator() < MININT)
    {
        // Throw an exception if overflow occurs
        throw std::overflow_error("Overflow");
    }

    // Log a message indicating the copy assignment operator has been called
    log("Copy assignment operator called");

    // Copy the numerator and denominator from the other Fraction object
    numerator = other.getNumerator();
    denominator = other.getDenominator();

    return *this;
}

Fraction &Fraction::operator=(float other)
{
    // Create a temporary Fraction object from the float value
    Fraction tmp = Fraction(other);

    // Assign the numerator and denominator from the temporary Fraction object
    numerator = tmp.getNumerator();
    denominator = tmp.getDenominator();

    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (numerator > MAXINT || numerator < MININT || denominator > MAXINT || denominator < MININT)
    {
        // Log an overflow error and throw an exception
        log("Overflow error");
        throw std::overflow_error("Overflow");
    }

    return *this;
}

// Operators for addition (+)
Fraction Fraction::operator+(const Fraction &other) const
{
    // Perform the addition using long long integers to avoid overflow
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.denominator) +
                        static_cast<long long int>(other.numerator) * static_cast<long long int>(denominator);

    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    // Error handling for overflow
    int MAXINT = std::numeric_limits<int>::max();
    int MININT = std::numeric_limits<int>::min();

    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        // Call an error handling function for overflow
        error_overflow();
    }

    // Create and return a new Fraction object representing the sum
    return Fraction(num, denom);
}

Fraction Fraction::operator+(float other)
{
    // Convert the Fraction object to a float value
    float tmp = to_float();

    // Round the float values to the desired precision
    tmp = round(tmp * FACTOR) / FACTOR;
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp + tmp2) * FACTOR) / FACTOR;

    // Log a message indicating the addition operator has been called
    log("Addition operator called");

    // Create and return a new Fraction object representing the sum
    return Fraction(tmp3);
}

Fraction Fraction::operator+=(const Fraction &other)
{
    // Check if the object is being added to itself
    if (this == &other)
    {
        log("Addition assignment operator called on itself");
        return *this;
    }

    // Use the addition operator to perform the addition
    *this = *this + other;

    return *this;
}

Fraction Fraction::operator+=(float other)
{
    // Log a message indicating the addition assignment operator has been called
    log("Addition assignment operator called");

    // Use the addition operator to perform the addition
    *this = *this + other;

    return *this;
}

Fraction &Fraction::operator++()
{
    // Increment the Fraction object by adding the denominator to the numerator
    numerator += denominator;

    // Reduce the fraction to its simplest form
    reduce(numerator, denominator);

    // Return a reference to the modified Fraction object
    return *this;
}

const Fraction Fraction::operator++(int)
{
    // Create a copy of the Fraction object
    Fraction cpy(*this);

    // Increment the Fraction object by adding the denominator to the numerator
    numerator += denominator;

    // Reduce the fraction to its simplest form
    reduce(numerator, denominator);

    // Return the original copy of the Fraction object
    return cpy;
}

/**
 * @brief Operator overload for subtraction of another fraction from this fraction.
 *
 * @param other The other fraction to subtract from this fraction.
 * @return A new Fraction object that is the result of the subtraction.
 */
Fraction Fraction::operator-(const Fraction &other) const
{
    // Check if subtracting the fraction from itself
    if (this == &other)
    {
        return *this;
    }

    // Perform subtraction of the fractions using long long int to handle potential overflow
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.denominator) -
                        static_cast<long long int>(other.numerator) * static_cast<long long int>(denominator);

    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.denominator);

    // Check for overflow after subtraction
    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        throw std::overflow_error("Overflow error");
    }

    return Fraction(num, denom);
}

/**
 * @brief Operator overload for subtraction of a float from this fraction.
 *
 * @param other The float to subtract from this fraction.
 * @return A new Fraction object that is the result of the subtraction.
 */
Fraction Fraction::operator-(float other)
{
    // Convert this fraction to a float and perform subtraction
    float tmp = to_float();
    tmp = round(tmp * FACTOR) / FACTOR;
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp - tmp2) * FACTOR) / FACTOR;
    return Fraction(tmp3);
}

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

/**
 * @brief Operator overload for division of two fractions.
 *
 * @param other The other fraction to divide by.
 * @return The result of dividing the fractions.
 */
Fraction Fraction::operator/(const Fraction &other) const
{
    // Error handling for zero numerator in the other fraction
    if (other.getNumerator() == 0)
    {
        error_zero();
    }

    // Perform the division using long long integers to avoid overflow
    long long int num = static_cast<long long int>(numerator) * static_cast<long long int>(other.getDenominator());
    long long int denom = static_cast<long long int>(denominator) * static_cast<long long int>(other.getNumerator());

    // Error handling for overflow
    if (num > MAXINT || num < MININT || denom > MAXINT || denom < MININT)
    {
        error_overflow();
    }

    // Create and return a new Fraction object representing the division result
    return Fraction(num, denom);
}

/**
 * @brief Operator overload for division of a fraction by a float.
 *
 * @param other The float to divide by.
 * @return The result of dividing the fraction by the float.
 */
Fraction Fraction::operator/(float other)
{
    // Error handling for zero denominator
    if (other == 0)
    {
        error_zero();
    }

    // Convert the fraction to a float value
    float tmp = to_float();

    // Perform the division with rounded precision
    float tmp2 = round(other * FACTOR) / FACTOR;
    float tmp3 = round((tmp / tmp2) * FACTOR) / FACTOR;

    // Create and return a new Fraction object representing the division result
    return Fraction(tmp3);
}

/**
 * @brief Operator overload for in-place division of a fraction by another fraction.
 *
 * @param other The other fraction to divide by.
 * @return Reference to the modified fraction after division.
 */
Fraction Fraction::operator/=(const Fraction &other)
{
    // Error handling for zero numerator in the other fraction
    if (other.getNumerator() == 0)
    {
        error_zero();
    }

    // Use the division operator to perform the division
    *this = *this / other;

    return *this;
}

/**
 * @brief Operator overload for in-place division of a fraction by a float.
 *
 * @param other The float to divide by.
 * @return Reference to the modified fraction after division.
 */
Fraction Fraction::operator/=(float other)
{
    // Error handling for zero denominator
    if (other == 0)
    {
        error_zero();
    }

    // Use the division operator to perform the division
    *this = *this / other;

    return *this;
}

// ********** Operators for equality-checking (==, !=) **********

/**
 * @brief Operator overload for equality comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if the two fractions are equal, false otherwise.
 */
bool Fraction::operator==(const Fraction &other) const
{
    // Convert both fractions to float values
    float val = to_float();
    float otherVal = other.to_float();

    // Compare the float values with rounded precision and return the result
    return round(val * FACTOR) / FACTOR == round(otherVal * FACTOR) / FACTOR;
}

/**
 * @brief Operator overload for equality comparison of a fraction and a float.
 *
 * @param other The float to compare to.
 * @return true if the fraction is equal to the float, false otherwise.
 */
bool Fraction::operator==(float other)
{
    // Convert the fraction to a float value
    float val = to_float();

    // Compare the float value with the given value with rounded precision and return the result
    return round(val * FACTOR) / FACTOR == round(other * FACTOR) / FACTOR;
}

/**
 * @brief Operator overload for inequality comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if the two fractions are not equal, false otherwise.
 */
bool Fraction::operator!=(const Fraction &other) const
{
    // Error handling for zero numerator in the other fraction
    if (other.getNumerator() == 0)
    {
        error_zero();
    }

    // Check if the fraction is not equal to the other fraction
    return !(*this == other);
}

bool Fraction::operator!=(float other)
{
    // Error handling for zero denominator
    if (other == 0)
    {
        error_zero();
    }

    // Check if the fraction is not equal to the given float value
    return !(*this == other);
}

/**
 * @brief Operator overload for comparison of two fractions.
 *
 * @param other The other fraction to compare to.
 * @return true if this fraction is greater than the other fraction, false otherwise.
 */
bool Fraction::operator>(const Fraction &other) const
{
    // Error handling for zero numerator in the other fraction
    if (other.getNumerator() == 0)
    {
        error_zero();
    }

    // Convert both fractions to float values
    float val = to_float();
    float otherVal = other.to_float();

    // Compare the float values and return the result
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
    // Error handling for zero denominator
    if (other == 0)
    {
        error_zero();
    }

    // Convert the fraction to a float value
    float val = to_float();

    // Compare the float value with the given value and return the result
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
    // Convert both fractions to float values
    float val = to_float();
    float otherVal = other.to_float();

    // Compare the float values and return the result
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
    // Convert the fraction to a float value
    float val = to_float();

    // Compare the float value with the given value and return the result
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
    // Convert both fractions to float values
    float val = to_float();
    float otherVal = other.to_float();

    // Compare the float values and return the result
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
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }

    // Convert the fraction to a float value
    float val = to_float();

    // Compare the float value with the given value and return the result
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
    // Error handling for zero denominators in both fractions
    if (denominator == 0 || other.denominator == 0)
    {
        error_zero();
    }

    // Convert both fractions to float values
    float val = to_float();
    float otherVal = other.to_float();

    // Compare the float values and return the result
    return (val <= otherVal);
}

/**
 * Check if the fraction is less than or equal to a given float value.
 *
 * @param other The float value to compare with.
 * @return True if the fraction is less than or equal to the given float value, false otherwise.
 * @throws ZeroDenominatorError if the denominator is zero.
 */
bool Fraction::operator<=(float other)
{
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }

    // Convert the fraction to a float value
    float val = to_float();

    // Compare the float value with the given value and return the result
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

// Getters
/**
 * Get the numerator of the fraction.
 *
 * @return The numerator of the fraction.
 * @throws ZeroDenominatorError if the denominator is zero.
 */
int ariel::Fraction::getNumerator() const
{
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }
    return numerator;
}

/**
 * Get the denominator of the fraction.
 *
 * @return The denominator of the fraction.
 * @throws ZeroDenominatorError if the denominator is zero.
 */
int ariel::Fraction::getDenominator() const
{
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }
    return denominator;
}

// To double
/**
 * Convert the fraction to a double value.
 *
 * @return The fraction as a double value.
 * @throws ZeroDenominatorError if the denominator is zero.
 */
double ariel::Fraction::to_double() const
{
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

/**
 * Convert the fraction to an integer value.
 *
 * @return The fraction as an integer value.
 * @throws ZeroDenominatorError if the denominator is zero.
 */
int ariel::Fraction::to_int() const
{
    // Error handling for zero denominator
    if (denominator == 0)
    {
        error_zero();
    }
    return numerator / denominator;
}

// Other methods

/**
 * @brief Reduces the numerator and denominator of the fraction to their simplest form.
 *
 * @param numerator The numerator of the fraction to reduce.
 * @param denominator The denominator of the fraction to reduce.
 *
 * @throws std::runtime_error if the denominator is zero.
 */
void Fraction::reduce(int &numerator, int &denominator)
{
    if (denominator == 0)
    {
        error_zero();
    }

    // Check if the numerator or denominator is negative
    bool nflag = numerator < 0;
    bool dflag = denominator < 0;

    // Make both numerator and denominator positive for simplification
    numerator *= (nflag) ? -1 : 1;
    denominator *= (dflag) ? -1 : 1;

    // Calculate the greatest common divisor (GCD) using std::__gcd
    int gcd = std::__gcd(numerator, denominator);

    // Divide both numerator and denominator by their GCD
    numerator /= gcd;
    denominator /= gcd;

    // Restore the original signs if necessary
    numerator *= (nflag) ? -1 : 1;
    denominator *= (dflag) ? -1 : 1;
}

/**
 * @brief Throws a runtime_error with the message "Can't divide by zero".
 */
void Fraction::error_zero()
{
    throw std::runtime_error("Can't divide by zero");
}

/**
 * @brief Throws a runtime_error with the message "Invalid input".
 */
void Fraction::error_invalid()
{
    throw std::runtime_error("Invalid input");
}

/**
 * @brief Throws an overflow_error with the message "Overflow".
 */
void Fraction::error_overflow()
{
    throw std::overflow_error("Overflow");
}

/**
 * @brief Converts the fraction to a float value.
 *
 * @return The float representation of the fraction.
 *
 * @throws std::runtime_error if the denominator is zero.
 */
float Fraction::to_float() const
{
    if (denominator == 0)
    {
        error_zero();
    }
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

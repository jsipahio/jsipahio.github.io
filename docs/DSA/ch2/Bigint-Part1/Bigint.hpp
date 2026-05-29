#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

const unsigned MAX_DIGITS = 512;

/**
 * The widest integer type on 64-bit computers is 8 bytes
 * This means that the largest positive integer that can be stored is: 
 * 18446744073709551615 which is 20 digits
 * There are applications where more than 20 digits are required.
 * 
 * Therefore, we create this ADT Bigint that provides all the operations
 * of a standard unsigned integer, but with the ability to support many digits
 * 
 */
class Bigint {
public:
    /**
     * Default constructor - Bigint is initialized to 0
     */
    Bigint() {}
    /**
     * Integer constructor
     * @param value - the unsigned integer value the Bigint object is initialized to
     */
    Bigint(unsigned value);
    /**
     * C-String constructor
     * @param value - the unsigned integer value (stored in a C-string) the object is initialized to
     */
    Bigint(const char value[]);

    /**
     * Overloaded operator to print the Bigint object 
     * @param out - std::ostream object reference (if a file stream, must be open)
     * @param bigint - Bigint object to be printed
     */
    friend std::ostream& operator<<(std::ostream& out, const Bigint &bigint);
    /** 
     * Overloaded operator to read a bigint object
     * @param in - std::istream object reference (if a file stream, must be open)
     * @param bigint - Bigint object that will store the result of the operation
     */
    friend std::ifstream& operator>>(std::ifstream& in, Bigint &bigint);

    /**
     * Overloaded operator to compare equality of Bigint objects
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is equal to the right-hand side
     * @returns false - Bigint on left is not equal to the right-hand side
     */
    bool operator==(const Bigint& rhs);
    /**
     * Overloaded operator to compare if left-hand Bigint is less than right-hand
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is less than the right-hand side
     * @returns false - Bigint on left is greater than or equal to the right-hand side
     */
    bool operator<(const Bigint& rhs);
    /**
     * Overloaded operator to compare if left-hand Bigint is greater than right-hand
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is greater than the right-hand side
     * @returns false - Bigint on left is less or equal to the right-hand side
     */
    bool operator>(const Bigint& rhs);
    /**
     * Overloaded operator to compare inequality of Bigint objects
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is not equal to right-hand side
     * @returns false - Bigint on left is equal to right-hand side
     */
    bool operator!=(const Bigint& rhs);
    /**
     * Overloaded operator to compare if left-hand Bigint is less or equal to than right-hand
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is less than or equal to right-hand side
     * @returns false - Bigint on left is greater than the right-hand side
     */
    bool operator<=(const Bigint& rhs);
    /**
     * Overloaded operator to compare if left-hand Bigint is greater than or equal to right-hand
     * @param rhs - Bigint object to compare with
     * @returns true - Bigint on left is greater than or equal to right-hand side
     * @returns false - Bigint on left is less than the right-hand side
     */
    bool operator>=(const Bigint& rhs);

    /**
     * Overloaded operator to add two Bigint objects
     * @param rhs - Bigint object to add to left hand
     * @return - Bigint that is sum of two operands
     */
    Bigint operator+(const Bigint& rhs) const;
    /**
     * Overloaded operator to subtract two Bigint objects
     * @param rhs - Bigint object to subtract from left hand
     * @return - Bigint that is the difference of two operands
     * @exception - Throws exception if rhs is greater than calling object, i.e., there cannot be a negative result
     */
    Bigint operator-(const Bigint& rhs) const;
    /**
     * Overloaded operator to multiply two Bigint objects
     * @param rhs - Bigint object to multiply with left hand
     * @return - Bigint that is product of two operands 
     */
    Bigint operator*(const Bigint& rhs) const;
private:
    unsigned short digits[MAX_DIGITS] = {0};
};

#endif
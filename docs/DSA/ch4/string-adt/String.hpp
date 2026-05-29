
#ifndef STRING_HPP
#define STRING_HPP

#include <limits>
#include <sys/types.h>

/**
 * String ADT
 * @invariant An empty string has a length of 0, the inner data should be an array with a single character, the null terminator, `\0`
 * @invariant A string with a single character has a length of 1, and consists of that character followed by the null terminator
 * @invariant A string with more than one character's size must not exceed the maximum capacity of the length member variable
 * @invariant Access to an out of range index of the string is undefined
 * @invariant Direct writing to the index of the null terminator (the `length + 1` index) is disallowed
 */
class String {
public:
    /** 
     * Default Constructor
    */
    String();
    /** 
     * Character Constructor
     * @param c - character to create String with
    */
    String(char c);
    /** 
     * C String Constructor
     * @param cStr - C string to create String with
    */
    String(const char *cStr);
    /** 
     * Copy Constructor
     * @param other - String to copy
    */
    String(const String &other);
    /** 
     * Destructor
    */
    ~String();
    /** 
     * Overloaded Assignment Operator
     * @param rhs - String to assign from
    */
    String& operator=(String rhs);
    /** 
     * Overloaded Equal Operator
     * @param rhs - String to compare with
     * @returns true - Strings match at each index
     * @returns false - Strings have a mismatch at some index
    */
    bool operator==(const String &rhs);
    /** 
     * Overloaded Less Than Operator
     * Performs lexicographical comparison of Strings
     * Note: UPPERCASE < uppercase
     * @param rhs - String to compare with
     * @returns true - If LHS string ever has a character that is 
     *  less than the character at the same index on the RHS String
     * @returns false - otherwise
    */
    bool operator<(const String &rhs);
    /** 
     * Overloaded Assignment Concatenation
     * @param rhs - String to concatenate to calling object
     * @return String - reference to self, result of concatenating rhs
    */
    String& operator+=(const String& rhs);
    /** 
     * Overloaded Concatenation
     * @param other - String that is being concatenated with calling object
     * @return new String object that is the result of concatenation
    */
    String operator+(const String& other);
    /** 
     * Overloaded Const Subscript
     * @param index - index being accessed
     * @return character at specified index
    */
    char operator[](size_t index) const;
    /** 
     * Overloaded Subscript
     * @param index - index being accessed
     * @return reference to character at specified index
     * @exception index == length + 1, i.e., trying to access null terminator
    */
    char& operator[](size_t index);
    /** 
     * find (character)
     * @param target - char to search for
     * @returns index of target if it is found
     * @returns STRING::MAX_LENGTH if target is not found
    */
    size_t find(char target);
    /** 
     * find (String)
     * @param target - substring to search for
     * @returns index of start of target if it is found
     * @returns STRING::MAX_LENGTH if target is not found
    */
    size_t find(const String& target);
    /** 
     * substring
     * @param start - starting index of substring
     * @param end - ending index of substring
     * @returns substring from start to end (inclusing)
     *  if the range is valid
     * @returns empty string if range is invalid
    */
    String substring(size_t start, size_t end);
    /** 
     * MAX_LENGTH
     * Static Constant Field that represents
     *  the maximum length of a string
     * Also serves as an "invalid" return result for find
    */
   const static size_t MAX_LENGTH = 
    std::numeric_limits<size_t>::max();
private:
    // max width unsigned integer to store the length
    size_t length;
    // pointer to character, used to create a 
    // C string to store data
    char * str;
};

#endif
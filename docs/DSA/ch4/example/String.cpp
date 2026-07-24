#include "String.hpp"

String::String() {
    currentLength = 0;
    str[0] = 0;
}

String::String(const char *cStr) {
    size_t len = 0;
    // find length of the C-string
    while (cStr[len] != 0 && len < MAX_STRING_SIZE) ++len;
    
    // copy characeters
    for (int i = 0; i < len; ++i) {
        str[i] = cStr[i];
    }
    // ensure last char is null
    str[len] = 0;
}

bool String::operator==(const String &rhs)
{
    // if lengths don't match, not equal
    if (currentLength != rhs.currentLength) return false;

    // check every char
    for (size_t i = 0; i < currentLength; ++i) {
        if (str[i] != rhs.str[i]) return false;
    }
    return true;
}

bool String::operator<(const String &rhs)
{
    return false;
}

char String::operator[](size_t index) const
{
    return 0;
}

char &String::operator[](size_t index)
{
    // TODO: insert return statement here
}

size_t String::length() const
{
    return size_t();
}

String String::operator+(const String &rhs) const
{
    return String();
}

String &String::operator+=(const String &rhs)
{
    // TODO: insert return statement here
}

void String::append(const String &other)
{
}

size_t String::find(char target, size_t start) const
{
    return size_t();
}

size_t String::find(const String &target, size_t start) const
{
    return size_t();
}

String String::substring(size_t start, size_t end) const
{
    return String();
}

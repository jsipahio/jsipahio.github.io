#ifndef STATIC_STRING_HPP
#define STATIC_STRING_HPP

#include <sys/types.h>

constexpr static size_t MAX_STRING_SIZE = 256;

class String {
public:
    String();
    String(const char *cStr);
    
    bool operator==(const String& rhs);
    bool operator<(const String& rhs);

    char operator[](size_t index) const;
    char& operator[](size_t index);

    size_t length() const;

    String operator+(const String& rhs) const;
    String& operator+=(const String& rhs);

    void append(const String& other);

    size_t find(char target, size_t start = 0) const;
    size_t find(const String& target, size_t start = 0) const;
    String substring(size_t start, size_t end) const;
private:
    size_t currentLength;
    char str[MAX_STRING_SIZE];
};

#endif

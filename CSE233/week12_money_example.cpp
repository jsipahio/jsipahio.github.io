#include <iostream>
#include <string>

class Money {
public:
    // constructor, default values of $0.00
    Money(unsigned long d = 0, unsigned short c = 0);

    // comparison operators, should always be const
    bool operator==(const Money& rhs) const;
    bool operator<(const Money& rhs) const;

    // assignment operators
    Money& operator+=(const Money& rhs);
    Money& operator-=(const Money& rhs);

    // arithmetic operators
    Money operator+(const Money& rhs) const;
    Money operator-(const Money& rhs) const;

    // other members
    void addDollars(unsigned long d);
    void addCents(unsigned long c);
    void print() const;
    std::string toString() const;
private:
    // the dollar amount, we use a very large data type
    unsigned long dollars;
    // cents only range from 0 to 100, so we can use the 
    // smallest integer type, short
    unsigned short cents;
};

// techically, these could be members as well, but they
// can be implemented as free functions using == and <
bool operator!=(const Money& lhs, const Money& rhs);
bool operator<=(const Money& lhs, const Money& rhs);
bool operator>(const Money& lhs, const Money& rhs);
bool operator>=(const Money& lhs, const Money& rhs);

int main() {
    Money m0;
    Money m1(20);
    Money m2(13, 2);
 
    m0.print();
    std::cout << "\n";
    m1.print();
    std::cout << "\n";
    m2.print();
    std::cout << "\n";

    Money m3 = m0 + m1;
    Money m4 = m1 + m2;
    Money m5 = m1 - m2;

    m0.print();
    std::cout << "\n";
    m1.print();
    std::cout << "\n";
    m2.print();
    std::cout << "\n";
    m3.print();
    std::cout << "\n";
    m4.print();
    std::cout << "\n";
    m5.print();
    std::cout << "\n";

    if (m0 < m1) {
        std::cout << "m0 is less than m1\n";
    }
    else {
        std::cout << "m0 is not less than m1\n";
    }

    if (m0 == m5) {
        std::cout << "m0 is equal to m5\n";
    }
    else {
        std::cout << "m0 is not equal to m5\n";
    }
    if (m4 > m5) {
        std::cout << "m4 is greater than m5\n";
    }
    else {
        std::cout << "m4 is not greater than m5\n";
    }

    return 0;
}

bool operator!=(const Money& lhs, const Money& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Money& lhs, const Money& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Money& lhs, const Money& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Money& lhs, const Money& rhs) {
    return !(lhs < rhs);
}

// implement constructor
Money::Money(unsigned long d, unsigned short c) {
    dollars = d;
    // handle case where cents is greater than 100
    // if the cents is less than 100, these won't make make a difference
    dollars += c / 100;
    cents = c % 100;
}

// implement comparison operators
bool Money::operator==(const Money& rhs) const {
    // if all the fields are the same, the money objects are equal
    return (dollars == rhs.dollars) &&
           (cents == rhs.cents);
}

bool Money::operator<(const Money& rhs) const {
    // if the dollars are less than rhs's dollars
    // this is less than the rhs
    if (dollars < rhs.dollars) return true;
    // if both dollar amounts are equal, we need to compare cents
    else if (dollars == rhs.dollars) {
        if (cents < rhs.cents) return true;
        else return false;
    }
    // otherwise, rhs.dollars are less and rhs is less overall
    else return false;
}

// implement the assignment operators
Money& Money::operator+=(const Money& rhs) {
    // add the rhs cents
    cents += rhs.cents;
    // add the rhs dollars
    dollars += rhs.dollars;
    // if the cents are now over 100, this will handle the rollover
    dollars += cents / 100;
    cents %= 100;

    return *this;
}

Money& Money::operator-=(const Money& rhs) {
    // rather than actually handling negatives, just force 
    // the amount to 0
    if (dollars < rhs.dollars) {
        dollars = 0;
        cents = 0;
    }
    else if (dollars == rhs.dollars) {
        if (cents < rhs.cents) {
            dollars = 0;
            cents = 0;
        }
        else {
            dollars = 0;
            cents -= rhs.cents;
        }
    }
    else {
        dollars -= rhs.dollars;
        if (rhs.cents < cents) {
            cents -= rhs.cents;
        }
        else {
            if (cents == 0) {
                cents = 100 - rhs.cents;
            }
            else {
                cents = rhs.cents - cents;
            }
            --dollars;
        }
    }

    return *this;
}

// implement the arithmetic operators
Money Money::operator+(const Money& rhs) const {
    Money returnValue(dollars, cents);
    returnValue += rhs;
    return returnValue;
}

Money Money::operator-(const Money& rhs) const {
    Money returnValue(dollars, cents);
    returnValue -= rhs;
    return returnValue;
}

// other members
void Money::addDollars(unsigned long d) {
    dollars += d;
}

void Money::addCents(unsigned long c) {
    cents += c;
    dollars += c / 100;
    cents %= 100;
}

void Money::print() const {
    std::cout << '$' << dollars << '.' 
    << cents / 10 << cents % 10;
}

std::string Money::toString() const {
    std::string str = "$";
    std::string dollarStr = std::to_string(dollars);
    char centStr[3];
    centStr[0] = cents / 10;
    centStr[1] = cents % 10;
    str += dollarStr;
    str += ".";
    str += centStr;
    return str;
}

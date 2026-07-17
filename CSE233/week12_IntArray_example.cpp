#include <iostream>
#include <string>

const int MAX_ARRAY_SIZE = 256; 

class IntArray {
public:
    IntArray();
    int maxSize() const;
    int size() const;
    bool empty() const;
    bool full() const;
    // append returns true if there was room to add a new value
    // or false otherwise
    bool append(int value);
    // overloaded subscript operators
    // this one is const (read only)
    int operator[](int i) const;
    // this one returns a reference,
    // so it can be used to update the value in the array
    int& operator[](int i);
    // member function, no parameter
    void printArray() const;
    // friend function, has a parameter
    friend void printArray(const IntArray &array);
    // overloaded insertion operator
    friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
    // overloaded extraction operator
    friend std::istream& operator>>(std::istream& in, IntArray& array);
private:
    int data[MAX_ARRAY_SIZE];
    int currentSize;
};

int main() {
    IntArray array1;
    for (int i = 0; i < 10; ++i) {
        array1.append(i);
    }
    for (int i = 0; i < array1.size(); ++i) {
        // using operator[] to print the values
        std::cout << array1[i] << "\n";
    }
    // using operator[] to modify a value
    array1[10] = 10;
    std::cout << array1[10] << "\n";
    
    // create another IntArray
    IntArray array2;

    // use overloaded operator >>
    std::cout << "Enter integers (separated by spaces).\n";
    std::cin >> array2;

    // print array using overloaded operator <<
    std::cout << "You entered: ";
    std::cout << array2 << "\n";

    return 0;
}

IntArray::IntArray() {
    currentSize = 0;
}

int IntArray::maxSize() const {
    return MAX_ARRAY_SIZE;
}

int IntArray::size() const {
    return currentSize;
}

bool IntArray::empty() const {
    return currentSize == 0;
}

bool IntArray::full() const {
    return currentSize + 1 == MAX_ARRAY_SIZE;
}

bool IntArray::append(int value) {
    if (currentSize < MAX_ARRAY_SIZE) {
        data[currentSize] = value;
        ++currentSize;
        return true;
    }
    else {
        return false;
    }
}

int IntArray::operator[](int i) const {
    // if the index is greater than current size, 
    // the value at the index is meaningless
    if (i < currentSize) {
        return data[i];
    }
    else {
        std::cout << "Invalid index\n";
        exit(1);
    }
}

int& IntArray::operator[](int i) {
    // since this is used to write and read data
    // we can't guard it as strictly as the read only one
    if (i < MAX_ARRAY_SIZE) {
        // if the index is greater than the current size
        // update the current size to be the index
        if (currentSize < i) {
            currentSize = i;
        }
        return data[i];
    }
    else {
        std::cout << "Invalid index\n";
        exit(1);
    }
}

void IntArray::printArray() const {
    bool printComma;
    // normal member function, access member variables directly
    for (int i = 0; i < currentSize; ++i) {
        if (printComma) {
            std::cout << ", ";
        }
        std::cout << data[i];
        printComma = true;
    }
}

// friend function does not have IntArray:: or friend specifier when 
// being defined
void printArray(const IntArray &array) {
    bool printComma;
    // friends do not have direct access to class member variables
    // they can access the member variables of its parameters,
    // even if they are private, though
    for (int i = 0; i < array.currentSize; ++i) {
        if (printComma) {
            std::cout << ", ";
        }
        std::cout << array.data[i];
        printComma = true;
    }
}

std::ostream& operator<<(std::ostream& out, const IntArray& array) {
    bool printComma;

    for (int i = 0; i < array.currentSize; ++i) {
        if (printComma) {
            std::cout << ", ";
        }
        out << array.data[i];
        printComma = true;
    }

    // overloaded << and >> always return the stream 
    // that is passed as a parameter
    return out;
}

std::istream& operator>>(std::istream& in, IntArray& array) {
    std::string line;
    std::getline(in, line);
    // remove any leading spaces
    while (line[0] == ' ') {
        line.erase(0, 1);
    }
    int start = 0;
    int end = line.find(' ');
    while (end != std::string::npos) {
        // extract a number
        std::string number = line.substr(start, end - start);
        // convert it to an int and add it to the array
        array.data[array.currentSize] = std::stoi(number);
        ++(array.currentSize);
        // erase the number
        line.erase(start, end);
        // erase any extra spaces between numbers
        while (line[0] == ' ') {
            line.erase(0, 1);
        } 
        // find the end of the next number
        end = line.find(' ');
    }

    return in;
}

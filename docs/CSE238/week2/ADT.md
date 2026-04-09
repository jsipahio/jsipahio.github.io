# Abstract Data Type
### CSE238 - Data Structures and Algorithms
An Abstract Data Type is a model for how data is stored, how it is operated on, and the expected conditions for the data type. Throughout the class, we will be describing the ADT for the common data structures encountered in computer science.  

## Components of an ADT
An ADT consists of three components: operations, data, and rules. The operations define what the ADT can do. The data is the internal representation of data within the ADT. The rules, also called invariants, describe conditions that should be true for a data type no matter. Often, there are rules for certain situations, for example, if a string is empty, its length must be 0. This rule describes a certain feature of the string (its length) under a certain condition (that the string is empty). These concepts will be better explained via the following example, where we design and implement an ADT for `DateTime`.

## Designing the `DateTime` ADT
Let's learn about abstract data types, by example. For this, we'll model and implement a `DateTime` ADT. The point of the `DateTime` ADT is, as the name would suggest, to model dates and times in a computer program. Since this is an example, our `DateTime` ADT might be a bit limited, but that's fine. The point is to show what an ADT is for right now, not to develop a professional software library.

#### Operations
Below is an (ASCII-art) class diagram for the `DateTime` ADT (note that here I am providing a Model Driven Architecture style class diagram, where the attributes are the public facing attributes (assumed to have get/set methods as needed), and not reflective of the private implementation features):
```
----------------------------------
|            DateTime            |
|--------------------------------|
| +second: unsigned int          |
| +minute: unsigned int          |
| +hour:   unsigned int          |
| +day:    unsigned int          |
| +month:  unsigned int          |
| +year:   unsigned int          |                         
|--------------------------------|
| +operator+(int):      DateTime | 
| +operator-(DateTime): int      |
| +__now__():           DateTime |
----------------------------------
```
So, the "fields" in the middle of the diagram, I'm actually going to refer to those as attributes. These may or may not be the private fields of the class that implements the ADT. But, they are the data we want outside users of the ADT to think of as representing the data of the ADT. Our `DateTime` ADT could be considered a Plain Old Data Type (POD). It doesn't offer much in the way of complex functionality. It is mostly data and some simple arithmetic operations. But for an example, that's fine.

#### Data Representation
We have our class diagram that defines the public interface and operations for our class. Now, we need to decide how to represent the data. We have attributes for the seconds, minutes, etc. We could create a private field for each of these. However, this requires storing many fields, which would all need to be checked and updated each time a change is made to the Date or Time. If we observe the `Clock` class from last week, we'll notice that rather than storing the hours, minutes, and seconds separately, we only stored the seconds since midnight, then computed hours and minutes when we needed. We can use that approach here, as well. However, we need a reference point. The current time is always changing, so using the current time as a reference point would not work. Many systems use the "Unix Epoch", which is midnight, January 1st, 1970 UTC, as a reference point for dates and times.  
  
Note that the point in time we choose as a reference, and even using seconds since a reference time, is a totally internal design decision, and has no impact on the interface that users of our `DateTime` use. That is the point of an ADT. The user does not need to know any of the implementation details, only what the ADT is (public attributes) and what it does (public methods). The user does not care if the attribute `hours` is stored as a private field called `hours`, or if we computed from the seconds since the Unix Epoch. All they need to know is that they can access the `hours` of a `DateTime` object.  

#### Rules/Axioms
The rules describe conditions that should be checked for to ensure the correct operation of the ADT. For example, the `now()` method returns the current date and time in a `DateTime` object at the moment the method is called. The attributes all return `unsigned int`, meaning they always refer to time in a positive context (note that if we wanted to have dates and times before the Unix Epoch, we would need to model it using negative seconds internally to the class). The rules/axioms basically define expected behavior of the ADT, and specify misuse conditions where the ADT may raise an error or have undefined behavior.

## Implementing the `DateTime` ADT
Now that we have sketched out the design for `DateTime`, we will realize it in C++. ADTs are implemented as classes in C++. So, we will have a class `DateTime` that implements the required methods and attributes, uses a private member `seconds` to keep track of time, and whose methods will follow the rules and axioms we discussed for the ADT. We will start with the class declaration, which will be contained in `DateTime.hpp`. (Remember, comments in the below code represent my thoughts as writing the code, not the doc comments that should be there. View the included code in the `DateTime-example.zip` file to see the correct doc comments.)   
*DateTime.hpp*
```C++
// so, first, we need the include guards
#ifndef DATETIME_HPP
#define DATETIME_HPP

// I'm going to implement DateTime as a wrapper around the 
// C standard time operations, so we need to include the 
// sys/types.h header for the standard library types
#include <sys/types.h>
// I want to include a toString method for printing, so
// we need to include string as well.
#include <string>

// I'm using better name for tm struct that is 
// defined in the sys/types.h and time.h headers
// The standard library types, especially in C
// do not have the most descriptive names...
// So, I am renaming the tm struct to TimeParts 
typedef tm TimeParts;

// here I'm declaring the DateTime class
class DateTime {
// I prefer to start with the public section
// most C++ code you see does as well
public:
    // For a plain old data type like this, you always want to
    // have a default constructor. People should be able to write:
    // DateTime dateTime;
    // to create an instance of the class, and know exactly what value
    // and state the DateTime object has.
    // In this case, we will set it to the Unix Epoch, which is pretty
    // standard for "null" times
    DateTime();
    // This constructor let's users pass a TimeParts struct that 
    // specifies the days, year, hour, etc. for a DateTime object
    // Since the C struct "tm" already does this, and is used for 
    // accessing the standard library time functions, I'm reusing it here
    // As stated above, I gave it the more descriptive TimeParts name
    DateTime(TimeParts parts);
    // this function returns the current time whenever it is called.
    // Since it is creating a new object and returning it, and not
    // operating on the fields or state of a "calling" object, 
    // this function is marked static
    static DateTime now();
    
    // this function returns the number of seconds between two DateTime objects
    time_t operator-(const DateTime &rhs) const;
    // this function adds a number of seconds to a DateTime object
    DateTime operator+(time_t rhs) const;
    // this function compares if two DateTime objects are equal
    bool operator==(const DateTime &rhs) const;
    // this function compares if the DateTime object on the left occurs
    // before the datetime object on the right
    bool operator<(const DateTime &rhs) const;
    
    // not much explanation needed for these
    // they are simple accessor methods that return what their name suggests
    unsigned int second() const;
    unsigned int minute() const;
    unsigned int hour() const;
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;

    // again, simple accessor method to update the values of the DateTime object's "fields"
    void second(unsigned int s);
    void minute(unsigned int m);
    void hour(unsigned int h);
    void day(unsigned int d);
    void month(unsigned int m);
    void year(unsigned int y);

    // this function returns a standard library string representation
    // of the DateTime object using a provided format.
    // There is also a default format provided that provides the US style date
    // with a military time
    std::string toString(std::string format = "%m/%d/%Y %H:%M:%S");
// the private section comes at the end
private:
    // there are a lot of ways to go about this
    // we could have stored the year/month/day/hour/minute/second
    // as individual fields, but, since the standard library
    // date and time functions use the seconds since the Unix Epoch
    // that is how we are going to represent the date and time
    // internally to our class.
    time_t seconds;
};

#endif

```
Now let's move to implementing the class. We'll do so in a file called `DateTime.cpp`.   
*DateTime.cpp*
```C++
// we need ctime to access the standard library functions 
// for manipulating date/time
#include <ctime>
// we need to include the DateTime.hpp file to have access to 
// the declaration of our DateTime class
// the sys/types.h and string headers are also chained into this include
#include "DateTime.hpp"

// constructors don't have a return type,
// so we just have DateTime::DateTime()
DateTime::DateTime() {
    // since our internal representation is seconds since the Unix Epoch
    // and we defined our default constructor as setting the object to 
    // the Unix Epoch, we just set seconds to 0
    seconds = 0;
}

// Here, we have the constructor that takes a TimeParts object as its parameter
DateTime::DateTime(TimeParts parts) {
    // to make the DateTime class as portable as possible, we will use
    // GMT (aka UTC) times
    // the standard library "timegm" function returns the seconds since the 
    // Unix Epoch UTC based on the TimeParts struct we pass it 
    // (thus, why we resued C's struct tm rather than making our own for this)
    seconds = timegm(&parts);
}

// this function returns a new DateTime object with the current date/time
// note that we only have to put static in the class declaration (header file)
// and cannot mark it as static here
DateTime DateTime::now() {
    // this gets the system time from 
    // the C time.h library
    // passing an argument of 0 to time gets the current (local) system time
    time_t t = time(0);
    // we now convert to UTC
    TimeParts parts = *gmtime(&t);
    // return a new DateTime object
    return DateTime(parts);
    // since this function never accesses the "seconds" field of "this" object
    // it is stateless and marked as static
}

// this is the operator overload that returns the difference (in seconds)
// between two DateTime objects
time_t DateTime::operator-(const DateTime &rhs) const {
    // pretty simple due to the way we store the time
    // we can just directly subtract the seconds
    return seconds - rhs.seconds;
}

// this adds a number of seconds to a DateTime object,
// and returns a new DateTime object that is the
// original object advanced by the number of seconds
DateTime DateTime::operator+(time_t rhs) const {
    // first, we need the total seconds of the DateTime object
    // and the parameter
    time_t t = seconds + rhs;
    // then we get a TimeParts object to pass to the constructor
    TimeParts parts = *gmtime(&t);
    // we use the constructor to return a new DateTime object with the
    // correct time
    return DateTime(parts);
}

// This overloaded operator compares two DateTime objects
// to see if they are equal
bool DateTime::operator==(const DateTime& rhs) const {
    // pretty simple, same seconds since the Unix Epoch -> same date and time
    return seconds == rhs.seconds;
}

// This overloaded operator compares two DateTime objects
// to see if the one on the left (when the operator is called) is less than the right
bool DateTime::operator<(const DateTime& rhs) const {
    // again, the way we represent the date and time make this pretty simple
    // just see which one has the lower value for seconds
    return seconds < rhs.seconds;
}

// all of the accessors work the same, so I'll only explain the first one
unsigned int DateTime::second() const {
    // to be safe, since we are passing a memory address, I'm making a 
    // copy of the seconds and storing it in this variable
    time_t t = seconds;
    // get the UTC TimeParts for this number of seconds since the Unix Epoch
    // this function, gmtime returns a pointer to a TimeParts object and takes a pointer
    // to a time_t variable. Instead of creating a time_t pointer, I'm using the & to
    // pass the memory address instead
    TimeParts *timeParts = gmtime(&t);
    // returning the seconds from the TimeParts object
    // (the other accessors follow the same steps, but return the minutes, hours, etc.)
    return timeParts->tm_sec;
}

unsigned int DateTime::minute() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_min;
}

unsigned int DateTime::hour() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_hour;
}

unsigned int DateTime::day() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_mday;
}

unsigned int DateTime::month() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    return timeParts->tm_mon;
}

unsigned int DateTime::year() const {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    // the tm_year is relative to 1900
    // for some reason
    return 1900 + timeParts->tm_year;
}

// all of the mutators work the same as well
// so again, I'll only explain the first one in-depth
void DateTime::second(unsigned int s) {
    // create a copy of the seconds
    time_t t = seconds;
    // call the gmtime function, just like
    // in the accessors
    TimeParts *timeParts = gmtime(&t);
    // update the seconds (luckily, the TimeParts struct)
    // and C standard time functions automatically
    // handle over/underflow and roll over time for us
    timeParts->tm_sec = s;
    // get the seconds from the Unix epoch
    t = mktime(timeParts);
    // set seconds accordingly
    seconds = t;
}

void DateTime::minute(unsigned int m) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_min = m;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::hour(unsigned int h) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_hour = h;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::day(unsigned int d) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_mday = d;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::month(unsigned int m) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_mon = m;
    t = mktime(timeParts);
    seconds = t;
}

void DateTime::year(unsigned int y) {
    time_t t = seconds;
    TimeParts *timeParts = gmtime(&t);
    timeParts->tm_year = y;
    t = mktime(timeParts);
    seconds = t;
}

// this function returns a the Date/Time as a string
// according to a user specified format
std::string DateTime::toString(std::string format) {
    // We need a C string to store the result in
    // we'll just use a static array for this
    // if someone creates a date format longer than 1024
    // characters, that is their own fault...
    char dateTime[1024];
    // create a copy of the seconds since the Unix Epoch
    time_t t = seconds;
    // create our TimeParts struct
    TimeParts *timeParts = gmtime(&t);
    // here, we are using the standard library strftime function.
    // it needs a C-string pointer to store the result in
    // the max size the C string can be, the format string,
    // and the TimeParts to format into a string
    // since C-strings need to end with the '\0' character,
    // the size we pass the function is one smaller than the 
    // size of the array we created to store the result
    strftime(dateTime, 1023, format.c_str(), timeParts);
    return std::string(dateTime); 
}

```
We've implemented the `DateTime` class as a wrapper around the C `<time.h>` header. Converting between seconds since the Unix Epoch and actual days, months, years, etc. is actually non-trivial, so that's why we'll skip that for this example and just use the C header.  

You can view the code for this ADT in the `DateTime-example.zip` file. 

## Looking Ahead
The next lecture will cover testing for this ADT. For your lab assignment this week, you will need to implement tests for an ADT called `Bigint`. The `Bigint` ADT represents unsigned integers that are larger than the maximum size of integers. As an exercise, try developing the class diagram for the `Bigint` ADT, and try to imagine how `Bigint` might be implemented (i.e., what would the private field(s) look like).  

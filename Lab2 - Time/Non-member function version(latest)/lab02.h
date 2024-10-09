#ifndef TEST_H // Head File Guard
#define TEST_H

// TODO: Complementary work: operator+(int, Time) is missing. 
// -- CHECK(line 40) and we set a test case in test_main.cpp(line 31-32)

#include <string>
#include <iostream>
using namespace std;

#define HOURS_24 1
#define HOURS_12 0

#define INVALID_TIME_STR "time is invalid"
#define INVALID_TIME {-1, -1, -1}

#define LEFT 0
#define RIGHT 1
#define EQUAL 2

struct Time
{

    // There is no member functions in the struct.
    int hour;
    int minute;
    int second;
};

// The following are non-member functions:
ostream &operator<<(std::ostream &os, Time const &t); // MODULE: Formatted input with operator<<.
istream &operator>>(std::istream &is, Time &t);       // MODULE: Formatted input with operator>>. input: xx:xx:xx

bool is_valid(Time &t); // if valid, return true; if not, return false

std::string is_am(Time &t); // if 0<=time<=12, return am; if 13<=time<=23, return pm;

std::string to_string(Time t, const int &timeFormat); // if time is invalid, return INVALID_TIME_STR; //if timeFormat=HOURS_12, return xx:xx:xx am/pm; if timeFormat=HOURS_24, return xx:xx:xx

Time operator+(Time t, int addNumber); // MODULE: Addition with a positive integer to generate a new time N seconds into the future with operator+, like t + N
Time operator+(int addNumber, Time t); // MODULE: Addition with a positive integer to generate a new time N seconds into the future with operator+, like N + t
Time operator++(Time &t);              // MODULE: Prefix time plus (change the Time object)
Time operator++(Time &t, int);         // MODULE: Post time plus (change the Time object)

Time operator-(Time t, int minusNumber); // MODULE: Subtraction with a positive integer to give an earlier time with operator-.
Time operator--(Time &t);                // MODULE: Prefix time minus (change the Time object)
Time operator--(Time &t, int);           // MODULE: Post time minus (change the Time object)

int comparison(Time &t, const Time t1); // if a>b, return LEFT; if==b, return EQUAL; if a<b, return RIGHT
// MODULE: Comparison between two Time objects with the usual comparison operators (the following six of them reuse the MODULE 'comparison')
bool operator>(Time &t, const Time t1);  // if a>b, return true; else return false
bool operator<(Time &t, const Time t1);  // if a<b, return true; else return false
bool operator==(Time &t, const Time t1); // if a==b, return true; else return false
bool operator>=(Time &t, const Time t1); // if a>b or a==b, return true; else return false
bool operator<=(Time &t, const Time t1); // if a<b or a==b, return true; else return false
bool operator!=(Time &t, const Time t1); // if a!=b, return true; else return false

#endif

#ifndef TEST_H //Head File Guard
#define TEST_H

// TODO: Complementary work: No function should not be a part of the 
// Time struct, they should all be free functions.
// Hint: Declare them outside of the struct and give all methods a Time& t argument
// This is a pretty big deal so refactor the code to use free functions and then submit again

// TODO: Complementary work: operator+(int, Time) is missing.
// However, this is since you have member functions

#include <string>
#include <iostream>
using namespace std;

#define HOURS_24 1
#define HOURS_12 0

#define INVALID_TIME_STR "time is invalid"
#define INVALID_TIME {-1,-1,-1}

#define LEFT 0
#define RIGHT 1
#define EQUAL 2

struct Time {
	
	int hour;
    int minute;
    int second;
    
	//The following are member functions:
	bool is_valid() const;							//if valid, return true; if not, return false
	std::string is_am();							//if 0<=time<=12, return am; if 13<=time<=23, return pm;


	std::string to_string(const int& timeFormat);	//if time is invalid, return INVALID_TIME_STR; 
													//if timeFormat=HOURS_12, return xx:xx:xx am/pm; if timeFormat=HOURS_24, return xx:xx:xx
													
	void operator =(const Time t);					//copy parameter to the object

	int comparison(const Time t);					//if a>b, return LEFT; if==b, return EQUAL; if a<b, return RIGHT
    
	//MODULE: Comparison between two Time objects with the usual comparison operators (the following six of them reuse the MODULE 'comparison')
	bool operator >(const Time t);					//if a>b, return true; else return false
	bool operator <(const Time t);					//if a<b, return true; else return false
	bool operator ==(const Time t);					//if a==b, return true; else return false
    bool operator >=(const Time t);                 //if a>b or a==b, return true; else return false
	bool operator <=(const Time t);                 //if a<b or a==b, return true; else return false
	bool operator !=(const Time t);					//if a!=b, return true; else return false


	Time operator + (int addNumber); //MODULE: Addition with a positive integer to generate a new time N seconds into the future with operator+.
	Time operator ++(); //MODULE: Prefix time plus (change the Time object)
	Time operator ++(int); //MODULE: Post time plus (change the Time object)


	Time operator - (int minusNumber); //MODULE: Subtraction with a positive integer to give an earlier time with operator-.
	Time operator --(); //MODULE: Prefix time minus (change the Time object)
	Time operator --(int); //MODULE: Post time minus (change the Time object)

};

//The following are non-member functions:
ostream& operator <<(std::ostream& os, Time const& t);	// MODULE: Formatted input with operator<<.
istream& operator >>(std::istream& is, Time & t);		//MODULE: Formatted input with operator>>. input: xx:xx:xx

#endif

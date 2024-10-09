#include "lab02.h"
#include <math.h>
#include <iostream>
#include <iomanip>

// TODO: Complementary work: In the operator>> you need to make sure to check the delimeter
// for ':' both times. So both ignore variables need to be checked that they are actually a colon.
// -- CHECK(line 193-197) and we set a test case in test_main.cpp(line 67-70)

bool is_valid(Time& t) {
	if ((t.hour >= 0 && t.hour <= 23) && (t.minute >= 0 && t.minute <= 59) && (t.second >= 0 && t.second <= 59)) {
		return true;
	}
	return false;
}

std::string is_am(Time& t) {
	if (is_valid(t) == false) {
		return INVALID_TIME_STR;
	}

	if (t.hour >= 0 && t.hour <= 12) return "am";
	else return "pm";
}

std::string to_string(Time t, const int& timeFormat) {
	if (is_valid(t) == false) { //reuse MODULE is_valid()
		return INVALID_TIME_STR;
	}

	std::string hourString{};
	std::string minuteString{};
	std::string secondString{};

    //According to the requirement, complete the '0' in the tens digits on output via setw() and setfill()
	if(t.minute < 10) {
		minuteString = "0" + std::to_string(t.minute);}
	else{
		minuteString = std::to_string(t.minute);}
	if (t.second < 10){
		secondString = "0" + std::to_string(t.second);}
	else{
		secondString = std::to_string(t.second);}

	if (timeFormat == HOURS_12) {
		if (t.hour == 12) {
			hourString = std::to_string(t.hour);
			return hourString + ":" + minuteString + ":" + secondString + " am";
		}
		if (t.hour < 12) {
			t.hour < 10 ? hourString = "0" + std::to_string(t.hour) : hourString = std::to_string(t.hour);
			return hourString + ":" + minuteString + ":" + secondString + " am";
		}
		if (t.hour > 12) {
			int hourTemp = t.hour - 12;
			hourTemp < 10 ? hourString = "0" + std::to_string(hourTemp) : hourString = std::to_string(hourTemp);
			return hourString + ":" + minuteString + ":" + secondString + " pm";
		}
	}

	t.hour < 10 ? hourString = "0" + std::to_string(t.hour) : hourString = std::to_string(t.hour);
	return hourString + ":" + minuteString + ":" + secondString;
}


// By implementing overloading '== and <, the rest of the comparison operators can be implemented based on these two operators
bool operator ==(Time& t, const Time t1) {
	if (t.hour == t1.hour && t.minute == t1.minute && t.second == t1.second) return true;
	else return false;
}

bool operator <(Time& t, const Time t1) {
	if (t.hour < t1.hour ) {
		return true;
	} else if(t.hour == t1.hour && t.minute < t1.minute){ 
		return true;
	} else if (t.hour == t1.hour && t.minute == t1.minute && t.second < t1.second){
		return true;
	}
	return false;
}

// Implement the other operators based on two operators overloading above
bool operator >(Time& t, const Time t1) {
	if (!(t==t1) && !(t<t1)){ // NOT = and NOT <
		return true;
	}
	else return false;	
}

bool operator >=(Time& t, const Time t1) {
	if (!(t<t1)) return true; // NOT <
	else return false;
}

bool operator <= (Time& t, const Time t1) {
	if ((t==t1) || (t<t1)) return true; // = or <
	else return false;
}

bool operator !=(Time& t, const Time t1) {
	if (!(t==t1)) return true; // NOT =
	else return false;
}


Time operator + (Time t, int addNumber)
{
    int addSecond = (t.second+addNumber) % 60; // The number of seconds added is divided by 60 to get the balance (only used if the number of seconds + N of the original time is greater than 60)
    int addMinute = floor((t.second+addNumber) / 60);// Number of minutes added
    
    if ((t.second + addNumber) > 60)
    {
        if((t.minute+addMinute) > 60){ // The most complex scenario where hours & minutes & seconds are all changed
            int addHour =  floor((t.minute+addMinute) / 60); // Number of hours added
			Time temp = {(t.hour+addHour) % 24, (t.minute+addMinute) % 60, addSecond};
            return temp;
        }
        else{ // Minutes & seconds both changes, but doesn't affect hours
            Time temp = {t.hour % 24, t.minute+addMinute, addSecond};
            return temp;
        }
    }
    else
    {   // Only the seconds changes, not the minutes and hours.
        Time temp = {t.hour % 24, t.minute, t.second+addNumber};
        return temp;
    }
 }

Time operator+(int addNumber, Time t) {
	t = t + addNumber;
	return t;
}

Time operator ++(Time &t) { // reuse MODULE 'opearator +' 
	t = t + 1; // Change the original object
	return t;
}

Time operator ++(Time &t, int) {// reuse MODULE 'prefix opearator ++' 
	t = ++t; // Change the original object
	return t;
}

Time operator - (Time t, int minusNumber){
    Time temp;
    int totalSecond = t.hour * 3600 + t.minute * 60 + t.second;
    totalSecond = totalSecond - minusNumber;
    if (totalSecond > 0)
    {
        temp.hour =    floor(totalSecond / 3600);
        temp.minute =  floor((totalSecond % 3600) / 60);
        temp.second =  totalSecond % 60;
    }
    else
    {
        totalSecond = totalSecond % 86400; // 86400 seconds represents the time of a day, and is used here to handle the case where N is greater than the entered time
        totalSecond = 86400 + (totalSecond);
            
        temp.hour =   floor(totalSecond / 3600);
        temp.minute = floor((totalSecond % 3600) / 60);
        temp.second = totalSecond % 60;
    }
    return temp;
}

Time operator --(Time& t) { // reuse MODULE 'opearator -' 
	t = t - 1; // Change the original object
	return t;
}

Time operator --(Time& t, int) { // reuse MODULE 'prefix opearator --' 
	t = --t; // Change the original object
	return t;
}

std::ostream& operator << (std::ostream& os, Time const& t) {
	// According to the requirement, complete the '0' in the tens digits on output via setw() and setfill()
	os << std::setfill('0') << std::setw(2) << t.hour << ":" // set setfill() only once
	   << std::setw(2) << t.minute << ":" 
	   << std::setw(2) << t.second;
	return os;
}

std::istream& operator >>(std::istream& is, Time& t) {
	// Save current valid time in case that it can be recovered if we input the invalid data
	int current_hour =  t.hour;
	int current_minute = t.minute;
	int current_second = t.second; 
	
	// Read the input hour, minute, and second with ':' as the flag.
	char ignore, ignore2; // temporary store ":"
	is >> t.hour >> ignore >> t.minute >> ignore2 >> t.second; // this is new time we input
	
	// Reuse FUNCTION: is_valid()
	if (is_valid(t) == false || ignore != ':' || ignore2 != ':') {
       
	    // Recovery from previously stored data
		t.hour = current_hour;
		t.minute = current_minute;
		t.second = current_second;

		// Set fail-flag if the input value is incorrect
        is.setstate(std::ios_base::failbit);
        
		// Check wether the fail-flag is set  
		if (is.fail()) {
            std::cout << "failbit is set." << std::endl;} 
    
	}

	return is;
}

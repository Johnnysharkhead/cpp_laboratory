#include "lab02.h"
#include <math.h>
#include <iostream>
#include <iomanip>

// TODO: Complementary work: operator>> should not destroy a valid time if it
// gets invalid input.

// TODO: Complementary work: Don't repeat sticky IO manipulators.  
// Every manipulator (except setw) will "stick" until a different 
// manipulator overrides it, so it is unnecessary to repeat them. 

// TODO: Complementary work: You should only have to implement a maximum of 
// two of the comparison operators which should be used to implement the other ones. 

bool Time::is_valid() const {
	if ((hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59) && (second >= 0 && second <= 59)) {
		return true;
	}
	return false;
}

std::string Time::is_am() {
	if (is_valid() == false) {
		return INVALID_TIME_STR;
	}

	if (hour >= 0 && hour <= 12) return "am";
	else return "pm";
}

std::string Time::to_string(const int& timeFormat) {
	if (is_valid() == false) { //reuse MODULE is_valid()
		return INVALID_TIME_STR;
	}

	std::string hourString{};
	std::string minuteString{};
	std::string secondString{};

    //According to the requirement, complete the '0' in the tens digits on output via setw() and setfill()
	if(minute < 10) {
		minuteString = "0" + std::to_string(minute);}
	else{
		minuteString = std::to_string(minute);}
	if (second < 10){
		secondString = "0" + std::to_string(second);}
	else{
		secondString = std::to_string(second);}

	if (timeFormat == HOURS_12) {
		if (hour == 12) {
			hourString = std::to_string(hour);
			return hourString + ":" + minuteString + ":" + secondString + " am";
		}
		if (hour < 12) {
			hour < 10 ? hourString = "0" + std::to_string(hour) : hourString = std::to_string(hour);
			return hourString + ":" + minuteString + ":" + secondString + " am";
		}
		if (hour > 12) {
			int hourTemp = hour - 12;
			hourTemp < 10 ? hourString = "0" + std::to_string(hourTemp) : hourString = std::to_string(hourTemp);
			return hourString + ":" + minuteString + ":" + secondString + " pm";
		}
	}

	hour < 10 ? hourString = "0" + std::to_string(hour) : hourString = std::to_string(hour);
	return hourString + ":" + minuteString + ":" + secondString;
}


void Time::operator =(const Time t) {
	hour = t.hour;
	minute = t.minute;
	second = t.second;
}

int Time::comparison(const Time t) {
	if (hour > t.hour) {
		return LEFT;
	}
	else if (hour < t.hour) {
		return RIGHT;
	}
	else { //Compare the hours first, and when they are the same, compare the minutes.
		if (minute > t.minute) {
			return LEFT;
		}
		else if (minute < t.minute) {
			return RIGHT;
		}
		else { //When the number of minutes are the same in both, the seconds are finally compared
			if (second > t.second) {
				return LEFT;
			}
			else if (second < t.second) {
				return RIGHT;
			}
			else return EQUAL;
		}
	}
}

bool Time::operator >(const Time t) {
	if (comparison(t) == LEFT) return true;
	else return false;
}
bool Time::operator <(const Time t) {
	if (comparison(t) == RIGHT)return true;
	else return false;
}
bool Time::operator ==(const Time t) {
	if (comparison(t) == EQUAL) return true;
	else return false;
}
bool Time::operator >=(const Time t) {
	if (comparison(t) == EQUAL || comparison(t) == LEFT) return true;
	else return false;
}
bool Time::operator <=(const Time t) {
	if (comparison(t) == EQUAL || comparison(t) == RIGHT) return true;
	else return false;
}
bool Time::operator !=(const Time t) {
	if (comparison(t) != EQUAL)return true;
	else return false;
}


Time Time::operator + (int addNumber)
{
    int addSecond = (second+addNumber) % 60; //The number of seconds added is divided by 60 to get the balance (only used if the number of seconds + N of the original time is greater than 60)
    int addMinute = floor((second+addNumber) / 60);//Number of minutes added
    
    if ((second + addNumber) > 60)
    {
        if((minute+addMinute) > 60){ //The most complex scenario where hours & minutes & seconds are all changed
            int addHour =  floor((minute+addMinute) / 60); //Number of hours added
			Time temp = {(hour+addHour)%24, (minute+addMinute)%60, addSecond};
            return temp;
        }
        else{ //Minutes & seconds both changes, but doesn't affect hours
            Time temp = {hour%24, minute+addMinute, addSecond};
            return temp;
        }
    }
    else
    {   //Only the seconds changes, not the minutes and hours.
        Time temp = {hour%24, minute, second+addNumber};
        return temp;
    }
 }

Time Time::operator ++() { //reuse MODULE 'opearator +' 
	*this = *this + 1; //Change the original object
	return *this;
}

Time Time::operator ++(int) {//reuse MODULE 'prefix opearator ++' 
	*this = ++*this; //Change the original object
	return *this;
}

Time Time::operator - (int minusNumber){
    Time temp;
    int totalSecond = hour * 3600 + minute * 60 + second;
    totalSecond = totalSecond - minusNumber;
    if (totalSecond > 0)
    {
        temp.hour =    floor(totalSecond / 3600);
        temp.minute =  floor((totalSecond % 3600) / 60);
        temp.second =  totalSecond % 60;
    }
    else
    {
        totalSecond = totalSecond % 86400; //86400 seconds represents the time of a day, and is used here to handle the case where N is greater than the entered time
        totalSecond = 86400 + (totalSecond);
            
        temp.hour =   floor(totalSecond / 3600);
        temp.minute = floor((totalSecond % 3600) / 60);
        temp.second = totalSecond % 60;
    }
    return temp;
}

Time Time::operator --() { //reuse MODULE 'opearator -' 
	*this = *this - 1; //Change the original object
	return *this;
}

Time Time::operator --(int) { //reuse MODULE 'prefix opearator --' 
	*this = --*this; //Change the original object
	return *this;
}


std::ostream& operator << (std::ostream& os, Time const& t) {
	//According to the requirement, complete the '0' in the tens digits on output via setw() and setfill()
	os << std::setfill('0') << std::setw(2) << t.hour << ":" << std::setfill('0') << std::setw(2) << t.minute 
	<< ":" << std::setfill('0') << std::setw(2) << t.second;
	return os;
}


std::istream& operator >>(std::istream& is, Time& t) {
	//Read the input hour, minute, and second with ':' as the flag.
	char ignore;
	is >> t.hour >> ignore >> t.minute >> ignore >> t.second;
	
	//Reuse FUNCTION: is_valid()
	if (t.is_valid() == false || ignore != ':') {
        //set fail-flag if the input value is incorrect
        is.setstate(std::ios_base::failbit);
        //check wether the fail-flag is set  
		if (is.fail()) {
            std::cout << "failbit is set." << std::endl;} 
    }

	return is;
}

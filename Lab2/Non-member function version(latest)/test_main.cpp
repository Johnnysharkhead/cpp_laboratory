#define CATCH_CONFIG_MAIN
#include "lab02.h"
#include "catch.hpp"

// TODO: Complementary work: Your tests are insufficent, adding/subtracting 
// should be tested when input is a large number (such as three days 86 400*3) to  
// show whether the Time is calculated correctly. -- CHECK(line 34-38, line 91-93)

TEST_CASE("time_BASIC") {//Testing basic functions
	
	Time t{ 23,40,30 };
	CHECK(is_valid(t) == true);
	CHECK(is_am(t)  == "pm");

	t++;
	CHECK(to_string(t, HOURS_12) == "11:40:31 pm");

	++t;
	CHECK(to_string(t, HOURS_12) == "11:40:32 pm");

	t--;
	CHECK(to_string(t, HOURS_12) == "11:40:31 pm");

	--t;
	CHECK(to_string(t, HOURS_12) == "11:40:30 pm");

	Time t1 = t + 5; 
	CHECK(to_string(t1, HOURS_24) == "23:40:35");
	CHECK(to_string(t, HOURS_24) == "23:40:30");//Test if the original object will be changed after N seconds.

	Time k = 5 + t;
	CHECK(to_string(k, HOURS_24) == "23:40:35");

	Time addingT = t + 86400 * 3;
	CHECK(to_string(t, HOURS_12) == "11:40:30 pm");

	Time subtractingT = t - 86400 * 3;
	CHECK(to_string(t, HOURS_12) == "11:40:30 pm");

	// Test operator >> overload with valid data
	std::istringstream iss("17:20:33");
	Time t2{};
	iss >> t2;
	CHECK(t2.hour == 17);
	CHECK(t2.minute == 20);
	CHECK(t2.second == 33); 

	// Test operator >> overload with invalid data
	iss.str("100:900:-10");
	iss >> t2;
	// Let's verify that entering an incorrect value for an existing valid time will not destroy that time
	CHECK(t2.hour == 17);
	CHECK(t2.minute == 20);
	CHECK(t2.second == 33);


	// Test operator >> overload with invlid time .
	iss.str("");
	iss.clear();
	iss.str("27:20:33");
	Time t3{};
	iss >> t3;
	CHECK(iss.fail());

	iss.str("");
	iss.clear();
	iss.str("10:20}33");
	Time t4{};
	iss >> t4;
	CHECK(iss.fail());

	// Test operator << overload and ten-digit complement.
	Time t5{ 8,0,12 };
	std::ostringstream oss;
	oss << t5;
	CHECK(oss.str() == "08:00:12"); 

	// Test comparsion overload
	CHECK((t1 > t) == true);
	CHECK((t1 < t) == false);
	CHECK((t1 != t) == true);
	CHECK((t1 <= t) == false);
	CHECK((t1 >= t) == true);
}

TEST_CASE("time_EXECEPTION"){//Testing extreme cases

	Time t1 = { 71,2,30 };
	CHECK(is_valid(t1) == false);

	Time t2 = { 1,0,0 };
	CHECK( to_string((t2-7200), HOURS_24) == "23:00:00");   // 1:00 a.m - 2h = 23:00 
	CHECK( to_string((t2+86400), HOURS_24) == "01:00:00");  // 1:00 a.m + 24h = 1:00 

	Time t3 = { 0,0,1 };
	CHECK( to_string((t3-2), HOURS_12) == "11:59:59 pm"); // 00:00:01 a.m - 2s = 11:59:59 in 12hours format.
}




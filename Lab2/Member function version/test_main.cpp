#define CATCH_CONFIG_MAIN
#include "lab02.h"
#include "catch.hpp"

TEST_CASE("time_BASIC") {//Testing basic functions
	
	Time t{ 23,40,30 };
	CHECK(t.is_valid() == true);
	CHECK(t.is_am()  == "pm");

	t++;
	CHECK(t.to_string(HOURS_12) == "11:40:31 pm");

	++t;
	CHECK(t.to_string(HOURS_12) == "11:40:32 pm");

	t--;
	CHECK(t.to_string(HOURS_12) == "11:40:31 pm");

	--t;
	CHECK(t.to_string(HOURS_12) == "11:40:30 pm");

	Time t1 = t + 5; 
	CHECK(t1.to_string(HOURS_24) == "23:40:35");
	CHECK(t.to_string(HOURS_24) == "23:40:30");//Test if the original object will be changed after N seconds.

	CHECK((t1 > t) == true);
	CHECK((t1 < t) == false);
	CHECK((t1 != t) == true);

	//Test operator >> overload.
	std::istringstream iss("17:20:33");
	Time t2{};
	iss >> t2;
	CHECK(t2.hour == 17);
	CHECK(t2.minute == 20);
	CHECK(t2.second == 33); 

	//Test operator >> overload with invlid time .
	iss.str("");
	iss.clear();
	iss.str("27:20:33");
	Time t3{};
	iss >> t3;
	CHECK(iss.fail());

	//Test operator << overload and ten-digit complement.
	Time t4{ 8,0,12 };
	std::ostringstream oss;
	oss << t4;
	CHECK(oss.str() == "08:00:12"); 

}

TEST_CASE("time_EXECEPTION"){//Testing extreme cases

	Time t1 = { 71,2,30 };
	CHECK(t1.is_valid() == false);

	Time t2 = { 1,0,0 };
	CHECK( (t2-7200).to_string(HOURS_24) == "23:00:00");   // 1:00 a.m - 2h = 23:00 
	CHECK( (t2+86400).to_string(HOURS_24) == "01:00:00");  // 1:00 a.m + 24h = 1:00 

	Time t3 = { 0,0,1 };
	CHECK( (t3-2).to_string(HOURS_12) == "11:59:59 pm"); // 00:00:01 a.m - 2s = 11:59:59 in 12hours format.
}




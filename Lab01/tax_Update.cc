#include <iostream>
#include <iomanip>
using namespace std;

// TODO: Complementary work: Still doesn't work. The user should not be able to enter a stride less          
// than 0.01. 
// Hint: What data types are you comparing?

// Tip: Use static_cast for the 0.01 you're comparing it to. Stride is a float but what type if the numher 0.01.
// It is important you compare the same types --- CHECK (thx for your tip, I see your point)

int main() {
	float firstPrice{0};
	float lastPrice{0};
	float stride{0};
	float taxPercent{0};
	float tax{0};
	float currentPrice{0};

	int count{0};
	int time{1};

	std::cout << "INPUT PART" << std::endl;
	std::cout << "==========" << std::endl;
	
	std::cout <<"Enter first price: ";
	std::cin >> firstPrice;
	std::cout << std::endl;

	while(firstPrice < 0) {
		std::cout << "ERROR: First price must be at least 0 (zero) SEK" << std::endl;
		std::cout << "Re-enter first price: " ;
        std::cin >> firstPrice;
		std::cout << std::endl;
	}
	
	std::cout << "Enter last price : ";
	std::cin >> lastPrice;
	std::cout << std::endl;
	
	while(lastPrice < firstPrice){
		std::cout << "ERROR: Last price must be larger than the first price" << std::endl;
		std::cout << "Re-enter last price: " ;
        std::cin >> lastPrice;
		std::cout << std::endl;
	}

	std::cout << "Enter stride: ";
	std::cin >> stride;
	std::cout << std::endl;

	while(stride < static_cast<float>(0.01)) {
  		std::cout << "ERROR: Stride must be at least 0.01" << std::endl;
        std::cout << "Re-enter stride: ";
        std::cin >> stride;
        std::cout << std::endl;
    }

	std::cout << "Enter tax percent: ";
	std::cin >> taxPercent;
	std::cout << std::endl;
	while (taxPercent < 0 || taxPercent > 100) {
		std::cout << "ERROR: Tax percent must be between 0 and 100" << std::endl;
		std::cout << "Re-enter Tax: ";
		std::cin >> taxPercent;
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "TAX TABLE" << std::endl;
	std::cout << "==========" << std::endl;
	
    std::cout	<< std::setw(14) << "Price"
				<< std::setw(14) << "Tax"
				<< std::setw(25) << "Price with tax"
				<< std::endl;

	std::cout	<< std::setfill('-')
				<< std::setw(55) << ""
				<< std::endl;


	currentPrice = firstPrice;
	taxPercent = taxPercent / 100;
	
	std::cout << setfill(' ') ;
	std::cout << std::fixed << std::setprecision(2); //All values entered will be decimal numbers with no more than two decimals.
	
	count = (lastPrice - firstPrice) / stride;
	

	while (time <= (count+1)) { 
		std::cout << std::setw(15) << currentPrice;
		
		tax = currentPrice * taxPercent;
		if (tax>100000){// All values will be in the interval [-100.00, +100000.00]
			std::cout << "\nTax exceeds maximum permissible range" << std::endl;
		    break;
		}
		std::cout << std::setw(15) << tax;
		
		std::cout << std::setw(20) << currentPrice + tax;
		
		//We introduce multiplication to minimize rounding errors instead of implementing it with repeated addition like "currentPrice += stride".
		currentPrice = time * stride + firstPrice; 
		time++;
		
		std::cout << std::endl;
	}	

	return 0;
}


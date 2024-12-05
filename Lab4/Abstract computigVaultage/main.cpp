#include "lab04.h"

#include <iostream>


// TODO: Complementary work: Compiling your code with the  
// "-Wall -Wextra -Wpedantic" flags should result in 0 warnings. --CHECK

// TODO: Complementary work: Error messages should be descriptive  
// in such a way that the user can correct their input without retrying  
// multiple times. 
// hint: when giving one wrong input i am unsure which one is wrong --CHECK


// TODO: Complementary work: Programs should not accept negative 
// values for arguments where it doesn't make sense. --CHECK



int main(int argc, char* argv[]) {

	if (argc != 5) {
		std::cerr << "this program needs four input" << std::endl;
		return -1;
	}

	int iterationTimes{ 0 }, linesToPrint{ 0 };
	double timeSlot{ 0 }, batteryVoltage{ 0 };

	try {
		iterationTimes = std::stoi(argv[1]);
		linesToPrint = std::stoi(argv[2]);
		timeSlot = std::stod(argv[3]);
		batteryVoltage = std::stod(argv[4]);
		
		if (iterationTimes <= 0 || linesToPrint <= 0 || timeSlot <= 0 || batteryVoltage <= 0) {
			throw std::invalid_argument("input should be possitive value");
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "input cannot be converted into number value" << e.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "value out of range" << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception& e) {
		std::cerr << "unknow error" << e.what() << std::endl;
		return 1;
	}

	Connection* p = new Connection(24.00, true);
	Connection* n = new Connection(0.00, true);
	Connection* R124 = new Connection();
	Connection* R23 = new Connection();

	std::vector<Component*> net1; // Polymorphism
	net1.push_back(new Battery("Bat", batteryVoltage, p, n));
	net1.push_back(new Resistor("R1", 6.00, p, R124));
	net1.push_back(new Resistor("R2", 4.00, R124, R23));
	net1.push_back(new Resistor("R3", 8.00, R23, n));
	net1.push_back(new Resistor("R4", 12.00, R124, n));
	simulate(net1, iterationTimes, linesToPrint, timeSlot);
	deallocate_components(net1);
	delete n,p,R124,R23;

	std::cout << std::endl;

	Connection* P = new Connection(24.00, true);
	Connection* N = new Connection(0.00, true);
	Connection* L = new Connection();
	Connection* R = new Connection();
	std::vector<Component*> net2; // Polymorphism
	net2.push_back(new Battery("Bat", batteryVoltage, P, N));
	net2.push_back(new Resistor("R1", 150.0, P, L));
	net2.push_back(new Resistor("R2", 50.0, P, R));
	net2.push_back(new Resistor("R3", 100.0, R, L));
	net2.push_back(new Resistor("R4", 300.0, L, N));
	net2.push_back(new Resistor("R5", 250.0, R, N));
	simulate(net2, iterationTimes, linesToPrint, timeSlot);
	deallocate_components(net2);
	delete P,N,L,R;

	std::cout << std::endl;

	Connection* P1 = new Connection(24.00, true);
	Connection* N1 = new Connection(0.00, true);
	Connection* L1 = new Connection();
	Connection* R1 = new Connection();
	std::vector<Component*> net3; // Polymorphism
	net3.push_back(new Battery("Bat", batteryVoltage, P1, N1));
	net3.push_back(new Resistor("R1", 150.0, P1, L1));
	net3.push_back(new Resistor("R2", 50.0, P1, R1));
	net3.push_back(new Capacitor("C3", 1.0, R1, L1));
	net3.push_back(new Resistor("R4", 300.0, L1, N1));
	net3.push_back(new Capacitor("C5", 0.75, R1, N1));
	simulate(net3, iterationTimes, linesToPrint, timeSlot);
	deallocate_components(net3);
	delete P1,N1,L1,R1;

	return 0;
}
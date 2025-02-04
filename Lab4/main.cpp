#include "lab04.h"

#include <iostream>

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
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "input cannot be converted into number value" << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "value out of range" << std::endl;
		return 1;
	}
	catch (const std::exception& e) {
		std::cerr << "unknow error" << std::endl;
		return 1;
	}

	Connection* p = new Connection(true);
	Connection* n = new Connection(true);
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
	delete n;
	delete p;
	delete R124;
	delete R23;


	std::cout << std::endl;


	Connection* P = new Connection(true);
	Connection* N = new Connection(true);
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

	std::cout << std::endl;


	std::vector<Component*> net3; // Polymorphism
	net3.push_back(new Battery("Bat", batteryVoltage, P, N));
	net3.push_back(new Resistor("R1", 150.0, P, L));
	net3.push_back(new Resistor("R2", 50.0, P, R));
	net3.push_back(new Capacitor("C3", 1.0, R, L));
	net3.push_back(new Resistor("R4", 300.0, L, N));
	net3.push_back(new Capacitor("C5", 0.75, R, N));

	simulate(net3, iterationTimes, linesToPrint, timeSlot);
	deallocate_components(net3);
	delete P;
	delete N;
	delete L;
	delete R;

	return 0;
}
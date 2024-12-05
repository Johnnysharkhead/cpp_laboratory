#include "lab04.h"
#include <iostream>
#include <iomanip>


//hint: Start with the following part, since some code will have to be rewritten:
// TODO: Complementary work neeed: Do not repeat similar code. 
// hint: computingVoltage contains a lot of repeat code.
//       The cause of this is probably since your connection class is pretty complicated
//		 e.g using only a double is sufficient in the connection class without "whichend()"
//       you will probably have to rethink some parts of the implementation to solve this. -- CHECK 


// TODO: Complementary work: Use '{...}' instead of '=' to initialize variables. -- CHECK

// Comment: Instead of manually calling getVoltage and getCurrent when  
// printing, implement a operator<< for Component  -- CHECK


Connection::Connection() : m_pointVoltage{ 0 }, m_isFixed{ false } {}

Connection::Connection(double voltage, bool isFixed) : m_pointVoltage{ voltage }, m_isFixed{ isFixed } {}

double Connection::getPointVoltage() const {
	return m_pointVoltage;
}

void Connection::changePointVoltage(double newVoltage) {
	if (!m_isFixed) { // Determine whether the connection is positive or negative, if yes, then the voltage remains constant
		m_pointVoltage = newVoltage;
	}
}

std::ostream& operator << (std::ostream& os, const Component& component) {
	os << component.getVoltage() << " " << component.getCurrent() << " ";
	return os;
}


Component::Component() :m_componentName{ 0 }, m_leftConnection{ 0 }, m_rightConnection{ 0 }, m_current{ 0 } {}

Component::Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
	m_componentName(componentName), m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current{ 0 } {}


Battery::Battery() : m_voltage(0) {}

Battery::Battery(std::string batteryName, double voltage, Connection* leftConnection, Connection* rightConnection) :
	Component(batteryName, leftConnection, rightConnection), m_voltage{ voltage } {
	this->m_leftConnection->changePointVoltage(m_voltage); // Assign the voltage of the left connection point of the battery directly to the voltage value of the battery in this Constructor.
}

std::string Battery::getComponentName() const {
	return m_componentName;
}

double Battery::getCurrent() const {
	return 0.0;
}

void Battery::computingCurrent() const {}

double Battery::getVoltage() const {
	return m_voltage;
}

Resistor::Resistor() : m_resistance(0) {}

Resistor::Resistor(std::string resistorName, double resistance, Connection* leftConnection, Connection* rightConnection) :
	Component(resistorName, leftConnection, rightConnection), m_resistance(resistance) {}

std::string Resistor::getComponentName() const {
	return m_componentName;
}

double Resistor::getCurrent() const {
	return m_current;
}

void Resistor::computingCurrent() {
	m_current = getVoltage() / m_resistance;
}


Capacitor::Capacitor() : m_capacitance{ 0 }, m_storedVoltage{ 0 } {}

Capacitor::Capacitor(std::string capacitorName, double capacitance, Connection* leftConnection, Connection* rightConnection) :
	Component(capacitorName, leftConnection, rightConnection), m_capacitance{ capacitance }, m_storedVoltage{ 0 } {}

std::string Capacitor::getComponentName() const {
	return m_componentName;
}

double Capacitor::getCurrent() const {
	return m_current;
}

void Capacitor::computingCurrent() {
	m_current = m_capacitance * (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage() - m_storedVoltage);
	if (m_current < 0.0) m_current = -(m_current);
}



void simulate(std::vector<Component*>& circuit, int iterationTimes, int linesToPrint, double timeSlot) {
	int iterationTimesBeforePrint{ iterationTimes / linesToPrint };
	for (auto i : circuit) {
		std::cout << std::right << std::setw(11) << i->getComponentName();
	}
	std::cout << std::endl;
	for (size_t i{0}; i < circuit.size(); i++) {
		std::cout << std::right << std::setw(11) << "Volt Curr";
	}
	std::cout << std::endl;

	int count{ 0 };
	while (count < iterationTimes && linesToPrint > 0) {
		count++;
		for (auto i : circuit) {
			i->computingVoltage(timeSlot);
			i->computingCurrent();
		}
		if (count == iterationTimesBeforePrint) {
			count = 0;
			linesToPrint--;
			for (auto i : circuit) {
				std::cout << std::right << std::setw(5) << std::fixed << std::setprecision(2) << *i;
			}
			std::cout << std::endl;
		}
	}
}

void deallocate_components(std::vector<Component*>& circuit) {
	for (auto i : circuit) {
		delete i;
	}
	circuit.clear();
}
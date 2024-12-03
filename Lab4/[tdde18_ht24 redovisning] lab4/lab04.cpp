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


double Connection::getPointVoltage() const {
	return m_pointVoltage;
}

void Connection::changePointVoltage(double newVoltage) {
	if (!m_isFixed) { // Determine whether the connection is positive or negative, if yes, then the voltage remains constant
        m_pointVoltage = newVoltage;
    }
}

std::ostream& operator << (std::ostream& os, const Component& component) {
    os << component.getVoltage()<< " " << component.getCurrent() << " ";
    return os;
}


std::string Battery::getComponentName() const {
	return m_componentName;
}

double Battery::getCurrent() const {
	return 0.0;
}

double Battery::getVoltage() const {
	return m_voltage;
}

void Battery::computingVoltage(double) {}

void Battery::computingCurrent() {}


std::string Resistor::getComponentName() const {
	return m_componentName;
}

double Resistor::getCurrent() const {
	return m_current;
}

void Resistor::computingVoltage(double timeSlot) {
	double chargeMove = (this->getVoltage() / m_resistance) * timeSlot;
	m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);
	m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);
}

void Resistor::computingCurrent() {
	m_current = getVoltage() / m_resistance;
}


std::string Capacitor::getComponentName() const {
	return m_componentName;
}

double Capacitor::getCurrent() const {
	return m_current;
}

void Capacitor::computingVoltage(double timeSlot) {
	double chargeToStore = m_capacitance * (this->getVoltage() - m_storedVoltage);
	m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
	m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);
	m_storedVoltage = m_storedVoltage + chargeToStore; // Used to calculate the current of capacitor
}

void Capacitor::computingCurrent() {
	m_current = m_capacitance * (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage() - m_storedVoltage);
	if (m_current < 0.0) m_current = -(m_current);
}


void simulate(std::vector<Component*>& circuit, int iterationTimes, int linesToPrint, double timeSlot) {
	int iterationTimesBeforePrint = iterationTimes / linesToPrint;
	for (auto i : circuit) {
		std::cout << std::right << std::setw(11) << i->getComponentName();
	}
	std::cout << std::endl;
	for (auto i : circuit) {
		std::cout << std::right << std::setw(11) << "Volt Curr";
	}
	std::cout << std::endl;

	int count {0};
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
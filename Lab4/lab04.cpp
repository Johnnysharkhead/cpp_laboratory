#include "lab04.h"

#include <iostream>
#include <iomanip>

double Connection::getPointVoltage() const {
	return m_pointVoltage;
}

void Connection::changePointVoltage(double newVoltage) {
	m_pointVoltage = newVoltage;
}

int Connection::whichEnd() const {
	if (m_pointVoltage > 0 && m_end) {
		return LEFT_END;
	}
	else if (m_pointVoltage == 0 && m_end) {
		return RIGHT_END;
	}
	else return NOT_END;
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

void Battery::computingVoltage(double timeSlot) {

}

void Battery::computingCurrent() {

}


std::string Resistor::getComponentName() const {
	return m_componentName;
}

double Resistor::getCurrent() const {
	return m_current;
}

double Resistor::getVoltage() const {
	double result = m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();
	if (result >= 0.01) {
		return result;
	}
	return 0.0;
}

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference = getVoltage();
	double chargeMove = (voltageDifference / m_resistance) * timeSlot;
	//if it is connect directly with battery
	if (m_leftConnection->whichEnd() == LEFT_END) {
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);	
	}
	else if (m_rightConnection->whichEnd() == RIGHT_END) {
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);
	}
	else {
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);
	}
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

double Capacitor::getVoltage() const {
	return m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();
}

void Capacitor::computingVoltage(double timeSlot) {
	double voltageDifference = m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();
	double chargeToStore = m_capacitance * (voltageDifference - m_storedVoltage);

	m_storedVoltage = m_storedVoltage + chargeToStore; 

	if (m_leftConnection->whichEnd() == LEFT_END) {
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);
	}
	else if (m_rightConnection->whichEnd() == RIGHT_END) {
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
	}
	else {
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);
	}
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

	int count = 0;
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

				std::cout << std::right << std::setw(5) << std::fixed << std::setprecision(2) << i->getVoltage() << " " << i->getCurrent() << " ";
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
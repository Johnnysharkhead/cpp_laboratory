#include "lab04.h"

#include <iostream>
#include <iomanip>

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference = getVoltage();																	// 电势差
	double chargeMove = (voltageDifference / m_resistance) * timeSlot;
	//if (voltageDifference / m_resistance < m_current - 0.01 || voltageDifference / m_resistance > m_current + 0.01) {
		if (m_leftConnection->whichEnd() == "left") { //左侧电压接电池正极的（左侧电压恒定）
			m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);	// 只有右侧电压变化
		}
		else if (m_rightConnection->whichEnd() == "right") { // 右侧电压接电池负极的（右侧电压恒定）
			m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);
		}
		else {
			m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);
			m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);
		}
	//}
}

void Resistor::computingCurrent() {
	m_current = getVoltage() / m_resistance;
}

void Capacitor::computingVoltage(double timeSlot) {
	double voltageDifference = m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();
	double chargeToStore = m_capacitance * (voltageDifference - m_storedVoltage);

	m_storedVoltage = m_storedVoltage + chargeToStore; // 更新迭代后已储存电荷的总和

	m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
	m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);
}

void Capacitor::computingCurrent() {
	m_current = m_capacitance * (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage() - m_storedVoltage);
}

void simulate(std::vector<Component*> circuit, int iterationTimes, int linesToPrint, double timeSlot) {
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
			std::cout<<std::endl;
		}
	}
}

void deallocate_components(std::vector<Component*> circuit) {
}

int main() {
	Connection* p = new Connection(true);
	Connection* n = new Connection(true);
	Connection* R124 = new Connection();
	Connection* R23 = new Connection();
	std::vector<Component*> net;
	net.push_back(new Battery("Bat", 24.0, n, p));
	net.push_back(new Resistor("R1", 6.0, p, R124));
	net.push_back(new Resistor("R2", 4.0, R124, R23));
	net.push_back(new Resistor("R3", 8.0, R23, n));
	net.push_back(new Resistor("R4", 12.0, R124, n));
	simulate(net, 200000, 10, 0.1);
	deallocate_components(net);
	return 0;
}
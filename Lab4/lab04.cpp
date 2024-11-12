#include "lab04.h"

#include <iostream>
#include <iomanip>

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference	= m_rightConnection->getPointVoltage() - m_leftConnection->getPointVoltage();	// ���Ʋ�
	double chargeMove			= voltageDifference / timeSlot;													// ����ƶ�������leftConnection��rightConnection�ĵ�ѹ���£�
	m_leftConnection	->	changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);				// ����ƶ��󣬸���������ѹ
	m_rightConnection	->	changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);				// ����ƶ��󣬸��¸�����ѹ
}

void Resistor::computingCurrent() {
	m_current = (m_rightConnection->getPointVoltage() - m_leftConnection->getPointVoltage()) / m_resistance;	// ʹ�ã����º��������ѹ-���º�ĸ�����ѹ��/����ֵ
																												// ��ȡ��ǰ�ĵ���ֵ
}

void Capacitor::computingVoltage(double timeSlot) {

}

void Capacitor::computingCurrent() {

}

void simulate(std::vector<Component*> circuit, int iterationTimes, int linesToPrint, double timeSlot) {
	int iterationTimesBeforePrint = iterationTimes / linesToPrint;
	for (auto i : circuit) {
		std::cout << std::right << std::setw(10) << i->getComponentName();
	}
	std::cout << std::endl;
	for (auto i : circuit) {
		std::cout << std::right << std::setw(10) << "Volt Curr";
	}
	std::cout << std::endl;

	int count = 0;
	while (count < iterationTimes) {
		count++;
		for (auto i : circuit) {
			i->computingVoltage(timeSlot);
			i->computingCurrent();
		}
		if (count == iterationTimesBeforePrint) {
			count = 0;
			for (auto i : circuit) {
				std::cout << std::right << std::setw(5)<< i->getVoltage() << " " << i->getCurrent() << " ";
			}
			std::cout<<std::endl;
		}
	}
}

void deallocate_components(std::vector<Component*> circuit) {
}

int main() {
	Connection* p = new Connection();
	Connection* n = new Connection();
	std::vector<Component*> net;
	net.push_back(new Battery("Bat", 24.0, p, n));
	net.push_back(new Resistor("R1", 6.0, p, n));
	net.push_back(new Resistor("R2", 8.0, p, n));
	simulate(net, 10000, 10, 0.1);
	deallocate_components(net);
	return 0;
}
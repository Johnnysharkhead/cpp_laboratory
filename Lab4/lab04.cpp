#include "lab04.h"

#include <iostream>
#include <iomanip>

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference	= m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();	// ���Ʋ�
	double chargeMove			= voltageDifference / timeSlot;													// ����ƶ�������leftConnection��rightConnection�ĵ�ѹ���£�
	m_leftConnection	->	changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);				// ����ƶ��󣬸���������ѹ
	m_rightConnection	->	changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);				// ����ƶ��󣬸��¸�����ѹ
}

void Resistor::computingCurrent() {
	m_current = (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage()) / m_resistance;	// ʹ�ã����º��������ѹ-���º�ĸ�����ѹ��/����ֵ
																												// ��ȡ��ǰ�ĵ���ֵ
}

void Capacitor::computingVoltage(double timeSlot) {

}

void Capacitor::computingCurrent() {

}

void simulate(std::vector<Component*> circuit, int iterationTimes, int linesToPrint, double timeSlot) {
	for (auto i : circuit) {
		std::cout << std::right << std::setw(30) << i->getComponentName() << std::endl;
	}
	for (auto i : circuit) {
		std::cout << std::right << std::setw(30) << "Volt Curr" << std::endl;
	}
}

void deallocate_components(std::vector<Component*> circuit) {
}

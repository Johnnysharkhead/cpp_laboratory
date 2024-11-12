#include "lab04.h"

#include <iostream>
#include <iomanip>

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference	= m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();	// 电势差
	double chargeMove			= voltageDifference / timeSlot;													// 电荷移动（用于leftConnection和rightConnection的电压更新）
	m_leftConnection	->	changePointVoltage(m_leftConnection->getPointVoltage() - chargeMove);				// 电荷移动后，更新正极电压
	m_rightConnection	->	changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);				// 电荷移动后，更新负极电压
}

void Resistor::computingCurrent() {
	m_current = (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage()) / m_resistance;	// 使用（更新后的正极电压-更新后的负极电压）/电阻值
																												// 获取当前的电流值
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

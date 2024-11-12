#include "lab04.h"

#include <iostream>
#include <iomanip>

void Resistor::computingVoltage(double timeSlot) {
	double voltageDifference = getVoltage();																	// ���Ʋ�
	double chargeMove = (voltageDifference / m_resistance) * timeSlot;
	//if (voltageDifference / m_resistance < m_current - 0.01 || voltageDifference / m_resistance > m_current + 0.01) {
		if (m_leftConnection->whichEnd() == "left") { //����ѹ�ӵ�������ģ�����ѹ�㶨��
			m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeMove);	// ֻ���Ҳ��ѹ�仯
		}
		else if (m_rightConnection->whichEnd() == "right") { // �Ҳ��ѹ�ӵ�ظ����ģ��Ҳ��ѹ�㶨��
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

void Capacitor::computingVoltage(double timeSlot){
	double voltageDifference = m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage();
	double chargeToStore = m_capacitance * (voltageDifference - m_storedVoltage);

	m_storedVoltage = m_storedVoltage + chargeToStore; // 计算电荷累计值

	if (m_leftConnection->whichEnd() == "left") { //����ѹ�ӵ�������ģ�����ѹ�㶨��
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);	// ֻ���Ҳ��ѹ�仯
	}
	else if (m_rightConnection->whichEnd() == "right") { // �Ҳ��ѹ�ӵ�ظ����ģ��Ҳ��ѹ�㶨��
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
	}
	else {
		m_leftConnection->changePointVoltage(m_leftConnection->getPointVoltage() - chargeToStore);
		m_rightConnection->changePointVoltage(m_rightConnection->getPointVoltage() + chargeToStore);
	}
}

void Capacitor::computingCurrent() {
	m_current = m_capacitance * (m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage() - m_storedVoltage);
	if (m_current<0.0) m_current= -(m_current);
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
	std::vector<Component*> net1;
	net1.push_back(new Battery("Bat", 24.00, n, p));
	net1.push_back(new Resistor("R1", 6.00, p, R124));
	net1.push_back(new Resistor("R2", 4.00, R124, R23));
	net1.push_back(new Resistor("R3", 8.00, R23, n));
	net1.push_back(new Resistor("R4", 12.00, R124, n));
	simulate(net1, 100000, 10, 0.1);
	deallocate_components(net1);

	
	std::cout << "\n" << std::endl;


	Connection* P = new Connection(true);
	Connection* N = new Connection(true);
	Connection* L = new Connection();
	Connection* R = new Connection();
	std::vector<Component*> net2;
	net2.push_back(new Battery("Bat", 24.0, N, P));
	net2.push_back(new Resistor("R1", 150.0, P, L));
	net2.push_back(new Resistor("R2", 50.0, P, R));
	net2.push_back(new Resistor("R3", 100.0, R, L));
	net2.push_back(new Resistor("R4", 300.0, L, N));
	net2.push_back(new Resistor("R5", 250.0, R, N));

	simulate(net2, 200000, 10, 0.01);
	deallocate_components(net2);
	
	
	std::cout << "\n" << std::endl;


	std::vector<Component*> net3;
	net3.push_back(new Battery("Bat", 24.0, N, P));
	net3.push_back(new Resistor("R1", 150.0, P, L));
	net3.push_back(new Resistor("R2", 50.0, P, R));
	net3.push_back(new Capacitor("C3", 1.0, R, L));
	net3.push_back(new Resistor("R4", 300.0, L, N));
	net3.push_back(new Capacitor("C5", 0.75, R, N));

	simulate(net3, 200000, 10, 0.01);
	deallocate_components(net3);

	return 0;
}
#ifndef COMPONENT_H
#define COMPONENT_H
#endif

#include <string>
#include <vector>

class Connection {
public:
	double getPointVoltage() const {
		return m_pointVoltage;
	}
	void changePointVoltage(double newVoltage) {
		m_pointVoltage = newVoltage;
	}
private:
	double			m_pointVoltage;
};

class Component {
public:
	Component();//�Է���һ������һ��Ĭ�ϵĹ��캯��
	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
		m_componentName(componentName), m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current(0) {
		
	}
	virtual void computingVoltage() = 0;//�����ѹֵ���ں������޸���Ӧ��ĵ�ѹ
	virtual void computingCurrent() = 0;//���㵱ǰԪ���ĵ���
	virtual std::string getComponentName() const = 0;//����Ԫ����
	virtual double getCurrent() const = 0;//���ص���ֵ
protected:
	std::string		m_componentName;
	Connection*		m_leftConnection;
	Connection*		m_rightConnection;
	double			m_current;
};

class Battery: public Component {
public:
	Battery() {

	}
	Battery(std::string batteryName, double voltage, Connection* leftConnection, Connection* rightConnection) :
		Component(batteryName, leftConnection, rightConnection), m_voltage(voltage) {
		this->m_rightConnection->changePointVoltage(m_voltage);
	}
	std::string getComponentName() const override {
		return m_componentName;
	}
	double getCurrent() const override;//��overrideʵ�����ᱨ������ʵ��
	void computingVoltage() override;//����ʵ��
	void computingCurrent() override;//����ʵ��
private:
	double			m_voltage;
};

class Resistor : public Component {
public:
	Resistor() {

	}
	Resistor(std::string resistorName, double resistance, Connection* leftConnection, Connection* rightConnection) :
		Component(resistorName, leftConnection, rightConnection), m_resistance(resistance) {

	}
	std::string getComponentName() const override {
		return m_componentName;
	}
	double getCurrent() const override {
		return m_current;
	}
	void computingVoltage() override;
	void computingCurrent() override;
private:
	double			m_resistance;
};

class Capacitor : public Component {
public:
	Capacitor() {

	}
	Capacitor(std::string capacitorName, double capacitance, Connection* leftConnection, Connection* rightConnection) :
		Component(capacitorName, leftConnection, rightConnection), m_capacitance(capacitance), m_storedVoltage(0) {

	}
	std::string getComponentName() const override {
		return m_componentName;
	}
	double getCurrent() const override {
		return m_current;
	}
	void computingVoltage(double timeUnit);//���أ��������޸�m_storedVoltage
	void computingCurrent() override;
private:
	double			m_capacitance;
	double			m_storedVoltage;
};

void simulate(std::vector<Component*> circuit, int iterationTimes, int linesToPrint, int timeSlot);//ѭ�������ͬʱ��ӡ����
void deallocate_components(std::vector<Component*> circuit);//������ѭ��delete vector��new��Ԫ��
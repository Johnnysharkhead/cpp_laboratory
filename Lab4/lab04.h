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
	Component();//以防万一重载了一个默认的构造函数
	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
		m_componentName(componentName), m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current(0) {
		
	}
	virtual void computingVoltage() = 0;//计算电压值，在函数内修改相应点的电压
	virtual void computingCurrent() = 0;//计算当前元件的电流
	virtual std::string getComponentName() const = 0;//返回元件名
	virtual double getCurrent() const = 0;//返回电流值
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
	double getCurrent() const override;//不override实例化会报错，不必实现
	void computingVoltage() override;//不必实现
	void computingCurrent() override;//不必实现
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
	void computingVoltage(double timeUnit);//重载，在里面修改m_storedVoltage
	void computingCurrent() override;
private:
	double			m_capacitance;
	double			m_storedVoltage;
};

void simulate(std::vector<Component*> circuit, int iterationTimes, int linesToPrint, int timeSlot);//循环计算的同时打印数据
void deallocate_components(std::vector<Component*> circuit);//在这里循环delete vector里new的元件
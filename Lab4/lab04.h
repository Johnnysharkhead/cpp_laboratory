#ifndef COMPONENT_H
#define COMPONENT_H
#endif

#include <string>
#include <vector>

#define	LEFT_END	0
#define	RIGHT_END	1
#define NOT_END		-1

class Connection {
public:
	Connection(): m_pointVoltage(0), m_end(false) {}
	Connection(bool ifEnd): m_pointVoltage(0), m_end(ifEnd) {}

	double getPointVoltage() const;
	void changePointVoltage(double newVoltage);

	int whichEnd() const;

private:
	double m_pointVoltage;
	bool const m_end;
};

class Component {
public:
	Component() {}

	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
		m_componentName(componentName),	m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current(0) {}
	
	virtual ~Component() = default; // virtual base class destructor 

	virtual std::string	getComponentName() const = 0;
	
	virtual double getCurrent()	const = 0;
	virtual double getVoltage()	const = 0;

	virtual void computingVoltage(double timeSlot) = 0;
	virtual void computingCurrent() = 0;

protected:
	std::string m_componentName;
	Connection*	m_leftConnection;
	Connection*	m_rightConnection;
	double m_current;
};

class Battery : public Component {
public:
	Battery(): m_voltage(0) {}

	Battery(std::string batteryName, double voltage, Connection* leftConnection, Connection* rightConnection) :
		Component(batteryName, leftConnection, rightConnection), m_voltage(voltage){
		this->m_rightConnection->changePointVoltage(m_voltage);
		}

	// ~Battery() {
	// 	delete m_leftConnection;
	// 	delete m_rightConnection;
	// }

	std::string getComponentName() const override;
	double getCurrent() const override;
	double getVoltage()	const override;

	void computingVoltage(double timeSlot) override;
	void computingCurrent() override;

private:
	double const m_voltage;
};

class Resistor : public Component {
public:
	Resistor() : m_resistance(0) {}
	Resistor(std::string resistorName, double resistance, Connection* leftConnection, Connection* rightConnection) :
		Component(resistorName,	leftConnection,	rightConnection), m_resistance(resistance) {}
	
	// ~Resistor() {
	// 	delete m_leftConnection;
	// 	delete m_rightConnection;
	// }
	
	std::string	getComponentName() const override;
	double getCurrent() const override;
	double getVoltage()	const override;

	void computingVoltage(double timeSlot) override;
	void computingCurrent()	override;

private:
	double const m_resistance;
};

class Capacitor : public Component {
public:
	Capacitor() : m_capacitance(0) {}
	Capacitor(std::string capacitorName, double capacitance, Connection* leftConnection, Connection* rightConnection) :
		Component(capacitorName, leftConnection, rightConnection), m_capacitance(capacitance), m_storedVoltage(0) {}

	// ~Capacitor() {
	// 	delete m_leftConnection;
	// 	delete m_rightConnection;
	// }

	std::string getComponentName() const override;
	double getCurrent() const override;
	double getVoltage()	const override;

	void computingVoltage(double timeSlot) override;
	void computingCurrent() override;

private:
	double const m_capacitance;
	double m_storedVoltage;
};

void simulate(std::vector<Component*>& circuit, int iterationTimes, int linesToPrint, double timeSlot);
void deallocate_components(std::vector<Component*>& circuit);
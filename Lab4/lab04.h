#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

#define	LEFT_END	0  // Indicates that the left side of the component is directly connected to the positive terminal of the battery, i.e. the voltage on the left side of the component does not change with the movement of the charge.
#define	RIGHT_END	1  // Indicates that the right side of the component is directly connected to the negative terminal of the battery, i.e. the voltage on the right side of the component does not change with the movement of the charge.
#define NOT_END		-1 // Indicates that the left and right sides of the component are not directly connected to the positive and negative terminals of the battery, i.e., the voltage on the left and right sides of the component will change with the movement of the charge.

// left and right connection points for each component
class Connection {
public:
	Connection(): m_pointVoltage(0), m_end(false) {} // Constructor
	Connection(bool ifEnd): m_pointVoltage(0), m_end(ifEnd) {} // Constructor

	double getPointVoltage() const; // Get the current voltage value of this connection point
	void changePointVoltage(double newVoltage); // Calculate and update the value of the voltage at this connection point after the change with charge movement
	
	int whichEnd() const; // Determine if the connection point is directly connected to the positive or negative terminal of the battery

private:
	double m_pointVoltage; 
	bool const m_end;
};


// The abstract base class for all components in this lab
class Component {
public:
	Component() {}
	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
		m_componentName(componentName),	m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current(0) {}
	
	virtual ~Component() = default; 

	virtual std::string	getComponentName() const = 0;
	
	virtual double getCurrent()	const = 0; // Get the value of current going through the component
	virtual double getVoltage()	const = 0; // Get the voltage at the left connection point of the component minus the voltage at the right connection point

	virtual void computingVoltage(double timeSlot) = 0; // Involves the movement and storage of charges, and updating the voltage values at the left and right connection points of the component respectively
	virtual void computingCurrent() = 0;

protected:
	std::string m_componentName;
	Connection*	m_leftConnection; // A pointer that point to an object(the left connection) of the Connection class
	Connection*	m_rightConnection; // A pointer that point to an object of the Connection class
	double m_current;
};

class Battery : public Component {
public:
	Battery(): m_voltage(0) {}

	Battery(std::string batteryName, double voltage, Connection* leftConnection, Connection* rightConnection) :
		Component(batteryName, leftConnection, rightConnection), m_voltage(voltage){
		this->m_leftConnection->changePointVoltage(m_voltage); // Assign the voltage of the left connection point of the battery directly to the voltage value of the battery in this Constructor.
		}

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

	std::string getComponentName() const override;
	double getCurrent() const override;
	double getVoltage()	const override;

	void computingVoltage(double timeSlot) override;
	void computingCurrent() override;

private:
	double const m_capacitance;
	double m_storedVoltage; 
};

void simulate(std::vector<Component*>& circuit, int iterationTimes, int linesToPrint, double timeSlot); // Analogue circuit simulation where the circuit reaches steady state after a certain period of time
void deallocate_components(std::vector<Component*>& circuit); // Release the object pointed by the pointer in the heap space to avoid memory leaks.

#endif
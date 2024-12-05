#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#pragma pack(push,1)

// Complementary work: Define is c code. This is a c++ course. You enum is more appropriate.
// 		But look into the comments in the other file first about replacing the connection component.-- CHECK

// TODO: Complementary work: Parameters to functions that you don’t use  
// should be declared without a name to signal that they are unused. -- CHECK

class Connection {
public:
	Connection(); // Constructor(Default)
	Connection(double voltage, bool isFixed = false); // Constructor(used to initialise positive and negative terminals)
	double getPointVoltage() const; // Get the current voltage value of this connection point
	void changePointVoltage(double newVoltage); // Calculate and update the value of the voltage at this connection point after the change with charge movement

private:
	double m_pointVoltage;
	bool m_isFixed;
};

// The abstract base class for all components in this lab
class Component {
public:
	Component();
	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection);
	virtual ~Component() = default;
	
	virtual std::string	getComponentName() const = 0;
	
	virtual double getCurrent()	const = 0; // Get the value of current going through the component	
	virtual double getVoltage()	const; // Get the voltage at the left connection point of the component minus the voltage at the right connection point

	virtual void computingVoltage(double timeSlot); // The computingVoltage method has a similar structure in the Resistor and Capacitor class. So we abstract the common logic into the base class
	virtual void computingCurrent() = 0;

	friend std::ostream& operator << (std::ostream&, const Component& component);

protected:
	std::string m_componentName;
	Connection* m_leftConnection; // A pointer that point to an object(the left connection) of the Connection class
	Connection* m_rightConnection; // A pointer that point to an object of the Connection class
	double m_current;

	virtual double calculateChargeMove(double timeSlot) = 0; // The Resistor and Capacitor object must have their own method to calculate the chargeMove
    void updateConnections(double chargeMove); // Updates the voltage values at the left and right connection points
};
class Battery : public Component {
public:
	Battery();
	// Assign the voltage of the left connection point of the battery directly to the voltage value of the battery in this Constructor.
	Battery(std::string batteryName, double voltage, Connection* leftConnection, Connection* rightConnection);
	Battery& operator=(const Battery&) = delete;
	Battery(const Battery&) = delete;

	std::string getComponentName() const override;
	double getCurrent() const override;
	double getVoltage()	const override;
	void computingCurrent() override;

protected:
    double calculateChargeMove(double) override {
        return 0;
    }

private:
	double const m_voltage;
};

class Resistor : public Component {
public:
	Resistor();
	Resistor(std::string resistorName, double resistance, Connection* leftConnection, Connection* rightConnection);
	Resistor& operator=(const Resistor&) = delete;
	Resistor(const Resistor&) = delete;

	std::string	getComponentName() const override;
	double getCurrent() const override;
	void computingCurrent()	override;

protected:
    double calculateChargeMove(double timeSlot) override;

private:
	double const m_resistance;
};

class Capacitor : public Component {
public:
	Capacitor();
	Capacitor(std::string capacitorName, double capacitance, Connection* leftConnection, Connection* rightConnection);
	Capacitor& operator=(const Capacitor&) = delete;
	Capacitor(const Capacitor&) = delete;

	std::string getComponentName() const override;
	double getCurrent() const override;
	void computingCurrent() override;

protected:
    double calculateChargeMove(double) override;

private:
	double const m_capacitance;
	double m_storedVoltage;
};

void simulate(std::vector<Component*>& circuit, int iterationTimes, int linesToPrint, double timeSlot); // Analogue circuit simulation where the circuit reaches steady state after a certain period of time
void deallocate_components(std::vector<Component*>& circuit); // Release the object pointed by the pointer in the heap space to avoid memory leaks.

#pragma pack(pop) 
#endif

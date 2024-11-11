#ifndef COMPONENT_H
#define COMPONENT_H
#endif

class Component {
public:
	virtual double computingVoltage() = 0;
	virtual double computingCurrent() = 0;
protected:
	double m_terminal_1;
	double m_terminal_2;
};

class Battery: public Component {
public:
	double computingVoltage() override;
	double computingCurrent() override;
private:
	double m_voltage;
};

class Resistor : public Component {
public:
	double computingVoltage() override;
	double computingCurrent() override;
private:
	double m_resistance;
};

class Capacitor : public Component {
public:
	double computingVoltage() override;
	double computingCurrent() override;
private:
	double m_capacitance;
	double m_storedVoltage;
};
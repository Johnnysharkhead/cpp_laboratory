#ifndef COMPONENT_H
#define COMPONENT_H
#endif

class Component {
public:
protected:
	int m_terminal_1;
	int m_terminal_2;
};

class Battery: public Component {
public:
private:
	int m_voltage;
};

class Resistor : public Component {
public:
private:
	double m_resistance;
};

class Capacitor : public Component {
public:
private:
	double m_capacitance;
};
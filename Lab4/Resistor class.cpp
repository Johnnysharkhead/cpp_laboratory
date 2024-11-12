#include <string>
#include <vector>
#include "lab04.h"

class Connection {
public:
	double getPointVoltage() const {
		return m_pointVoltage;
	}
	void changePointVoltage(double newVoltage) {
		m_pointVoltage = newVoltage;
	}
private:
	double	m_pointVoltage;
};


class Component {
public:
	Component();
	Component(std::string componentName, Connection* leftConnection, Connection* rightConnection) :
		m_componentName(componentName), m_leftConnection(leftConnection), m_rightConnection(rightConnection), m_current(0) {
		
	}
	virtual void computingVoltage(int timeSlot) = 0;
	virtual void computingCurrent() = 0;
protected:
	std::string		m_componentName;
	Connection*		m_leftConnection;
	Connection*		m_rightConnection;
	double			m_current;
};




class Resistor : public Component {
public:
	Resistor() {};
	
    Resistor(std::string m_componentName, double resistance, Connection* leftConnection, Connection* rightConnection) :
        Component(m_componentName, leftConnection, rightConnection), m_resistance(resistance) {}; // 电阻的构造函数
	
    void computingVoltage(int timeSlot) override{ //加入了参数timeSlot，同时在base class里面更新了computingVoltage函数所需参数声明
        double voltageDifference = m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage(); // 电势差
        double chargeMove = voltageDifference / timeSlot; // 电荷移动（用于leftConnection和rightConnection的电压更新）
        m_leftConnection->changePointVoltage( m_leftConnection->getPointVoltage() - chargeMove ); // 电荷移动后，更新正极电压
        m_rightConnection->changePointVoltage( m_rightConnection->getPointVoltage() + chargeMove); // 电荷移动后，更新负极电压
    }

	void computingCurrent() override{
        m_current = ( m_leftConnection->getPointVoltage() - m_rightConnection->getPointVoltage() ) / m_resistance; // 使用（更新后的正极电压-更新后的负极电压）/电阻值 获取当前的电流值
    }
private:
	double m_resistance;

};
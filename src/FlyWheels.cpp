/*
 * FlyWheels.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include <FlyWheels.h>

FlyWheels::FlyWheels(
		SmartTalon& rightFlyWheelMotor,
		SmartTalon& leftFlyWheelMotor,
		Joystick& gamepad):
		m_rightFlyWheelMotor(rightFlyWheelMotor),
		m_leftFlyWheelMotor(leftFlyWheelMotor),
		m_gamepad(gamepad) {

	m_state = STATE::OFF;
}

FlyWheels::~FlyWheels()
{

}

void FlyWheels::run()
{
	switch (m_state)
	{
	case OFF:
		m_rightFlyWheelMotor.goAt(0.0); //stop right FlyWheel
		m_leftFlyWheelMotor.goAt(0.0); //stop left FlyWheel

		if (m_gamepad.GetRawButton(DriveStationConstants::triggerRT))
		{
			setState(ON);
		}
		break;
	case ON:
		m_rightFlyWheelMotor.goAt(motorSpeed); // set right FlyWheel speed
		m_leftFlyWheelMotor.goAt(motorSpeed); //set left Flywheel speed

		if (m_gamepad.GetRawButton(DriveStationConstants::triggerLT))
		{
			setState(OFF);
		}
		break;
	}
}

FlyWheels::STATE FlyWheels::getState()
{
	return m_state;
}
void FlyWheels::setState(STATE state)
{
	m_state = state;

}

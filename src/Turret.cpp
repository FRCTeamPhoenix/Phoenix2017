/*
 * Turret.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "Turret.h"

Turret::Turret(
		SmartTalon& turretRotatorMotor,
		Joystick& gamepad):
		m_turretRotatorMotor(turretRotatorMotor),
		m_gamepad(gamepad)

{
	m_state = IDLE;

}

Turret::~Turret()
{


}

void Turret::run()
{
	switch (m_state)
	{
	case IDLE:
		m_turretRotatorMotor.goAt(0.0);

		if(gamepadJoystickWithDeadZone() != 0)
		{
			setState(MOVING);
		}

		break;

	case MOVING:
		m_turretRotatorMotor.goAt(gamepadJoystickWithDeadZone());

		if(gamepadJoystickWithDeadZone() == 0)
		{
			setState(IDLE);
		}

		break;

	}
}

float Turret::gamepadJoystickWithDeadZone()
{
	float power = -m_gamepadJoystick;

	if (fabs(power) < 0.05f){
		power = 0;
	}
	return power * RobotConstants::turretDamp;
}

Turret::STATE Turret::getState()
{
	return m_state;
}
void Turret::setState(STATE state)
{
	m_state = state;

}

/*
 * Turret.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_TURRET_H_
#define SRC_TURRET_H_
#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"

class Turret
{

public:

	enum STATE
	{
	IDLE, //Turret Rotating
	MOVING //Turret IDLE

	};
	void run();
	float gamepadJoystickWithDeadZone();

	STATE getState(); // Get State
	void setState(STATE state); //Set State

	Turret(
			SmartTalon& m_turretRotatorMotor,
	        Joystick* gamepad
	                   );
	virtual ~Turret();

private:
	SmartTalon& m_turretRotatorMotor; //Turret Motor
	Joystick* m_gamepad;

	float m_gamepadJoystick = 0.0;
	float motorSpeed = 0.5;
	STATE m_state;
};

#endif /* SRC_TURRET_H_ */

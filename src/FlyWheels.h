/*
 * FlyWheels.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_FLYWHEELS_H_
#define SRC_FLYWHEELS_H_
#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"
class FlyWheels
{

public:

	enum STATE // States
	{
		OFF,
		ON
	};

	void run();
	STATE getState(); //Get State
	void setState(STATE state); //Set State


	FlyWheels(
			SmartTalon& rightFlyWheelMotor,
			SmartTalon& leftFlyWheelMotor,
			Joystick& gamepad
	);
	virtual ~FlyWheels();


private:
	STATE m_state;
	float motorSpeed = 0.5;
	SmartTalon& m_rightFlyWheelMotor; //Right FlyWheel Motor
	SmartTalon& m_leftFlyWheelMotor; // Left FlyWheel Motor
	Joystick& m_gamepad; //Gamepad

};

#endif /* SRC_FLYWHEELS_H_ */

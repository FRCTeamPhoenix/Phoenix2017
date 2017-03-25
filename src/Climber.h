/*
 * Climber.h
 *
 *  Created on: Jan 10, 2017
 *      Author: Joshua Calzadillas
 */
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"

/* constants:
 *
 *
 */

class Climber
{
public:
	Climber(SmartTalon & motor, SmartTalon& motor2, Joystick& customBox);
	virtual ~Climber();
	enum STATE
	{
		OFF,
		ON
	};
	void updateButton(); // Checks to see if the button is pressed on the Smart Train Dashboard console
	void move(double speed);
	void stop();
	void run();
	STATE getState();
	void setState(STATE state);

private:
	SmartTalon & m_motor;
    SmartTalon & m_motor2;
	STATE m_state;
    Joystick& m_customBox;

};



#endif /* SRC_CLIMBER_H_ */

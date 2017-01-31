/*
 * Gatherer.h
 *
 *  Created on: Jan 29, 2017
 *      Author: joshc
 */
#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"
#ifndef SRC_GATHERER_H_
#define SRC_GATHERER_H_

class Gatherer {
public:
	Gatherer(Talon & motor,
			Joystick & gamepad);
	virtual ~Gatherer();
	enum STATE {
		OFF,
		ON,
		AUTO
	};
	void run();
	void stop();
	void move(double speed); // Move the gatherer
	void Update(); // This is for testing only // Button check for the Smart Dashboard

private:
	Talon & m_motor;
	Joystick & m_gamepad;
	STATE m_state;
};

#endif /* SRC_GATHERER_H_ */

/*
 * Gather.h
 *
 *  Created on: Jan 24, 2017
 *      Author: joshc
 */
#include "WPILib.h"
#include "constants.h"


#ifndef SRC_GATHERER_H_
#define SRC_GATHERER_H_

class Gatherer {
public:
	enum State {
		OFF,
		ON
	}; // State of the gatherer
	Gatherer(Talon & motor,
			Joystick & joystick);
	virtual ~Gatherer();
	void run(); // This is the main function for the gatherer
	void stop(); // Stops the gatherer
	void start(); // Starts the gatherer

private:
	Talon & m_motor;
	Joystick & m_joystick;
	State m_state;
};

#endif /* SRC_GATHERER_H_ */

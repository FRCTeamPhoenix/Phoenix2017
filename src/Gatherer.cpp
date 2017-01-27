/*
 * Gather.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: joshc
 */

#include "Gatherer.h"

Gatherer::Gatherer(Talon & motor,
		Joystick & joystick):
		m_motor(motor),
		m_joystick(joystick){
	// TODO Auto-generated constructor stub
	m_state = OFF;
}

void Gatherer::run() {
	switch(m_state) {
	case OFF:
		// Tests if there is a button press
		if (!m_joystick.GetRawButton(DriveStationConstants::buttonB)) {
			stop();
			break;
		}
		m_state = ON;
		break;

	case ON:
		// If there is a button press then it will move the motors.
		if(m_joystick.GetRawButton(DriveStationConstants::buttonB)) {
			start();
			break;
		}
		m_state = OFF;
		break;
	}
}

void Gatherer::stop() {
	m_motor.Set(0.0f);
}

void Gatherer::start() {
	m_motor.Set(1.0f);
}

void Gatherer::move(double speed) {
	m_motor.Set(speed);
}

Gatherer::~Gatherer() {
	// TODO Auto-generated destructor stub
}


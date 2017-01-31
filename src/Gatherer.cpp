/*
 * Gatherer.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: joshc
 */

#include <Gatherer.h>

Gatherer::Gatherer(
		Talon & motor,
		Joystick & gamepad):
		m_motor(motor),
		m_gamepad(gamepad)
{
	// TODO Auto-generated constructor stub
	m_state = OFF;
}

void Gatherer::move(double speed) {
	m_motor.Set(speed);
}

void Gatherer::stop() {
	m_motor.Set(0.0);
}

void Gatherer::Update() {
    std::stringstream btn;
    btn << "Button B: " << m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonB + 1);
    SmartDashboard::PutString("DB/String 1", btn.str());
}

void Gatherer::run() {
	Update();
	switch(m_state)
	{
	case OFF:
		stop();
		if (!m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonB + 1)) {
			break;
		}
		m_state = ON;
		break;

	case ON:
		move(0.3);
		if (m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonB + 1)) {
			break;
		}
		m_state = OFF;
		break;

	case AUTO:
		break;
	}
}

Gatherer::~Gatherer() {
	// TODO Auto-generated destructor stub
}


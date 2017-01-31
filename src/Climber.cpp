/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: Joshua Calzadillas
 */
#include "Climber.h"

Climber::Climber(
        SmartTalon & motor,
        Joystick & gamepad):
		m_motor(motor),
		m_gamepad(gamepad)
{
	m_state = OFF;
}

Climber::~Climber()
{
}

void Climber::updateButton() {
    std::stringstream btn;
    btn << "Button A: " << m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonA + 1);
    SmartDashboard::PutString("DB/String 0", btn.str());
}

void Climber::move(double speed) {
	m_motor.Set(speed); // GOAT will be later
}

void Climber::stop() {
	m_motor.Set(0.0);
}

void Climber::run()
{
	updateButton();
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
        case OFF:
        	stop();
            if (!m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonA + 1))
            {
                break;
            }
            m_state = ON;
            break;

        case ON:
        	move(0.3);
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonA + 1))
            {
            	break;
            }
            m_state = OFF;
            break;

            // TODO we need to add the limits and find them witht the encoders.
    }

}

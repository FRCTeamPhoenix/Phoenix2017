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
}

Climber::~Climber()
{
}

void Climber::move(double speed) {
	m_motor.goAt(speed);
}

void Climber::stop() {
	m_motor.goAt(0.0);
}

void Climber::run()
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
    	stop();
        case OFF:
            if (!m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
                break;
            }
            m_state = ON;
            break;

        case ON:
        	move(2000);
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
            	break;
            }
            m_state = OFF;
            break;

            // TODO we need to add the limits and find them witht the encoders.
    }

}

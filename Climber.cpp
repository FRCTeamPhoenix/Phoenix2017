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

// This functions allows you to move at a distance in ticks
void Climber::move(double distance) {
	m_motor.goAt(distance);
}

// Stops the climber
void Climber::stop() {
	m_motor.goAt(0.0);
}

// The main function for the climber
void Climber::run()
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
        case OFF:
            if (!m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
            	stop();
                break;
            }
            m_state = ON;
            break;

        case ON:
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
            	move(2000);
            	break;
            }
            m_state = OFF;
            break;

            // TODO we need to add the limits and find them witht the encoders.
    }

}

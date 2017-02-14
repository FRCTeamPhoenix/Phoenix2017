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

void Climber::move(double speed) { //Function to make the motor move at a certain speed.
	m_motor.goAt(speed);
}

void Climber::stop() {
	m_motor.goAt(0.0);
}

void Climber::run() //Changes the states of the run function.
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
    	stop();
        case OFF: //If the gamepad is not pressed, the state is set to OFF.
            if (!m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
                break;
            }
            m_state = ON;
            break;

        case ON: //If the gamepad is pressed, the state is set to ON.
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

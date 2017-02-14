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

void Climber::updateButton() { //Updates button
    std::stringstream btn;
    btn << "Button : " << m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonA);
    SmartDashboard::PutString("DB/String 0", btn.str());
    btn.clear();
}

void Climber::move(double speed) {
	m_motor.Set(speed); // GoAt will be later
}

void Climber::stop() {
	m_motor.Set(0.0);
}

void Climber::run()
{
	//updateButton(); This was for testing Button Input
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    { //Case OFF checks to see if button isn't pressed. if it's pressed, state changes.
        case OFF:
        	stop();
            if (!m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonLB))
            {
                break;
            }
            m_state = ON;
            break;

            //Case ON sets motor speed to 0.3 when button is pressed. If button isn't pressed, state changes.
        case ON:
        	move(0.3);
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonNames::buttonLB))
            {
            	break;
            }
            m_state = OFF;
            break;

            // TODO we need to add the limits and find them with the encoders.
    }

}

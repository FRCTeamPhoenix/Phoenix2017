/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "Climber.h"

Climber::Climber(
        Talon * motor,
        Joystick * gamepad)
{
    m_motor = motor;
    m_gamepad = gamepad;
}

Climber::~Climber()
{
}

void Climber::start()
{
    // TODO Not sure if talons or smarttalons will be used, start might need to be changed
    m_motor->Set(1.0f);
}

void Climber::stop()
{
    // TODO Not sure if talons or smarttalons will be used, stop might need to be changed
    m_motor->Set(0.0f);
}

void Climber::run()
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
        case OFF:
            // Button A is the climbing button
            if (!m_gamepad->GetRawButton(buttonNames::buttonA))
            {
                break;
            }
            m_state = ON;
            break;

        case ON:
            if (m_gamepad->GetRawButton(buttonNames::buttonA))
            {
                start();
            }

            // Emergency stop button for the robot is the start button
            if (m_gamepad->GetRawButton(buttonNames::buttonStart))
            {
                m_state = OFF;
                break;
            }
            break;
    }


}

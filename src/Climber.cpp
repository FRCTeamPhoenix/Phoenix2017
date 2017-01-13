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

void Climber::run()
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
        case OFF:
            if (!m_gamepad->GetRawButton(buttonNames::buttonA))
            {
                break;
            }
            m_state = ON;
            break;

        case ON:
            if (m_gamepad->GetRawButton(buttonNames::buttonA))
            {
            }

    }


}

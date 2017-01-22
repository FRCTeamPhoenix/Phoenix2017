/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: evsci_000
 */
#include "Climber.h"
#include "constants.h"

Climber::Climber(
        SmartTalon * motor,
        Joystick * gamepad)
{
    m_state = OFF;
    m_motor = motor;
    m_gamepad = gamepad;
}

Climber::~Climber()
{
}

void Climber::start()
{
    m_motor->goAt(1.0);
}

void Climber::stop()
{
    m_motor->goAt(0.0);
}

void Climber::run()
{
    //bool m_climb = m_gamepad->GetRawButton(buttonNames::buttonA); //Reason why is because we need to setup buttons
    switch (m_state)
    {
        case OFF:
            // Button A is the climbing button
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonA))
            {
                break;
            }
            m_state = ON;
            break;

        case ON:
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonA))
            {
                start();
            }

            // Emergency stop button for the robot is the start button
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonStart))
            {
                m_state = OFF;
                break;
            }
            break;
    }


}

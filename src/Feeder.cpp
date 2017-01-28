/*
 * Feeder.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Feeder.h>

Feeder::Feeder(SmartTalon* feederMotor, Joystick* gamepad):
    m_feederMotor(feederMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Feeder::~Feeder()
{
}

State Feeder::getState()
{
    return m_state;
}

void Feeder::setState(State state)
{
    m_state = state;
}

void Feeder::run()
{
    switch (m_state)
    {
        case ON:
            start();
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonA))
            {
                m_state = OFF;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonA))
            {
                m_state = ON;
            }
            break;
    }
}

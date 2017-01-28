/*
 * Gatherer.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: cbadu
 */

#include <Gatherer.h>

Gatherer::Gatherer(SmartTalon* gathererMotor, Joystick* gamepad):
    m_gathererMotor(gathererMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Gatherer::~Gatherer()
{
}

State Gatherer::getState()
{
    return m_state;
}

void Gatherer::setState(State state)
{
    m_state = state;
}

void Gatherer::run()
{
    switch (m_state)
    {
        case ON:
            start();
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonX))
            {
                m_state = OFF;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonX))
            {
                m_state = ON;
            }
            break;
    }
}

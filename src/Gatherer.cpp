/*
 * Gatherer.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: cbadu
 */

#include <Gatherer.h>

Gatherer::Gatherer(Talon* GathererMotor, Joystick* gamepad):
    m_GathererMotor(GathererMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Gatherer::~Gatherer()
{
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
                break;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonX))
            {
                m_state = ON;
                break;
            }
            break;
    }
}

void Gatherer::start()
{
    m_GathererMotor->Set(0.5f);
}

void Gatherer::stop()
{
    m_GathererMotor->Set(0.0f);
}

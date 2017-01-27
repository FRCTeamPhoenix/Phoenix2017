/*
 * Feeder.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Feeder.h>

Feeder::Feeder(Talon* FeederMotor, Joystick* gamepad):
    m_FeederMotor(FeederMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Feeder::~Feeder()
{
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
                break;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonA))
            {
                m_state = ON;
                break;
            }
            break;
    }
}

void Feeder::start()
{
    m_FeederMotor->Set(0.5f);
}

void Feeder::stop()
{
    m_FeederMotor->Set(0.0f);
}

/*
 * Feeder.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Feeder.h>

Feeder::Feeder(SmartTalon& feederMotor, Joystick& gamepad):
    m_feederMotor(feederMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Feeder::~Feeder()
{
}

Feeder::State Feeder::getState()
{
    return m_state;
}

void Feeder::setState(Feeder::State state)
{
    m_state = state;
}

void Feeder::run()
{
    switch (m_state)
    {
    case ON:
        m_feederMotor.goAt(1.0);
        break;
    case OFF:
        m_feederMotor.goAt(0.0);
        break;
    }
}

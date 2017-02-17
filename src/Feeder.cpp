/*
 * Feeder.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include "Feeder.h"

Feeder::Feeder(SmartTalon& feederMotor, Joystick& gamepad):
    m_feederMotor(feederMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Feeder::~Feeder()
{
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
        m_feederMotor.goAt(0.3);
        break;

    case OFF:
        m_feederMotor.goAt(0.0);
        break;
    }
}

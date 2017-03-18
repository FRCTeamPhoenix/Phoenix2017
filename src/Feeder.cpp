/*
 * Feeder.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include "Feeder.h"

Feeder::Feeder(SmartTalon& feederMotor, Joystick& customBox):
    m_feederMotor(feederMotor),
    m_customBox(customBox)
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
    SmartDashboard::PutNumber("Talons/Feeder/Speed", m_feederMotor.GetEncVel());
    SmartDashboard::PutNumber("Talons/Feeder/Goal Speed", 0.70 * m_feederMotor.getMaxForwardSpeed());
    switch (m_state)
    {
    case ON:
        m_feederMotor.goAt(0.70);

        break;
    case OFF:
        m_feederMotor.goAt(0.0);
        break;
    }
}

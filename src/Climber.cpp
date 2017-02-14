/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: Joshua Calzadillas
 */
#include "Climber.h"

Climber::Climber(
        SmartTalon& motor):
        m_motor(motor)
{
    m_state = OFF;
}

Climber::~Climber()
{
}

//Gets the current state of the FlyWheels state machine
Climber::STATE Climber::getState()
{
    return m_state;
}

//Sets the state when there is a change in the FlyWheels state machine
void Climber::setState(STATE state)
{
    m_state = state;

}

void Climber::run()
{
    switch (m_state)
    {
        case OFF:
            m_motor.goAt(0.0);
            break;

        case ON:
            m_motor.goAt(1.0);
            break;
    }

}

/*
 * Gatherer.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: cbadu
 */

#include "Gatherer.h"

Gatherer::Gatherer(Talon& gathererMotor, Joystick& gamepad):
    m_gathererMotor(gathererMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Gatherer::~Gatherer()
{
}

Gatherer::State Gatherer::getState()
{
    return m_state;
}

void Gatherer::setState(Gatherer::State state)
{
    m_state = state;
}

void Gatherer::run()
{
    switch (m_state)
    {
    case ON:
        m_gathererMotor.Set(0.5);
        break;
    case OFF:
        m_gathererMotor.Set(0.0);
    }
}

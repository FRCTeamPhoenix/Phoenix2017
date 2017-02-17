/*
 * Indexer.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include "Indexer.h"

Indexer::Indexer(SmartTalon& indexerMotor, Joystick& gamepad):
    m_indexerMotor(indexerMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Indexer::~Indexer()
{
}

void Indexer::setState(State state)
{
    m_state = state;
}

void Indexer::run()
{
    switch (m_state)
    { 
    case ON:
        m_indexerMotor.goAt(0.3);
        break;

    case OFF:
        m_indexerMotor.goAt(0.0);
        break;

    case QUARTER_TURN:
        m_indexerMotor.goDistance(1024, 0.5);
        if (m_indexerMotor.GetSpeed() == 0.0)
        {
            m_state = OFF;
            break;
        }
        break;
    }
}

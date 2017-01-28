/*
 * Indexer.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Indexer.h>

Indexer::Indexer(SmartTalon* indexerMotor, Joystick* gamepad):
    m_indexerMotor(indexerMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Indexer::~Indexer()
{
}

Indexer::State Indexer::getState()
{
    return m_state;
}

void Indexer::setState(Indexer::State state)
{
    m_state = state;
}

void Indexer::run()
{
    switch (m_state)
    { 
    case ON:
        m_indexerMotor->Set(0.5);
        break;
    case OFF:
        if (m_gamepad->GetRawButton(DriveStationConstants::buttonX))
            m_indexerMotor->Set(0.5);
        else
            m_indexerMotor->Set(0.0);
        break;
    case QUARTER_TURN:
        /* TODO: Insert code for quarter-turn here */
        break;
    }
}

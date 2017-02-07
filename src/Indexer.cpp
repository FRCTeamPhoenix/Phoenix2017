/*
 * Indexer.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Indexer.h>

Indexer::Indexer(SmartTalon& indexerMotor, Joystick& gamepad):
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
    switch(m_state) {
        case TELEOP:
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                m_indexerMotor.goAt(1.0);
            else
                m_indexerMotor.goAt(0.0);
            break;
        case ON:
            m_indexerMotor.goAt(1.0);
            break;
        case OFF:
            m_indexerMotor.goAt(0.0);
            break;
    }
}

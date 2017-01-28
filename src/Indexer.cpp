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

State Indexer::getState()
{
    return m_state;
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
            start();
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB) &&
                    !m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = OFF;
            }
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = QUARTER_TURN;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB))
            {
                m_state = ON;
            }
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = QUARTER_TURN;
            }
            break;

        case QUARTER_TURN:
            start();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB))
            {
                m_state = ON;
            }
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB) &&
                    !m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = OFF;
            }
            break;
    }
}

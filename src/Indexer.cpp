/*
 * Indexer.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include <Indexer.h>

Indexer::Indexer(Talon* IndexerMotor, Joystick* gamepad):
    m_IndexerMotor(IndexerMotor),
    m_gamepad(gamepad)
{
    m_state = OFF;
}

Indexer::~Indexer()
{
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
                break;
            }
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = QuarterTurn;
                break;
            }
            break;

        case OFF:
            stop();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB))
            {
                m_state = ON;
                break;
            }
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = QuarterTurn;
                break;
            }
            break;

        case QuarterTurn:
            start();
            if (m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB))
            {
                m_state = ON;
                break;
            }
            if (!m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonB) &&
                    !m_gamepad->GetRawButton(DriveStationConstants::buttonNames::buttonY))
            {
                m_state = OFF;
                break;
            }
            break;
    }
}

void Indexer::start()
{
    m_IndexerMotor->Set(0.5f);
}

void Indexer::stop()
{
    m_IndexerMotor->Set(0.0f);
}

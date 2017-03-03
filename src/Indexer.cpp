/*
 * Indexer.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: cbadu
 */

#include "Indexer.h"
#include "Robot.h"
#include "Actions/AllActions.h"

Indexer::Indexer(SmartTalon& indexerMotor, Joystick& customBox):
    m_indexerMotor(indexerMotor),
    m_customBox(customBox),
    m_speedGroup(new ActionGroup())
{

    m_state = OFF;
    m_speed = 1.0;


//Drive full






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

void Indexer::setSpeed(double speed)
{
    m_speed = speed;
}

void Indexer::run()
{
    switch(m_state) {
        case TELEOP:
            if (m_customBox.GetRawButton(DriveStationConstants::buttonX)) {
                m_indexerMotor.goAt(m_speed);

                if(m_indexerMotor.GetIaccum() > 700000)
                    m_indexerMotor.ClearIaccum();
            }
            else
                m_indexerMotor.goAt(0.0);
            break;
        case ON:
            //m_indexerMotor.goAt(m_speed);
            m_speedGroup->execute(m_speedGroup->getContainedActions());

            if(m_indexerMotor.GetIaccum() > 700000)
                m_indexerMotor.ClearIaccum();
            break;
        case OFF:
            m_indexerMotor.goAt(0.0);
            break;
    }
}

void Indexer::initSpeedGroup(std::shared_ptr<Robot> robot)
{
    json jsonDoc = "{"
            "\"type\": \"ActionGroup\","
            "\"name\": \"Indexer Speed Group\","

            "\"startingCondition\": 0,"
            "\"containedActions\": ["
                "{"
                    "\"type\": \"IndexerRunTime\","
                    "\"startingCondition\": 0,"

                    "\"speed\": 0.75,"
                    "\"duration\": 0.5,"

                    "\"dependencies\": []"
                "},"

                "{"
                    "\"type\": \"IndexerRunTime\","
                    "\"startingCondition\": 0,"

                    "\"speed\": 0.3,"
                    "\"duration\": 0.1,"

                    "\"dependencies\": ["
                        "{\"place\": 0, \"requiredCondition\": 2}"
                    "]"
                "},"

                "{"
                    "\"type\": \"ResetAction\","
                    "\"startingCondition\": 0,"

                    "\"placesToReset\": [0, 1, 2],"

                    "\"dependencies\": ["
                        "{\"place\": 1, \"requiredCondition\": 2}"
                    "]"
                "}"
            "],"
            "\"dependencies\": [],"
            "\"doneDependencies\": []"
        "}"_json;

    m_speedGroup->initActionGroup(jsonDoc, robot);
}

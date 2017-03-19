/*
 * SetIndexerState.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#include "SetIndexerState.h"
#include "../Robot.h"

SetIndexerState::SetIndexerState(int state, double duration, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
    Action(dependencies, robot),
    m_state(state),
    m_duration(duration)
{ }

SetIndexerState::SetIndexerState(json& action, shared_ptr<Robot> robot):
    Action(),
    m_state(action["state"]),
    m_duration(action["duration"])
{
    initAction(action, robot);

}

void SetIndexerState::run()
{

    m_robot->setIndexerState(m_state);

    if(getCondition() == dependency::NotStarted)
    {
        m_timer.Reset();
        m_timer.Start();
        start();
    }
    else if (m_timer.Get() > m_duration)
    {
        finish();
        m_timer.Start();
    }

}

void SetIndexerState::reset()
{
    resetCondition();
    m_timer.Stop();
    m_timer.Reset();
}

/*
 * SetShooterState.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#include "SetShooterState.h"
#include "../Robot.h"

SetShooterState::SetShooterState(int state, double duration, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
Action (dependencies, robot),
m_state(state),
m_duration(duration)
{
}

SetShooterState::SetShooterState(json& action, shared_ptr<Robot> robot) :
        Action(),
        m_state(action["state"]),
        m_duration(action["duration"])
{
    initAction(action, robot);
}

void SetShooterState::run() {

    m_robot->setFeederState(m_state);
    m_robot->setFlywheelState(m_state);

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

void SetShooterState::reset()
{
    resetCondition();
    m_timer.Stop();
    m_timer.Reset();
}

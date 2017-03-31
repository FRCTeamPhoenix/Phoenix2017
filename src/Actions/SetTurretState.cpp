//
// Created by William Gebhardt on 3/30/17.
//

#include "SetTurretState.h"
#include "../Robot.h"

SetTurretState::SetTurretState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
Action (dependencies, robot),
m_state(state)
{ }

SetTurretState::SetTurretState(json &action, shared_ptr<Robot> robot) :
        Action(),
        m_state(action["state"])
{
    initAction(action, robot);
}

void SetTurretState::run()
{
    m_robot->setTurretState(m_state);
    finish();
}

void SetTurretState::reset()
{
    resetCondition();
}
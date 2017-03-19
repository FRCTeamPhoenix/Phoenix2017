//
// Created by William Gebhardt on 3/19/17.
//

#include "SetGearTargetingState.h"
#include "../Robot.h"

SetGearTargetingState::SetGearTargetingState(int state, vector<shared_ptr<dependency>> dependencies,
                                             shared_ptr<Robot> robot):
    Action(dependencies, robot),
    m_desiredState(state)
{ }

SetGearTargetingState::SetGearTargetingState(json &action, shared_ptr<Robot> robot):
    Action(),
    m_desiredState(action["state"])
{
    initAction(action, robot);
}

void SetGearTargetingState::run()
{
    m_robot->setGearTargetingState(m_desiredState);
    finish();
}

void SetGearTargetingState::reset()
{
    resetCondition();
    m_robot->setGearTargetingState(0);
}


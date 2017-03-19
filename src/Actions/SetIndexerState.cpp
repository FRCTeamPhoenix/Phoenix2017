/*
 * SetIndexerState.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#include "SetIndexerState.h"
#include "../Robot.h"

SetIndexerState::SetIndexerState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
    Action(dependencies, robot),
    m_state(state)
{ }

SetIndexerState::SetIndexerState(json& action, shared_ptr<Robot> robot):
    Action(),
    m_state(action["state"])
{
    initAction(action, robot);

}

void SetIndexerState::run() {

    m_robot->setIndexerState(m_state);

}

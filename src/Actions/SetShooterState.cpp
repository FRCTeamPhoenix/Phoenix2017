/*
 * SetShooterState.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: Brin Harper
 */

#include <Actions/SetShooterState.h>
#include "../Robot.h"

SetShooterState::SetShooterState(int state, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
Action (dependencies, robot),
m_state(state)
{
}

SetShooterState::SetShooterState(json& action, shared_ptr<Robot> robot) :
        Action(),
        m_state(action["state"])
{
    initAction(action, robot);
}

void SetShooterState::run() {

    //m_robot->setFlywheelState(m_flywheelState);
    //m_robot->setFeederState(m_feederState);

}

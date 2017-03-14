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
    if (m_state == 0) {
        m_flywheelState = FlyWheels::STATE::OFF;
        m_feederState = Feeder::State::OFF;
    } else {
        m_flywheelState = FlyWheels::STATE::FLATRATE;
        m_feederState = Feeder::State::ON;
    }
}

SetShooterState::SetShooterState(json& action, shared_ptr<Robot> robot) :
        Action(),
        m_state(action["state"])
{
    if (m_state == 0) {
        m_flywheelState = FlyWheels::STATE::OFF;
        m_feederState = Feeder::State::OFF;
    } else {
        m_flywheelState = FlyWheels::STATE::FLATRATE;
        m_feederState = Feeder::State::ON;
    }

    initAction(action, robot);
}

void SetShooterState::run() {

    m_robot->m_flywheel.setState(m_flywheelState);
    m_robot->m_feeder.setState(m_feederState);

}

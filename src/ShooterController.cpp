/*
 * Shooter.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include <ShooterController.h>

ShooterController::ShooterController(
        FlyWheels& flywheel,
        Turret& turret):
        m_flywheel(flywheel),
        m_turret(turret)

{
    m_state = IDLE;
}

ShooterController::~ShooterController()
{

}

void ShooterController::run()
{
    //Run functinos of FlyWheels and Turret
    m_flywheel.run();
    m_turret.run();

    switch (m_state)
    {

    //Idle state for the ShooterController
    case IDLE:

        break;

    //Auto state for the ShooterController
    case AUTO:

        break;

    //Teleop state for the ShooterController
    case TELEOP:

        break;
    }
}

//Gets the current state of the ShooterController state machine
ShooterController::STATE ShooterController::getState()
{
    return m_state;
}

//Sets the state when there is a change in the ShooterController state machine
void ShooterController::setState(STATE state)
{
    m_state = state;
}

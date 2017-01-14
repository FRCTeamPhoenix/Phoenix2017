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
	switch (getState())
	{
	case IDLE:

		break;

	case AUTO:

		break;

	case TELEOP:

		break;
	}
}



ShooterController::STATE ShooterController::getState()
{
	return m_state;
}

void ShooterController::setState(STATE state)
{
	m_state = state;
}

/*
 * Shooter.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include <ShooterController.h>

ShooterController::ShooterController(
		Talon* rightFlyWheelMotor,
		Talon* leftFlyWheelMotor,
		Encoder* rightFlyWheelEncoder,
		Encoder* leftFlyWheelEncoder
		):
		m_rightFlyWheelMotor(rightFlyWheelMotor),
		m_leftFlyWheelMotor(leftFlyWheelMotor),
		m_rightFlyWheelEncoder(rightFlyWheelEncoder),
		m_leftFlyWheelEncoder(leftFlyWheelEncoder)
{

}

ShooterController::~ShooterController()
{

}

void ShooterController::run()
{
	switch(getState())
	{
	case IDLE:
		break;
	case STOP:
		break;
	case SPINNING:
		break;
	case SHOOTING:
		break;
	case LOADING:
		break;
	}
}

void ShooterController::start()
{

}

ShooterController::STATE ShooterController::getState()
{

}

ShooterController::STATE ShooterController::setState()
{

}

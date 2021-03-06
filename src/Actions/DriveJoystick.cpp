/*
 * DriveJoysitck.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: larry
 */

#include "DriveJoystick.h"
#include "../Robot.h"

DriveJoystick::DriveJoystick(vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot):
Action(dependencies, robot)
{
	// TODO Auto-generated constructor stub
}

DriveJoystick::DriveJoystick(json& action, shared_ptr<Robot> robot):
Action()
{
	initAction(action, robot);
}


void DriveJoystick::run()
{
	m_robot->driveJoystick();
}

void DriveJoystick::reset()
{
	resetCondition();
}

DriveJoystick::~DriveJoystick() {
	// TODO Auto-generated destructor stub
}


/*
 * ActionRotate.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#include <Actions/ActionRotate.h>

ActionRotate::ActionRotate(relativeMecanumDrivetrain * driveTrain, double speed, double angle):
    Action(),
    m_driveTrain(driveTrain),
    m_speed(speed),
    m_angle(angle)
{

}

void ActionRotate::init()
{
    m_initialized = true;
    m_driveTrain->rotate(m_angle, m_speed);
}

bool ActionRotate::execute()
{
    return true;
}

ActionRotate::~ActionRotate()
{
    // TODO Auto-generated destructor stub
}


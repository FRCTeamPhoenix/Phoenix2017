/*
 * ActionGoDistance.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#include <Actions/ActionGoDistance.h>

ActionGoDistance::ActionGoDistance(relativeMecanumDrivetrain * driveTrain, double distance, double angle, double speed):
    Action(),
    m_driveTrain(driveTrain),
    m_distance(distance),
    m_angle(angle),
    m_speed(speed)
{

}

void ActionGoDistance::init()
{
    m_initialized = true;
    m_driveTrain->moveDistance(m_distance, m_angle, m_speed);
}

bool ActionGoDistance::execute()
{
    return true;
}

ActionGoDistance::~ActionGoDistance()
{

}


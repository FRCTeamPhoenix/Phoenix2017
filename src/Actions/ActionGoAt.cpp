/*
 * ActionGoAt.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#include <Actions/ActionGoAt.h>

ActionGoAt::ActionGoAt(relativeMecanumDrivetrain * driveTrain, double speed, double angle):
    Action(),
    m_driveTrain(driveTrain),
    m_speed(speed),
    m_angle(angle)
{
    // TODO Auto-generated constructor stub

}

void ActionGoAt::init()
{
    m_initialized = true;
    m_driveTrain->moveAt(m_speed, m_angle);
}

bool ActionGoAt::execute()
{
    return true;
}

ActionGoAt::~ActionGoAt()
{
    // TODO Auto-generated destructor stub
}


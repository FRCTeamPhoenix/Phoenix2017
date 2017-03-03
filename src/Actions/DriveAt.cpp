//
// Created by William Gebhardt on 1/31/17.
//

#include "DriveAt.h"
#include "../Robot.h"

DriveAt::DriveAt (double speed, double angle, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot):
    Action(dependencies, robot),
    m_speed(speed),
    m_angle(angle)
{ }

DriveAt::DriveAt (json &action, shared_ptr<Robot> robot):
    Action(),
    m_speed(action["speed"]),
    m_angle(action["angle"])
{
    initAction(action, robot);
}


void DriveAt::run ()
{
    m_robot->driveAt(m_speed, m_angle);
}

void DriveAt::reset ()
{
    resetCondition ();
}

//
// Created by William Gebhardt on 1/31/17.
//

#include "DriveAt.h"

DriveAt::DriveAt (double speed, double angle, vector<shared_ptr<dependency>> dependencies):
    Action(dependencies),
    m_speed(speed),
    m_angle(angle)
{ }

DriveAt::DriveAt (json &action, Robot *robot)
try : Action(),
      m_speed(action["speed"]),
      m_angle(action["angle"])
{
    initAction(action, robot);
}
catch (...)
{
    std::cout << "DriveAt Constuctor Fail" << std::endl;
}

void DriveAt::run ()
{
    m_robot->driveAt(m_speed, m_angle);
}

void DriveAt::reset ()
{
    resetCondition ();
}
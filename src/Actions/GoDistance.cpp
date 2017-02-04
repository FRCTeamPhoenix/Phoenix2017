//
// Created by William Gebhardt on 2/2/17.
//

#include "GoDistance.h"

GoDistance::GoDistance (double distance, double angle, double speed, double tolerance, vector<shared_ptr<dependency>> dependencies):
    Action(dependencies),
    m_distance(distance),
    m_angle(angle),
    m_speed(speed),
    m_tolerance(tolerance),
    m_count(0)
{ }

GoDistance::GoDistance (json &action, shared_ptr<Robot> robot)
try : Action(),
      m_distance(action["distance"]),
      m_angle(action["angle"]),
      m_speed(action["speed"]),
      m_tolerance(action["tolerance"]),
      m_count(0)
{
    cout << "Done with Go Distance Init" << endl;
    initAction(action, robot);
}
catch (...)
{
    std::cout << "GoDistance Constuctor Fail" << std::endl;
}

void GoDistance::run ()
{
    if(getCondition() == dependency::NotStarted)
    {
        m_robot->driveDistance (m_distance, m_angle, m_speed);
        start ();
    }
    else if(m_count < 5)
    {
        m_count ++;
    }
    else if(m_robot->doneDriveMove (m_tolerance))
    {
        finish();
    }

}

void GoDistance::reset ()
{
    resetCondition();
    m_count = 0;
}
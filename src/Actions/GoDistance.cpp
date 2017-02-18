//
// Created by William Gebhardt on 2/2/17.
//

#include "GoDistance.h"

GoDistance::GoDistance (double distance, double angle, double speed, double tolerance, vector<shared_ptr<dependency>> dependencies):
    Action(dependencies),
    m_distance(distance),
    m_angle(angle),
    m_speed(speed),
    m_tolerance(tolerance)
{ }

GoDistance::GoDistance (json &action, shared_ptr<Robot> robot):
    Action(),
    m_distance(action["distance"]),
    m_angle(action["angle"]),
    m_speed(action["speed"]),
    m_tolerance(action["tolerance"])
{
    initAction(action, robot);
}

void GoDistance::run ()
{
    if(getCondition() == dependency::NotStarted)
    {
        m_robot->driveDistance (m_distance, m_angle, m_speed);
        m_timer.Reset ();
        m_timer.Start ();
        start ();
    }
    else if(m_timer.Get() < 0.1)
    {
    }
    else if(m_robot->doneDriveMove (m_tolerance))
    {
        finish();
        cout << m_name << " is done" << endl;
        m_timer.Stop ();
    }

}

void GoDistance::reset ()
{
    resetCondition();
}

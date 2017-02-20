//
// Created by William Gebhardt on 2/5/17.
//

#include "Rotate.h"

Rotate::Rotate (double angle, double speed, double tolerance, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot):
    Action(dependencies, robot),
    m_angle(angle),
    m_speed(speed),
    m_tolerance(tolerance)
{ }

Rotate::Rotate (json &action, shared_ptr<Robot> robot):
    Action(),
    m_angle(action["angle"]),
    m_speed(action["speed"]),
    m_tolerance(action["tolerance"])
{
    initAction(action, robot);
}

void Rotate::run ()
{
//    LOGI << m_name << ": is running";

    if(getCondition() == dependency::NotStarted)
    {
        m_robot->rotateAngle (m_angle, m_speed);
        m_timer.Reset ();
        m_timer.Start ();
        start ();
    }
    else if(m_timer.Get() < 0.1)
    {
//        LOGI << m_name << ": " << m_timer.Get ();
    }
    else if(m_robot->doneDriveMove (m_tolerance))
    {
        finish();
        m_timer.Stop ();
    }

}

void Rotate::reset ()
{
    resetCondition();
}
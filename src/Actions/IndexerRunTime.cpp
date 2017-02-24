//
// Created by William Gebhardt on 2/18/17.
//

#include "IndexerRunTime.h"


IndexerRunTime::IndexerRunTime (double speed, double duration, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot):
        Action(dependencies, robot),
        m_speed(speed),
        m_duration(duration)
{ }

IndexerRunTime::IndexerRunTime (json &action, shared_ptr<Robot> robot):
        Action(),
        m_speed(action["speed"]),
        m_duration(action["duration"])
{
    initAction(action, robot);
}


void IndexerRunTime::run ()
{
    m_robot->setIndexerSpeed(m_speed);

    if(getCondition() == dependency::NotStarted)
    {
        m_timer.Reset();
        m_timer.Start();
        start();
    }
    else if (m_timer.Get() > m_duration)
    {
        finish();
        m_timer.Start();
    }
}

void IndexerRunTime::reset ()
{
    resetCondition ();
    m_timer.Stop();
    m_timer.Reset();
}

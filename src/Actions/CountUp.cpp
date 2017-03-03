//
// Created by William Gebhardt on 1/22/17.
//

#include "CountUp.h"
#include "../Robot.h"
#include "Action.h"
#include "dependency.h"
#include <vector>
#include <iostream>
#include "../plog/Log.h"

CountUp::CountUp (int start, int end, vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot):
    Action(dependencies, robot),
    m_current(start),
    m_start(start),
    m_end(end)


{ }

CountUp::CountUp (json& action, shared_ptr<Robot> robot):
    Action(),
    m_current(action["start"]),
    m_start(action["start"]),
    m_end(action["end"])
{

    initAction (action, robot);
}


void CountUp::run ()
{
    LOGI << m_name << ":\t" << m_current;

    m_current++;

    if(m_current > m_start)
        start();

    if(m_current >= m_end)
        finish();
}

void CountUp::reset ()
{
    resetCondition ();
    m_current = m_start;
}

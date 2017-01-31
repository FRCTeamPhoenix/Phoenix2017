//
// Created by William Gebhardt on 1/22/17.
//

#include "CountUp.h"

CountUp::CountUp (int start, int end, vector<shared_ptr<dependency>> dependencies):
    Action(dependencies),
    m_current(start),
    m_start(start),
    m_end(end)


{ }

CountUp::CountUp (json& action)
try :   Action(),
        m_current(action["start"]),
        m_start(action["start"]),
        m_end(action["end"])
{

    initAction(action);
}
catch (...)
{
    std::cout << "CountDown Constuctor Fail" << std::endl;
}


void CountUp::run ()
{
    LOGI << m_name << ":\t" << m_current;

    m_current++;

    if(m_current > m_start)
        start();

    if(m_current > m_end)
        finish();
}

void CountUp::reset ()
{
    resetCondition ();
    m_current = m_start;
}

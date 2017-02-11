//
// Created by William Gebhardt on 1/23/17.
//

#include "dependency.h"


dependency::dependency (int p, condition rc):
    m_place(p),
    m_requiredCondition(rc)
{

}

dependency::dependency (json dependency)
{
    try
    {
        m_place = dependency["place"];
        m_requiredCondition = (dependency::condition)(int)dependency["requiredCondition"];

    }
    catch (...)
    {
        LOGI << "dependency failed to load";
    }

}


int dependency::getPlace ()
{
    return m_place;
}


dependency::condition dependency::getCondition ()
{
    return m_requiredCondition;
}
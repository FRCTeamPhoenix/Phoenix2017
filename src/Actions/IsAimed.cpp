//
// Created by William Gebhardt on 4/2/17.
//

#include "IsAimed.h"
#include "../Robot.h"

IsAimed::IsAimed(vector<shared_ptr<dependency>> dependencies, shared_ptr<Robot> robot) :
        Action (dependencies, robot)
{ }

IsAimed::IsAimed(json &action, shared_ptr<Robot> robot) :
        Action()
{
    initAction(action, robot);
}

void IsAimed::run()
{

    if(m_robot->isTurretAimed()){
        m_currentCondition = dependency::Started;
    }
    else
    {
        m_currentCondition = dependency::NotStarted;
    }
}
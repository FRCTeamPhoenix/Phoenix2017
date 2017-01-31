//
// Created by William Gebhardt on 1/15/17.
//

#include "ActionMotorDoneDistance.h"


ActionMotorDoneDistance::ActionMotorDoneDistance (relativeMecanumDrivetrain &driveTrain, int allowedError):
    Action(),
    m_driveTrain(driveTrain),
    m_allowedError(allowedError)
{ }

void ActionMotorDoneDistance::init()
{
    m_initialized = true;
}

bool ActionMotorDoneDistance::execute()
{
    if(m_driveTrain.getAvgError () < m_allowedError)
        return true;
    return false;
}

ActionMotorDoneDistance::~ActionMotorDoneDistance()
{
    // TODO Auto-generated destructor stub
}


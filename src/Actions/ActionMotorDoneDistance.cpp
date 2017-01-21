//
// Created by William Gebhardt on 1/15/17.
//

#include "ActionMotorDoneDistance.h"


ActionMotorDoneDistance::ActionMotorDoneDistance (relativeMecanumDrivetrain &driveTrain):
    Action(),
    m_driveTrain(driveTrain)
{ }

void ActionMotorDoneDistance::init()
{
    m_initialized = true;
}

bool ActionMotorDoneDistance::execute()
{
    if(m_driveTrain.doneMove())
        return true;
    return false;
}

ActionMotorDoneDistance::~ActionMotorDoneDistance()
{
    // TODO Auto-generated destructor stub
}


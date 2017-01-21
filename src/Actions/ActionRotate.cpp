/*
 * ActionRotate.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: cooli
 */

#include "ActionRotate.h"
#include "../relativeMecanumDrivetrain.h"
#include "WPILib.h"


ActionRotate::ActionRotate(relativeMecanumDrivetrain& driveTrain, double angle, double speed):
    Action(),
    m_driveTrain(driveTrain),
    m_angle(angle),
    m_speed(speed)
{

}

void ActionRotate::init()
{
    m_driveTrain.moveDistance(0, 0, m_speed, m_angle);
    m_initialized = true;


}

bool ActionRotate::execute()
{
    return true;
}

ActionRotate::~ActionRotate()
{
    // TODO Auto-generated destructor stub
}


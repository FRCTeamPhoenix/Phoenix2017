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

    std::ostringstream Angel;
    Angel << "Angle: ";
    Angel << (m_angle);
    SmartDashboard::PutString("DB/String 5", Angel.str());

    std::ostringstream Speed;
    Speed << "speed: ";
    Speed << (m_speed);
    SmartDashboard::PutString("DB/String 6", Speed.str());

    m_driveTrain.rotate(m_angle, m_speed);
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


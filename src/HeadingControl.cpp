//
// Created by William Gebhardt on 1/21/17.
//

#include "HeadingControl.h"


HeadingControl::HeadingControl (ADIS16448_IMU& gyro, GyroAxes axis, bool invertDirection):
    m_gyro(gyro),
    m_axisOfInterest(axis),
    m_invertDirection(invertDirection),
    m_currentOutput(0),
    m_gyroController(0.01, 0, 0, this, this)
{
    m_gyroController.Enable ();

}

double HeadingControl::PIDGet ()
{
	double angle;
//    std::stringstream rotation;

    switch(m_axisOfInterest){
        case x:
        	angle = m_gyro.GetAngleX();

//            rotation << "Rotation: " << angle;
//            SmartDashboard::PutString("DB/String 5", rotation.str());
            return angle;
        case y:
        	angle = m_gyro.GetAngleY();
//            rotation << "Rotation: " << angle;
//            SmartDashboard::PutString("DB/String 5", rotation.str());
            return angle;
        case z:
        	angle = m_gyro.GetAngleZ();
//            rotation << "Rotation: " << angle;
//            SmartDashboard::PutString("DB/String 5", rotation.str());
            return angle;
    }
    return 0;
}


void HeadingControl::PIDWrite (double output)
{
    if(m_invertDirection){
        output *= -1;
    }


    m_currentOutput = output;
}

double HeadingControl::getOutput ()
{
    return m_currentOutput;
}

bool HeadingControl::isDone ()
{
    double angle = 0;
    switch(m_axisOfInterest){
        case x:
            angle = m_gyro.GetAngleX();
            break;
        case y:
            angle = m_gyro.GetAngleY();
            break;
        case z:
            angle = m_gyro.GetAngleZ();
            break;
    }

    double goal = m_gyroController.GetSetpoint ();

    if(fabs(goal - angle) < 5){
        return true;
    }
    return false;

}

void HeadingControl::setGoal (double goal)
{
    m_gyroController.SetSetpoint (goal);
}

void HeadingControl::keepAt ()
{
    switch(m_axisOfInterest){
        case x:
            m_gyroController.SetSetpoint (m_gyro.GetAngleX ());
            break;
        case y:
            m_gyroController.SetSetpoint (m_gyro.GetAngleY ());
            break;
        case z:
            m_gyroController.SetSetpoint (m_gyro.GetAngleZ ());
            break;
    }
}

void HeadingControl::changeAngle (double change)
{
    switch(m_axisOfInterest){
        case x:
            m_gyroController.SetSetpoint (m_gyro.GetAngleX () + change);
            break;
        case y:
            m_gyroController.SetSetpoint (m_gyro.GetAngleY () + change);
            break;
        case z:
            m_gyroController.SetSetpoint (m_gyro.GetAngleZ () + change);
            break;
    }
}


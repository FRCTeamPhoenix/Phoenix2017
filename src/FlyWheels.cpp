/*
 * FlyWheels.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "FlyWheels.h"

FlyWheels::FlyWheels(
        SmartTalon& rightFlyWheelMotor,
        SmartTalon& leftFlyWheelMotor,
        ShooterCalibrator& shooterCalibrator,
        Lidar& lidar,
        Joystick& customBox):
        m_lowerFlyWheelMotor(leftFlyWheelMotor),
        m_topFlyWheelMotor(rightFlyWheelMotor),
        m_shooterCalibrator(shooterCalibrator),
        m_lidar(lidar),
        m_customBox(customBox)
{
    m_state = STATE::OFF;
}

FlyWheels::~FlyWheels()
{

}

void FlyWheels::run()
{
    switch (m_state)
    {

        //Off State for the FlyWheels
        //Motors are given 0.0f to stop the flywheels
        //Changes state to On if the right trigger is pressed
        case OFF: //
            m_lowerFlyWheelMotor.goAt(0.0); //stop right FlyWheel
            m_topFlyWheelMotor.goAt(0.0); //stop left FlyWheel
            break;
        case FLATRATE: //Speed based on given number.
            setLeftSpeed(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
            setRightSpeed(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
            break;
        case LIDARRATE: //Speed based on lidar Distance
        {

            // Max/min speeds must be set in Talon json
            int topSpeed = m_shooterCalibrator.getTopFlywheelVelocity(SmartDashboard::GetNumber("../datatable/high_goal_distance", 0.0));
            int lowerSpeed = m_shooterCalibrator.getLowFlywheelVelocity(SmartDashboard::GetNumber("../datatable/high_goal_distance", 0.0));

            m_topFlyWheelMotor.goAtVelocity(topSpeed);
            m_lowerFlyWheelMotor.goAtVelocity(lowerSpeed);

        }
            break;

        case JOYSTICKRATE: //The position that the joystick is in determines the speed.
        	double speed = ((m_customBox.GetRawAxis(DriveStationConstants::potFlywheelSpeed) + 1) / 2) * 0.55;

            SmartDashboard::PutNumber("Talons/Flywheels/Top Goal Speed", speed * m_topFlyWheelMotor.getMaxForwardSpeed());
            SmartDashboard::PutNumber("Talons/Flywheels/Bottom Goal Speed", speed * m_lowerFlyWheelMotor.getMaxForwardSpeed());


            SmartDashboard::PutNumber("Talons/Flywheels/Top Speed", m_topFlyWheelMotor.GetEncVel());
            SmartDashboard::PutNumber("Talons/Flywheels/Bottom Speed", m_lowerFlyWheelMotor.GetEncVel());

            SmartDashboard::PutNumber("Talons/Flywheels/Top Voltage", m_topFlyWheelMotor.GetOutputVoltage());
            SmartDashboard::PutNumber("Talons/Flywheels/Bottom Voltage", m_lowerFlyWheelMotor.GetOutputVoltage());

            setRightSpeed(speed);
            setLeftSpeed(speed);
            break;
    }
}

//Gets the current state of the FlyWheels state machine
FlyWheels::STATE FlyWheels::getState()
{
    return m_state;
}

//Sets the state when there is a change in the FlyWheels state machine
void FlyWheels::setState(STATE state)
{
    m_state = state;

}

void FlyWheels::setLeftSpeed(double speed)
{
    m_topFlyWheelMotor.goAt(speed);
}

void FlyWheels::setRightSpeed(double speed)
{
    m_lowerFlyWheelMotor.goAt(speed);
}

void FlyWheels::setBothSpeed(double speed)
{
    m_topFlyWheelMotor.goAt(speed);
    m_lowerFlyWheelMotor.goAt(speed);
}

bool FlyWheels::inRange()
{
    return m_shooterCalibrator.inRange(m_lidar.getDistance());
}

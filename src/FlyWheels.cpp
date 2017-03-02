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
        m_lowerFlyWheelMotor(rightFlyWheelMotor),
        m_topFlyWheelMotor(leftFlyWheelMotor),
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
            int topSpeed = m_shooterCalibrator.getTopFlywheelVelocity(m_lidar.getDistance());
            int lowerSpeed = m_shooterCalibrator.getLowFlywheelVelocity(m_lidar.getDistance());

            m_topFlyWheelMotor.goAtVelocity(topSpeed);
            m_lowerFlyWheelMotor.goAtVelocity(lowerSpeed);

        }
            break;

        case JOYSTICKRATE: //The position that the joystick is in determines the speed.
        	double speed = ((m_customBox.GetRawAxis(DriveStationConstants::potFlywheelSpeed) + 1) / 2) * 0.55;

            SmartDashboard::PutNumber("Top Goal Speed", speed * 80000 / 4);
            SmartDashboard::PutNumber("Bottom Goal Speed", speed * 80000);


            SmartDashboard::PutNumber("Top Speed", m_topFlyWheelMotor.GetEncVel());
            SmartDashboard::PutNumber("Bottom Speed", m_lowerFlyWheelMotor.GetEncVel());

            SmartDashboard::PutNumber("Top Voltage", m_topFlyWheelMotor.GetOutputVoltage());
            SmartDashboard::PutNumber("Bottom Voltage", m_lowerFlyWheelMotor.GetOutputVoltage());

            setRightSpeed(speed);
            setLeftSpeed(speed / 4);
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

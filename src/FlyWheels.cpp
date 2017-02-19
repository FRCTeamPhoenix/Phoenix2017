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
        Joystick& gamepad):
        m_lowerFlyWheelMotor(rightFlyWheelMotor),
        m_topFlyWheelMotor(leftFlyWheelMotor),
        m_shooterCalibrator(shooterCalibrator),
        m_lidar(lidar),
        m_gamepad(gamepad)
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

            int topSpeed = m_shooterCalibrator.getTopFlywheelVelocity(m_lidar.getDistance());
            int lowerSpeed = m_shooterCalibrator.getLowFlywheelVelocity(m_lidar.getDistance();

            if (topSpeed > ShooterConstants::maxFlywheelVelocity) {
                m_lowerFlyWheelMotor.goAtVelocity(ShooterConstants::maxFlywheelVelocity);
            } else if (topSpeed < ShooterConstants::minFlywheelVelocity) {
                m_lowerFlyWheelMotor.goAtVelocity(ShooterConstants::minFlywheelVelocity);
            } else {
                m_lowerFlyWheelMotor.goAtVelocity(topSpeed);
            }

            if (lowerSpeed > ShooterConstants::maxFlywheelVelocity) {
                m_topFlyWheelMotor.goAtVelocity(ShooterConstants::maxFlywheelVelocity);
            } else if (lowerSpeed < ShooterConstants::minFlywheelVelocity) {
                m_topFlyWheelMotor.goAtVelocity(ShooterConstants::minFlywheelVelocity);
            } else {
                m_topFlyWheelMotor.goAtVelocity(lowerSpeed);
            }

            break;

        case JOYSTICKRATE: //The position that the joystick is in determines the speed.
            double speed = ((m_gamepad.GetRawAxis(3) + 1) / 2) * 0.6;

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

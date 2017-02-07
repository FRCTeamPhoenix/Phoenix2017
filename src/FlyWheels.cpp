/*
 * FlyWheels.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include <FlyWheels.h>

FlyWheels::FlyWheels(
        SmartTalon& rightFlyWheelMotor,
        SmartTalon& leftFlyWheelMotor,
        ShooterCalibrator& shooterCalibrator,
        Lidar& lidar,
        Joystick& gamepad,
        Joystick& joystick):
        m_rightFlyWheelMotor(rightFlyWheelMotor),
        m_leftFlyWheelMotor(leftFlyWheelMotor),
        m_shooterCalibrator(shooterCalibrator),
        m_lidar(lidar),
        m_gamepad(gamepad),
        m_joystick(joystick)
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
            m_rightFlyWheelMotor.goAt(0.0); //stop right FlyWheel
            m_leftFlyWheelMotor.goAt(0.0); //stop left FlyWheel

            if (m_gamepad.GetRawButton(DriveStationConstants::triggerRT))
            {
                setState(FLATRATE);
            }
            if(m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
                setState(LIDARRATE);
            }
            if(m_gamepad.GetRawButton(DriveStationConstants::buttonB))
            {
                setState(JOYSTICKRATE);
            }
            break;

        case FLATRATE: //Speed based on given number.
            setLeftSpeed(0.5);
            setRightSpeed(0.5);
            if (!m_gamepad.GetRawButton(DriveStationConstants::triggerRT))
            {
                setState(OFF);
            }
            break;
        case LIDARRATE: //Speed based on lidar Distance
            setRightSpeed(m_shooterCalibrator.getFlywheelPower(m_lidar.getFastAverage()));
            setLeftSpeed(m_shooterCalibrator.getFlywheelPower(m_lidar.getFastAverage()));
            if(!m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
                setState(OFF);
            }
            break;
        case JOYSTICKRATE: //The position that the joystick is in determines the speed.
            setRightSpeed(m_joystick.GetThrottle());
            setRightSpeed(m_joystick.GetThrottle());
//            setBothSpeed(m_joystick.GetThrottle());
            if(!m_gamepad.GetRawButton(DriveStationConstants::buttonB))
            {
                setState(OFF);
            }
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
    m_leftFlyWheelMotor.goAt(speed);
}

void FlyWheels::setRightSpeed(double speed)
{
    m_rightFlyWheelMotor.goAt(speed);
}

void FlyWheels::setBothSpeed(double speed)
{
    m_leftFlyWheelMotor.goAt(speed);
    m_rightFlyWheelMotor.goAt(speed);
}

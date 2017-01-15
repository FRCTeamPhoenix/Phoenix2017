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
        Joystick& gamepad):
        m_rightFlyWheelMotor(rightFlyWheelMotor),
        m_leftFlyWheelMotor(leftFlyWheelMotor),
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
    //Ganges state to On if the right trigger is pressed
    case OFF:
        m_rightFlyWheelMotor.goAt(0.0); //stop right FlyWheel
        m_leftFlyWheelMotor.goAt(0.0); //stop left FlyWheel

        if (m_gamepad.GetRawButton(DriveStationConstants::triggerRT))
        {
            setState(ON);
        }
        break;

        //On state for the FlyWheels
        //Motors are given a fixed value
        //Changes state to Off if the left trigger is pressed
    case ON:
        m_rightFlyWheelMotor.goAt(motorSpeed); // set right FlyWheel speed
        m_leftFlyWheelMotor.goAt(motorSpeed); //set left FlyWheel speed

        if (m_gamepad.GetRawButton(DriveStationConstants::triggerLT))
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

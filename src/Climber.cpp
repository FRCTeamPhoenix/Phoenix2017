/*
 * Climber.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: Joshua Calzadillas
 */
#include "Climber.h"

Climber::Climber(SmartTalon& motor, SmartTalon& motor2, Joystick& customBox):
        m_motor(motor),
        m_motor2(motor2),
        m_customBox(customBox)
{
    m_state = OFF;
    m_motor.SetControlMode(CANSpeedController::kPercentVbus);
    m_motor2.SetControlMode(CANSpeedController::kPercentVbus);

}

Climber::~Climber()
{
}

//Gets the current state of the FlyWheels state machine
Climber::STATE Climber::getState(){
    return m_state;
}

//Sets the state when there is a change in the FlyWheels state machine
void Climber::setState(Climber::STATE state)
{
    m_state = state;

}

void Climber::run()
{
    switch (m_state)
    {
        case OFF:
            m_motor.Set(0.0);
            m_motor2.Set(0.0);
            break;

        case ON:
            m_motor.Set((m_customBox.GetRawAxis(DriveStationConstants::potFlywheelSpeed) + 1) / 2);
            m_motor2.Set((m_customBox.GetRawAxis(DriveStationConstants::potFlywheelSpeed) + 1) / 2);
            break;
    }

}

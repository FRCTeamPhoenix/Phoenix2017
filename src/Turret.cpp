/*
 * Turret.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "Turret.h"

Turret::Turret(
        SmartTalon& turretRotatorMotor,
        Joystick& gamepad):
        m_turretRotatorMotor(turretRotatorMotor),
        m_gamepad(gamepad)
{
    m_state = IDLE;
    m_gamepadJoystick = 0;
}

Turret::~Turret()
{
}

void Turret::run()
{
    switch (m_state)
    {

    //Idle state of Turret
    //Changes to Moving when there is joystick movement that is not in the deadzone
    case IDLE:
        m_turretRotatorMotor.goAt(0.0);

        if(gamepadJoystickWithDeadZone() != 0)
        {
            setState(MOVING);
        }
        break;

        //Moving state of Turret
        //Changes to Idle when there is no joystick movement
    case MOVING:
        m_turretRotatorMotor.goAt(gamepadJoystickWithDeadZone());

        if(gamepadJoystickWithDeadZone() == 0)
        {
            setState(IDLE);
        }
        break;
    }
}

//Creates a function for the gamepad joystick with a deadzone
//Has a damping effect because we do not want the turret moving at full speed
float Turret::gamepadJoystickWithDeadZone()
{
    float power = -m_gamepadJoystick;

    if (fabs(power) < 0.05f){
        power = 0;
    }
    return power * RobotConstants::turretDamp;
}

//Gets the current state of the Turret state machine
Turret::STATE Turret::getState()
{
    return m_state;
}

//Sets the state when there is a change in the Turret state machine
void Turret::setState(STATE state)
{
    m_state = state;

}

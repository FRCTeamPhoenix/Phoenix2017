/*
 * Turret.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "Turret.h"

Turret::Turret(
        SmartTalon& turretRotatorMotor,
        Communications& visionComs,
        Joystick& gamepad):

        m_turretRotatorMotor(turretRotatorMotor),
        m_visionComs(visionComs),
        m_gamepad(gamepad)

{
    m_state = HOMING;
    m_gamepadJoystick = 0;
    m_visionTimeStamp = 0;
}

Turret::~Turret()
{
}

void Turret::run()
{
    //Homing State of Turret
    //Returns Turret to right limit.
    if(m_state == HOMING){
        m_turretRotatorMotor.goAt(0.5);//will need to be changed. temp number.
        if(m_turretRotatorMotor.IsFwdLimitSwitchClosed())
        {
            setState(IDLE);
        }
    }
    else{
        switch (m_state)
        {

            //Idle state of Turret
            //Changes to Moving when there is joystick movement that is not in the deadzone
            case IDLE:
                m_turretRotatorMotor.goAt(0.0);

                if(gamepadJoystickWithDeadZone() != 0)
                {
                    setState(TELEOP);
                }
                if(m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                {
                    setState(AUTO);
                }
                break;
                //Moving state of Turret
                //Changes to Idle when there is no joystick movement
            case TELEOP:
                gamepadJoystickWithDeadZone();

                if(m_turretRotatorMotor.IsFwdLimitSwitchClosed())
                {
                    if (gamepadJoystickWithDeadZone() > 0)
                    {
                        m_turretRotatorMotor.goAt(0.0);
                    }
                    else
                    {
                        m_turretRotatorMotor.goAt(gamepadJoystickWithDeadZone());
                    }
                }
                else if (m_turretRotatorMotor.IsRevLimitSwitchClosed())
                {
                    if (gamepadJoystickWithDeadZone() < 0)
                    {
                        m_turretRotatorMotor.goAt(0.0);
                    }
                    else
                    {
                        m_turretRotatorMotor.goAt(gamepadJoystickWithDeadZone());
                    }

                }
                else
                {
                    m_turretRotatorMotor.goAt(gamepadJoystickWithDeadZone());
                }
                if(gamepadJoystickWithDeadZone() == 0)
                {
                    setState(IDLE);
                }
                break;
            case HOMING:
                break;
            case AUTO:
                long long int tempTime = m_visionComs.getAngleTimestamp();

                if (tempTime != m_visionTimeStamp){
                    m_visionTimeStamp = tempTime;

                    autoTarget(m_visionComs.getAngle());
                }
                if(!m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                {
                    setState(IDLE);
                }

                break;
        }
    }
}

void Turret::autoTarget(float degrees){
    m_turretRotatorMotor.goDistance(degreeToTicks(degrees), 0.5);
}

float Turret::degreeToTicks(float angle){
    return angle * RobotConstants::degreesToTicks;
}

//Creates a function for the gamepad joystick with a deadzone
//Has a damping effect because we do not want the turret moving at full speed
float Turret::gamepadJoystickWithDeadZone()
{
    float power = -m_gamepad.GetY();

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

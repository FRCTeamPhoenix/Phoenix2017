/*
 * Turret.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#include "Turret.h"

Turret::Turret(
        SmartTalon& turretRotatorMotor,
        Communications& visionComms,
        Joystick& customBox):

        m_turretRotatorMotor(turretRotatorMotor),
        m_visionComms(visionComms),
        m_customBox(customBox)
        //m_prevAngles(),
        //m_timer()

{
    m_state = HOMING;
    m_gamepadJoystick = 0;
}

Turret::~Turret()
{
}

void Turret::run()
{
    //Communicate our current turret position to the Jetson
    m_visionComms.setNumber(JetsonComms::turretAngle, m_turretRotatorMotor.GetEncPosition() / RobotConstants::degreesToTicks);
    //m_vision.setNumber("turret_velocity", turretRotatorMotor.GetEncVel() / RobotConstants::degreesToTicks);

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
                break;
                //Moving state of Turret
                //Changes to Idle when there is no joystick movement
            case TELEOP:
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
                if(m_turretRotatorMotor.IsFwdLimitSwitchClosed())
                {
                    m_turretRotatorMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_turretRotatorMotor.Set(0.1);
                }
                else
                {
                    setState(IDLE);
                    m_turretRotatorMotor.Set(0.0);
                }
                break;
            case AUTO:
                double degreesGoal = m_visionComms.getNumber(JetsonComms::goalAngle);
                m_turretRotatorMotor.goTo(degreesGoal * RobotConstants::degreesToTicks, RobotConstants::turretSpeed);
                //LOGI << "Goal: " << degreesGoal << "\n";
                break;
        }
    }
}

//Creates a function for the gamepad joystick with a deadzone
//Has a damping effect because we do not want the turret moving at full speed
float Turret::gamepadJoystickWithDeadZone()
{
    float power = -m_customBox.GetRawAxis(2);

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

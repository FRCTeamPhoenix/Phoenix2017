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
        Joystick& gamepad):

        m_turretRotatorMotor(turretRotatorMotor),
        m_visionComms(visionComms),
        m_gamepad(gamepad),
        m_prevAngles(),
        m_timer()

{
    m_state = HOMING;
    m_gamepadJoystick = 0;
    m_visionTimeStamp = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    m_initialUTC = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    m_timer.Start();
}

Turret::~Turret()
{
}

void Turret::run()
{
    m_state = AUTO;//TEMPORARY FOR TESTING
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
                long long int tempTime = m_visionComms.getTimestampFor(JetsonComms::goalId);

                if (tempTime != m_visionTimeStamp){
                    m_visionTimeStamp = (float) (tempTime - m_initialUTC);
                    m_prevAngles.push_back(m_visionComms.getNumber(JetsonComms::goalId));
                    m_prevTimes.push_back(m_visionTimeStamp);
                    autoTarget();
                    m_timer.Reset();

                    if (m_prevAngles.size() > 2)
                    {
                        m_prevAngles.erase(m_prevAngles.begin(), m_prevAngles.begin() + 1);
                        m_prevTimes.erase(m_prevTimes.begin(), m_prevTimes.begin() + 1);
                    }
                }
                if(!m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                {
                    //setState(IDLE);
                }

                break;
        }
    }
}

void Turret::autoTarget()
{
    //If the last timestamp was long ago, clear the vector, as the data is no longer relevant
    if (m_prevAngles.size() > 1)
    {
        float slope = (m_prevAngles[0] - m_prevAngles[1]) / (m_prevTimes[0] - m_prevTimes[1]);
        float predictedAngle = slope * m_timer.Get() + m_prevAngles[1];
        printf("angle:%f\n", predictedAngle);
        LOGI << "angle" << predictedAngle;
        m_turretRotatorMotor.goDistance(degreeToTicks(predictedAngle), 0.5);
        m_visionComms.setNumber("debug", predictedAngle);
    }
    else
    {
        m_turretRotatorMotor.goDistance(degreeToTicks(m_prevAngles[2]), 0.5);
    }
    m_visionComms.setNumber("debug", -1.0);
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

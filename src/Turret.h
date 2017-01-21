/*
 * Turret.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_TURRET_H_
#define SRC_TURRET_H_
#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"

class Turret
{

public:
    enum STATE
    {
        IDLE, //State of the Turret when it is not moving
        HOMING,
        MOVING //State of the Turret when it is moving/aiming
    };
    void run();
    float gamepadJoystickWithDeadZone(); //Creates a deadzone for the gamepad joystick

    STATE getState(); // Gets the current state of Turret
    void setState(STATE state); //Sets the state of Turret
    void autoTarget(float); //Follows the target for the shooter
    float degreeToTicks(float);

    Turret(
            SmartTalon& turretRotatorMotor,
            DigitalInput& leftLimitSwitch,
            DigitalInput& rightLimitSwitch,
            Joystick& gamepad
    );
    virtual ~Turret();

private:
    SmartTalon& m_turretRotatorMotor; //Turret Motor for rotating the turret
    DigitalInput& m_leftLimitSwitch;
    DigitalInput& m_rightLimitSwitch;
    Joystick& m_gamepad; //Turret uses a joystick on the gamepad
    float m_gamepadJoystick; //Variable for the gamepad joystick value that is out putted
    STATE m_state; //State variable for the Turret
};

#endif /* SRC_TURRET_H_ */

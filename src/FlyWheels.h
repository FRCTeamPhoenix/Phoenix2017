/*
 * FlyWheels.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_FLYWHEELS_H_
#define SRC_FLYWHEELS_H_
#include "WPILib.h"
#include "SmartTalon.h"
#include "constants.h"

class FlyWheels
{

public:

    enum STATE
    {
        OFF, //State of the FLywheels when it is off
        ON //State of the Flywheel when it is on
    };

    void run();
    STATE getState(); //Gets the current state of the Flywheels
    void setState(STATE state); //Sets the state of the Flywheels


    FlyWheels(
            SmartTalon& rightFlyWheelMotor, //Smart Talon of the right flywheel
            SmartTalon& leftFlyWheelMotor, // Smart Talon of the left flywheel
            Joystick& gamepad //Uses gamepad for the right trigger and the left trigger
    );
    virtual ~FlyWheels();


private:
    STATE m_state; //State variable for the FlyWheels
    float motorSpeed = 0.5; //Value is subject for change, only for testing purposes
    SmartTalon& m_rightFlyWheelMotor; //Right FlyWheel Motor
    SmartTalon& m_leftFlyWheelMotor; // Left FlyWheel Motor
    Joystick& m_gamepad; //Gamepad

};

#endif /* SRC_FLYWHEELS_H_ */

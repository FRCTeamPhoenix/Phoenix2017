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
#include "ShooterCalibrator.h"
#include "Lidar.h"

class FlyWheels
{

public:

    enum STATE
    {
        OFF, //State of the FLywheels when it is off
        FLATRATE, //Speed based on given number.
        LIDARRATE, //Speed based on lidar Distance
        JOYSTICKRATE, //The position that the joystick is in determines the speed.
    };

    void run();
    STATE getState(); //Gets the current state of the Flywheels
    void setState(STATE state); //Sets the state of the Flywheels


    FlyWheels(
            SmartTalon& lowerFlyWheelMotor, //Smart Talon of the right flywheel
            SmartTalon& leftFlyWheelMotor, // Smart Talon of the left flywheel
            ShooterCalibrator& shooterCalibrator, //Lidar based flywheel speed
            Lidar& lidar,
            Joystick& gamepad //Uses gamepad for the right trigger and the left trigger
    );
    virtual ~FlyWheels();


private:
    STATE m_state; //State variable for the FlyWheels
    SmartTalon& m_lowerFlyWheelMotor; //Right FlyWheel Motor
    SmartTalon&m_topFlyWheelMotor; // Left FlyWheel Motor
    ShooterCalibrator& m_shooterCalibrator;
    Lidar& m_lidar;
    Joystick& m_gamepad; //Gamepad

    void setRightSpeed(double speed);
    void setLeftSpeed(double speed);
    void setBothSpeed(double speed);

};

#endif /* SRC_FLYWHEELS_H_ */

/*
 * Shooter.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_ROBOTCONTROLLER_H_
#define SRC_ROBOTCONTROLLER_H_
#include "WPILib.h"
#include "FlyWheels.h"
#include "Turret.h"
#include "constants.h"
#include "Feeder.h"
#include "Indexer.h"
#include "Gatherer.h"
#include "Climber.h"


class RobotController
{

public:
    /*
       * Robot Teleop Controls:
       * Button A held: Feeder and Flywheels on, flywheels at joystick rate or lidar rate
       * Button B pressed: turret auto on
       * Button X pressed: turret auto off
       * Button Y held: indexer on
       * Button LB held: climber on
       * Button RB held: Gatherer on
       * Gamepad left joystick: turret Control
       */


    enum STATE
    {
        AUTO, //State of the ShooterController when the game is in Autonomous mode
        TELEOP //State of the ShooterController when the game is in Tele Operated mode
    };

    void run();
    void setState(STATE state); //Sets the state of the ShooterController
    STATE getState(); //Gets the current state of the ShooterController

   RobotController
    (
            FlyWheels& flywheel, //Takes in the FlyWheels
            Turret& turret, //Takes in the Turret
            Feeder& feeder,
            Indexer& indexer,
            Joystick& gamepad,
            Climber& climber,
            Gatherer& gatherer

    );
    virtual ~RobotController();
//
private:
    STATE m_state; //State variable for the ShooterController
    FlyWheels& m_flywheels;
    Turret& m_turret;
    Feeder& m_feeder;
    Indexer& m_indexer;
    Joystick& m_gamepad;
    Climber& m_climber;
    Gatherer& m_gatherer;
//    Joystick& m_controlBox;
};

#endif /* SRC_ROBOTCONTROLLER_H_ */

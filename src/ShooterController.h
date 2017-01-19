/*
 * Shooter.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_SHOOTERCONTROLLER_H_
#define SRC_SHOOTERCONTROLLER_H_
#include "WPIlib.h"
#include "FlyWheels.h"
#include "Turret.h"
#include "constants.h"

class ShooterController
{

public:
    enum STATE
    {
        IDLE, //State of the ShooterController when it is not doing anything
        AUTO, //State of the ShooterController when the game is in Autonomous mode
        TELEOP //State of the ShooterController when the game is in Tele Operated mode
    };

    void run();
    void setState(STATE state); //Sets the state of the ShooterController
    STATE getState(); //Gets the current state of the ShooterController

    ShooterController
    (
            FlyWheels& flywheel, //Takes in the FlyWheels
            Turret& turret //Takes in the Turret
    );
    virtual ~ShooterController();

private:
    STATE m_state; //State variable for the ShooterController
    FlyWheels& m_flywheel;
    Turret& m_turret;
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */

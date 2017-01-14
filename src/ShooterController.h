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
	 IDLE,    //Resting
	 AUTO,    //Auto
	 TELEOP   //Teleop
 };

 	 void run();
 	 void setState(STATE state);//Setter
 	 STATE getState();//Getter


	ShooterController
	(
			FlyWheels& flywheel,
			Turret& turret
	);
	virtual ~ShooterController();
private:
	STATE m_state;
	FlyWheels& m_flywheel;
	Turret& m_turret;
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */

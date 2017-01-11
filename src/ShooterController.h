/*
 * Shooter.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_SHOOTERCONTROLLER_H_
#define SRC_SHOOTERCONTROLLER_H_
#include "WPIlib.h"
class ShooterController
{
private:
 Talon* m_rightFlyWheelMotor;
 Talon* m_leftFlyWheelMotor;
 Encoder* m_rightFlyWheelEncoder;
 Encoder* m_leftFlyWheelEncoder;

	 void stop(); //Stop!!
	 void start(); //start da fly wheels
public:
 enum STATE
 {
	 IDLE,    //Resting
	 SPINNING,//Gaining speed
	 LOADING, //loader
	 SHOOTING,//fire in the hole
	 STOP     //EStop
 };

 	 void run();
 	 STATE setState();//Setter
 	 STATE getState();//Getter


	ShooterController(
			Talon* rightFlyWheelMotor,
			Talon* leftFlyWheelMotor,
			Encoder* rightFlyWheelEncoder,
			Encoder* leftFlyWheelEncoder
			);
	virtual ~ShooterController();
};

#endif /* SRC_SHOOTERCONTROLLER_H_ */

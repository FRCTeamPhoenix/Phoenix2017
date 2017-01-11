/*
 * Shooter.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include "WPIlib.h"
class Shooter
{
private:
 Talon* m_rightFlyWheelMotor;
 Talon* m_leftFlyWheelMotor;
 Encoder* m_rightFlyWheelEncoder;
 Encoder* m_leftFlyWheelEncoder;

	 void stop(); //Stop!!
	 void Start(); //start da fly wheels
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


	Shooter();
	virtual ~Shooter();
};

#endif /* SRC_SHOOTER_H_ */

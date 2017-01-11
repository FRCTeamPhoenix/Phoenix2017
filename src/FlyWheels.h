/*
 * FlyWheels.h
 *
 *  Created on: Jan 10, 2017
 *      Author: lukec
 */

#ifndef SRC_FLYWHEELS_H_
#define SRC_FLYWHEELS_H_
#include "WPILib.h"

class FlyWheels
{
private:
SmartTalon& m_rightFlyWheelMotor;
SmartTalon& m_leftFlyWheelMotor;

public:
	FlyWheels();
	virtual ~FlyWheels();
};

#endif /* SRC_FLYWHEELS_H_ */

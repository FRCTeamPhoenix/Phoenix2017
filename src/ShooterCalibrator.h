/*
 * ShooterCalibrator.h
 *
 * Implements interpolation of necessary power to apply to the shooter's flywheels,
 * based on distance from target.
 *
 *  Created on: Jan 12, 2017
 *      Author: Brin Harper
 */

#include "WPILib.h"
#ifndef SRC_SHOOTERCALIBRATOR_H_
#define SRC_SHOOTERCALIBRATOR_H_

class ShooterCalibrator
{

public:

   /* Constructor will eventually be changed to take in a file containing a table of
    * measured distance/power pairings, for use in interpolation. */
   ShooterCalibrator();

   double getFlywheelPower(double distance);

   virtual ~ShooterCalibrator();

private:

};



#endif /* SRC_SHOOTERCALIBRATOR_H_ */

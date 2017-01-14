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

   const static int DP_PAIRS = 4;

   /* Constructor will eventually be changed to take in a file containing a table of
    * measured distance/power pairings, for use in interpolation. */
   ShooterCalibrator();

   double getFlywheelPower(double distance);

   virtual ~ShooterCalibrator();

private:

   // Reference distance/power pairings for calibration
   double refVals[DP_PAIRS][2];

   double interpolateLinear(double distance);

   void sortRefVals(double (&referenceVals)[DP_PAIRS][2]);

   void printRefVals(double (&referenceVals)[DP_PAIRS][2]);

};



#endif /* SRC_SHOOTERCALIBRATOR_H_ */

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
#include "math.h"
#ifndef SRC_SHOOTERCALIBRATOR_H_
#define SRC_SHOOTERCALIBRATOR_H_

class ShooterCalibrator
{

public:

   /* Constructor will eventually be changed to take in a file containing a table of
    * measured distance/power pairings, for use in interpolation. */
   ShooterCalibrator();

   double getFlywheelPower(double distance, double shootingElevation, double height);

   virtual ~ShooterCalibrator();

   // Number of distance/power pairings in table
      const static int DP_PAIRS = 4;

      const static int g = 9.8;

private:

   double interpolateLinear(double distance);

   void sortRefVals(double (&referenceVals)[DP_PAIRS][2]);

   void printRefVals(double (&referenceVals)[DP_PAIRS][2]);

   double getRequiredStartingVelocity(double distance, double shootingElevation, double height);

   double getCurrentSidewaysVelocity();

   double getRequiredFlywheelVelocity(double distance, double shootingElevation, double height);

   double getStationaryDistance(double startingVelocity, double shootingElevation);

   // Reference distance/power pairings for calibration
   double refVals[DP_PAIRS][2];

};



#endif /* SRC_SHOOTERCALIBRATOR_H_ */

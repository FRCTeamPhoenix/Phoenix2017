/*
 * ShooterCalibrator.cpp
 *
 * Implements interpolation of necessary power to apply to the shooter's flywheels,
 * based on distance from target.
 *
 *  Created on: Jan 12, 2017
 *      Author: Brin Harper
 */

#include <ShooterCalibrator.h>

ShooterCalibrator::ShooterCalibrator()
{

   // Populate array of reference distance/power pairs with default values
   // Column 0 holds distance (meters); column 1 holds power (fraction of total possible power)

   referenceVals[0][0] = 4;
   referenceVals[0][1] = 0.1;

   referenceVals[1][0] = 8;
   referenceVals[1][1] = 0.3;

   referenceVals[2][0] = 16;
   referenceVals[2][1] = 0.5;

   referenceVals[3][0] = 25;
   referenceVals[3][1] = 0.8;

}

double ShooterCalibrator::getFlywheelPower(double distance)
{
   return 0;
}

double ShooterCalibrator::interpolateLinear(double distance) {

   // Table indexes of lower and upper bounds on distance
   // (Lower bound will be -1 if the distance is lower than ALL reference values)
   int lowerBound = -1;
   int upperBound = 0;

   for (int i = 0; i <= 3; i++) {
      if (distance >= referenceVals[i][0]) {
         lowerBound = i;
         break;
      }
   }

   upperBound = lowerBound + 1;

   return 0;

}

ShooterCalibrator::~ShooterCalibrator()
{

}

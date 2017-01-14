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

   refVals[0][0] = 4;
   refVals[0][1] = 0.1;

   refVals[1][0] = 8;
   refVals[1][1] = 0.3;

   refVals[2][0] = 16;
   refVals[2][1] = 0.5;

   refVals[3][0] = 25;
   refVals[3][1] = 0.8;

}

double ShooterCalibrator::getFlywheelPower(double distance)
{
   return 0;
}

double ShooterCalibrator::interpolateLinear(double distance) {

   return 0;

}

// Sort reference distance-power value pairs in order of increasing distance
void sortRefVals(double (&referenceVals)[ShooterCalibrator::DP_PAIRS][2])
{

   // Selection sort
   for (int i = 1; i < ShooterCalibrator::DP_PAIRS; i++)
   {
      double currentDistance = referenceVals[i][0];
      double currentPower = referenceVals[i][1];
      int j = i;
      while (j > 0 && referenceVals[j - 1][0] > currentDistance)
      {
         referenceVals[j][0] = referenceVals[j - 1][0];
         referenceVals[j][1] = referenceVals[j - 1][1];
         j--;
      }
      referenceVals[j][0] = currentDistance;
      referenceVals[j][1] = currentPower;
   }

}

// Print array of reference distance-power value pairs to console
void printRefVals(double (&referenceVals)[ShooterCalibrator::DP_PAIRS][2])
{

   for (int x = 0; x < ShooterCalibrator::DP_PAIRS; x++) {
      std::cout << "[";
      for (int y = 0; y < 2; y++) {
         std::cout << referenceVals[x][y] << " ";
      }
      std::cout << "]" << '\n';
   }

}

ShooterCalibrator::~ShooterCalibrator()
{

}

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

// Retrieve and organize reference distance/power values
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

   // Sort reference distance/power pairs in order of increasing distance (selection sort)
   for (int i = 1; i < ShooterCalibrator::DP_PAIRS; i++)
   {
      double currentDistance = refVals[i][0];
      double currentPower = refVals[i][1];
      int j = i;
      while (j > 0 && refVals[j - 1][0] > currentDistance)
      {
         refVals[j][0] = refVals[j - 1][0];
         refVals[j][1] = refVals[j - 1][1];
         j--;
      }
      refVals[j][0] = currentDistance;
      refVals[j][1] = currentPower;
   }


}

double ShooterCalibrator::interpolateLinear(double distance) {

   int lowerBound = -1;
   for (int i = 0; i < ShooterCalibrator::DP_PAIRS; i++) {
      if (distance >= refVals[i][0]) {
         lowerBound = i;
         break;
      }
   }

   // Temporary ~ a [much] better method of extrapolation will be needed
   // If distance is less than the lowest entry's, round up to lowest entry's power
   if (lowerBound == -1) {
      return refVals[0][1];
   }
   // If distance is greater than the highest entry's, round down to highest entry's power
   else if (lowerBound == DP_PAIRS) {
      return refVals[DP_PAIRS - 1][1];
   }

   else {

      // Change in required power (% of total) per unit distance (m)
      double slope = (refVals[lowerBound + 1][1] - refVals[lowerBound][1])
            / (refVals[lowerBound + 1][0] - refVals[lowerBound][0]);

      // Linear interpolation
      return refVals[lowerBound + 1][1] + slope*(distance - refVals[lowerBound][0]);

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

// Required initial velocity to shoot from a given distance, when stationary
// Lookup table will be used to convert velocity to power
double getRequiredStartingVelocity(double distance, double shootingElevation, double height)
{
   return sqrt(distance*distance*ShooterCalibrator::g
         /(cos(shootingElevation)*cos(shootingElevation)*(distance*tan(shootingElevation) - height)));
}

// TODO: Use encoder info to calculate current sideways velocity
double getCurrentSidewaysVelocity()
{
   return 0;
}

double getRequiredFlywheelVelocity(double distance, double shootingElevation, double height)
{
   double vN = getRequiredStartingVelocity(distance, shootingElevation, height);
   double vR = getCurrentSidewaysVelocity();
   return sqrt((vN*vN - vR*vR)/(cos(shootingElevation)*cos(shootingElevation)));
}

double getStationaryDistance(double startingVelocity, double shootingElevation)
{
   return 2*startingVelocity*startingVelocity*cos(shootingElevation)*cos(shootingElevation)/ShooterCalibrator::g;
}

double ShooterCalibrator::getFlywheelPower(double distance, double shootingElevation, double height)
{
   //double v0 = getRequiredFlywheelVelocity(distance, shootingElevation, height);
   //double dx = getStationaryDistance(v0, shootingElevation);
   // Table lookup: required power for dx (interpolation)
   // return required power
   return 0;
}

ShooterCalibrator::~ShooterCalibrator()
{

}

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
#include <math.h>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "DistancePowerPair.h"

#ifndef SRC_SHOOTERCALIBRATOR_H_
#define SRC_SHOOTERCALIBRATOR_H_

using namespace std;
using json=nlohmann::json;

class ShooterCalibrator
{

public:

        ShooterCalibrator();

        // Calculate required flywheel power, given shooting distance
        double getFlywheelPower(double distance);
        // Estimate resultant distance from a given flywheel power
        double getDistance(double power);

        // Number of distance/power pairings in config file
        int getNumPairs();

        void printRefVals();
        ~ShooterCalibrator();


private:

        // Store distance/power pairs (read in from json)
        vector<DistancePowerPair> dpPairs;

        vector<DistancePowerPair> dpPairsLow;
        vector<DistancePowerPair> dpPairsTop;

        double interpolatePowerLinear(double distance);
        double interpolateDistanceLinear(double power);

};



#endif /* SRC_SHOOTERCALIBRATOR_H_ */

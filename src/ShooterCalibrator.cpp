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

    // Create json object containing distance/power pairs
    ifstream points_json;
    points_json.open("/home/lvuser/config/shooterCalibrator.json");
    json points;
    points_json >> points;
    points_json.close();

    // Iterate over points from json file; read and store reference values
    json::iterator jsonItr;
    for (jsonItr = points.begin(); jsonItr != points.end(); jsonItr++)
    {
        dvPairsLow.push_back(DistanceVelocityPair(*jsonItr, false));
        dvPairsTop.push_back(DistanceVelocityPair(*jsonItr, true));
    }

    // Sort reference values
    sortRefVals(dvPairsLow);
    sortRefVals(dvPairsTop);

}

double ShooterCalibrator::interpolateVelocityLinear(double distance, vector<DistanceVelocityPair>& dvPairs) {

    // Lower and upper indices on dpPairs
    int i1 = 0;
    int i2 = 1;
    // Lower and upper bounds on distance (start with first two reference values)
    double d1 = dvPairs[i1].getDistance();
    double d2 = dvPairs[i2].getDistance();

    // Use last two reference values if distance exceeds greatest value
    if (distance >= dvPairs[dvPairs.size() - 1].getDistance())
    {
        i1 = dvPairs.size() - 2;
        d1 = dvPairs[i1].getDistance();
        i2 = i1 + 1;
        d2 = dvPairs[i2].getDistance();
    }
    // Otherwise, if distance isn't below/between the first pair of reference values, choose greater values
    else if (distance >= dvPairs[1].getDistance())
    {
        while (d2 <= distance) {
            i1++;
            d1 = dvPairs[i1].getDistance();
            i2++;
            d2 = dvPairs[i2].getDistance();
        }
    }

    // Lower and upper bounds on power
    double v1 = dvPairs[i1].getVelocity();
    double v2 = dvPairs[i2].getVelocity();

    // Change in power per unit distance
    double m = (v2 - v1)/(d2 - d1);

    // Required power (linear interpolation)
    double vReq = m*(distance - d1) + v1;

    return vReq;

}

double ShooterCalibrator::getTopFlywheelVelocity(double distance) {

    return interpolateVelocityLinear(distance, dvPairsTop);

}

double ShooterCalibrator::getLowFlywheelVelocity(double distance) {

    return interpolateVelocityLinear(distance, dvPairsLow);

}

void ShooterCalibrator::sortRefVals(vector<DistanceVelocityPair>& dvPairs) {

    // Sort reference values
    for (int i = 1; i < (int) dvPairs.size(); i++) {
        double currentDistance = dvPairs[i].getDistance();
        double currentVelocity = dvPairs[i].getVelocity();
        int j = i;
        while (j > 0 && dvPairs[j - 1].getDistance() > currentDistance)
        {
            dvPairs[j].setDistance(dvPairs[j - 1].getDistance());
            dvPairs[j].setVelocity(dvPairs[j - 1].getVelocity());
            j--;
        }
        dvPairs[j].setDistance(currentDistance);
        dvPairs[j].setVelocity(currentVelocity);
    }

}

void ShooterCalibrator::initialize() {



}

ShooterCalibrator::~ShooterCalibrator()
{

}

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

double ShooterCalibrator::interpolateVelocityLinear(double distance, vector<DistanceVelocityPair> dvPairs) {

    // Lower and upper indices on dpPairs
    int i1 = 0;
    int i2 = 1;
    // Lower and upper bounds on distance (start with first two reference values)
    double d1 = dvPairs[i1].getDistance();
    double d2 = dvPairs[i2].getDistance();

    // Use last two reference values if distance exceeds greatest value
    if (distance > dvPairs[dvPairs.size() - 1].getDistance())
    {
        i1 = dvPairs.size() - 2;
        i2 = i1 + 1;
    }
    // Otherwise, if distance isn't below/between the first pair of reference values, choose greater values
    else if (distance > dvPairs[1].getDistance())
    {
        i1++;
        d1 = dvPairs[i1].getDistance();
        i2++;
        d2 = dvPairs[i2].getDistance();
    }

    // Lower and upper bounds on power
    double v1 = dvPairs[i1].getVelocity();
    double v2 = dvPairs[i2].getVelocity();

    // Change in power per unit distance
    double m = (v2 - v1)/(d2 - d1);

    // Required power (linear interpolation)
    double vReq = m*(distance - d1) + v1;

    // Don't shoot with power below 0.1 or above 0.85
    if (vReq < 0.1)
    {
        return 0.1;
    }
    else if (vReq > 0.85)
    {
        return 0.85;
    }
    else
    {
        return vReq;
    }

}

double ShooterCalibrator::interpolateDistanceLinear(double velocity, vector<DistanceVelocityPair> dvPairs) {

    // Lower and upper indices on dpPairs
    int i1 = 0;
    int i2 = 1;
    // Lower and upper bounds on power (start with first two reference values)
    double p1 = dvPairs[i1].getVelocity();
    double p2 = dvPairs[i2].getVelocity();

    // Use last two reference values if power exceeds greatest value
    if (velocity > dvPairs[dvPairs.size() - 1].getVelocity())
    {
        i1 = dvPairs.size() - 2;
        i2 = i1 + 1;
    }
    // Otherwise, if power isn't below/between the first pair of reference values, choose greater values
    else if (velocity > dvPairs[1].getVelocity())
    {
        i1++;
        p1 = dvPairs[i1].getVelocity();
        i2++;
        p2 = dvPairs[i2].getVelocity();
    }

    // Lower and upper bounds on distance
    double d1 = dvPairs[i1].getDistance();
    double d2 = dvPairs[i2].getDistance();

    // Change in power per unit distance
    double m = (d2 - d1)/(p2 - p1);

    // Estimated distance (linear interpolation)
    double distanceEst = m*(velocity - p1) + d1;

    return distanceEst;

}

double ShooterCalibrator::getTopFlywheelVelocity(double distance) {

    return interpolateVelocityLinear(distance, dvPairsTop);

}

double ShooterCalibrator::getLowFlywheelVelocity(double distance) {

    return interpolateVelocityLinear(distance, dvPairsLow);

}

double ShooterCalibrator::getDistance(double power) {

    return interpolateDistanceLinear(power, dvPairsTop);

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

ShooterCalibrator::~ShooterCalibrator()
{

}

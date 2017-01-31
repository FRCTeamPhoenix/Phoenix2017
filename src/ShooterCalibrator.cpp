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
    points_json.open("/home/lvuser/shooterCalibrator.json");
    json points;
    points_json >> points;
    points_json.close();

    // Iterate over points from json file; read and store reference values
    json::iterator jsonItr;
    for (jsonItr = points.begin(); jsonItr != points.end(); jsonItr++)
    {
        dpPairs.push_back(DistancePowerPair(*jsonItr));
    }

    // Sort reference values
    for (int i = 1; i < (int) dpPairs.size(); i++) {
        double currentDistance = dpPairs[i].getDistance();
        double currentPower = dpPairs[i].getPower();
        int j = i;
        while (j > 0 && dpPairs[j - 1].getDistance() > currentDistance)
        {
            dpPairs[j].setDistance(dpPairs[j - 1].getDistance());
            dpPairs[j].setPower(dpPairs[j - 1].getPower());
            j--;
        }
        dpPairs[j].setDistance(currentDistance);
        dpPairs[j].setPower(currentPower);
    }

}

double ShooterCalibrator::interpolateLinear(double distance) {

    // Lower and upper indices on dpPairs
    int i1 = 0;
    int i2 = 1;
    // Lower and upper bounds on distance (start with first two reference values)
    double d1 = dpPairs[i1].getDistance();
    double d2 = dpPairs[i2].getDistance();

    // Use last two reference values if distance exceeds greatest value
    if (distance > dpPairs[dpPairs.size() - 1].getDistance())
    {
        i1 = dpPairs.size() - 2;
        i2 = i1 + 1;
    }
    // Otherwise, if distance isn't below/between the first pair of reference values, choose greater values
    else if (distance > dpPairs[1].getDistance())
    {
        i1++;
        d1 = dpPairs[i1].getDistance();
        i2++;
        d2 = dpPairs[i2].getDistance();
    }

    // Lower and upper bounds on power
    double p1 = dpPairs[i1].getPower();
    double p2 = dpPairs[i2].getPower();

    // Change in power per unit distance
    double m = (p2 - p1)/(d2 - d1);

    // Required power (linear interpolation)
    double powerReq = m*(distance - d1) + p1;

    // Don't shoot with power below 0.1 or above 0.85
    if (powerReq < 0.1)
    {
        return 0.1;
    }
    else if (powerReq > 0.85)
    {
        return 0.85;
    }
    else
    {
        return powerReq;
    }

}

double ShooterCalibrator::getPower(double distance) {

    return interpolateLinear(distance);

}

int ShooterCalibrator::getNumPairs()
{
    return dpPairs.size();
}

// Print stored reference values
void ShooterCalibrator::printRefVals()
{

    vector<DistancePowerPair>::iterator dpItr;
    for (dpItr = dpPairs.begin(); dpItr != dpPairs.end(); dpItr++)
    {
        cout << "(" << dpItr->getDistance() << ", " << dpItr->getPower() << ")" << endl;
    }

}

ShooterCalibrator::~ShooterCalibrator()
{

}

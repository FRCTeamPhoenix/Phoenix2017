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

/*
 * ShooterCalibrator.cpp
 *
 * Implements interpolation of necessary power to apply to the shooter's flywheels,
 * based on distance from target.
 *
 *  Created on: Jan 12, 2017
 *      Author: Brin Harper
 */

#include "ShooterCalibrator.h"

ShooterCalibrator::ShooterCalibrator()
{

    json scJsonDoc;
    json scSchemaDoc;

    try
    {

        if (!valijson::utils::loadDocument("/home/lvuser/schemas/shooterCalibrator.schema", scSchemaDoc))
        {

            cout << "Shooter Calibration Schema Failed Loading" << endl;

            throw std::runtime_error("Failed to load shooter calibrator schema document");

        }

        Schema scSchema;
        SchemaParser parser;
        NlohmannJsonAdapter scSchemaAdapter(scSchemaDoc);
        parser.populateSchema(scSchemaAdapter, scSchema);

        if (!valijson::utils::loadDocument("/home/lvuser/config/shooterCalibrator.json", scJsonDoc))
        {
            cout << "Shooter Calibration Json Failed Loading" << endl;

            throw std::runtime_error("Failed to load shooter calibrator Json document");
        }

        Validator validator;
        NlohmannJsonAdapter scTargetAdapter(scJsonDoc);
        if (!validator.validate(scSchema, scTargetAdapter, NULL))
        {
            cout << "Shooter Calibration Validation Failed" << endl;
            throw std::runtime_error("Shooter Calibration Validation failed");
        }

        else
        {
            cout << "Shooter Calibration Validated" << endl;

            // Iterate over points from json file; read and store reference values
            json::iterator jsonItr;
            for (jsonItr = scJsonDoc.begin(); jsonItr != scJsonDoc.end(); jsonItr++)
            {
                dvPairsLow.push_back(DistanceVelocityPair(*jsonItr, false));
                dvPairsTop.push_back(DistanceVelocityPair(*jsonItr, true));
            }

            // Sort reference values
            sortRefVals(dvPairsLow);
            sortRefVals(dvPairsTop);

        }

    }

    catch (runtime_error runtime) {

        cout << runtime.what() << endl;
        cout << "Default Shooter Calibration Values Loaded";

        dvPairsTop.push_back(DistanceVelocityPair(0, 40000));
        dvPairsLow.push_back(DistanceVelocityPair(0, 3000));

        dvPairsTop.push_back(DistanceVelocityPair(104, 55000));
        dvPairsLow.push_back(DistanceVelocityPair(104, 3000));

        dvPairsTop.push_back(DistanceVelocityPair(144, 59000));
        dvPairsLow.push_back(DistanceVelocityPair(144, 3300));

        dvPairsTop.push_back(DistanceVelocityPair(159, 61000));
        dvPairsLow.push_back(DistanceVelocityPair(159, 3400));

        dvPairsTop.push_back(DistanceVelocityPair(165, 64000));
        dvPairsLow.push_back(DistanceVelocityPair(144, 3400));

        return;

    }

}

// Calculate required flywheel power, given shooting distance
// IMPORTANT: Upper/lower velocity limits must be controlled externally!
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

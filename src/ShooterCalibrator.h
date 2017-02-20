/*
 * ShooterCalibrator.h
 *
 * Implements interpolation of necessary power to apply to the shooter's flywheels,
 * based on distance from target.
 *
 *  Created on: Jan 12, 2017
 *      Author: Brin Harper
 */

#include "DistanceVelocityPair.h"
#include "WPILib.h"
#include <math.h>
#include <iostream>
#include "json.hpp"
#include <fstream>

//Suppresses uint_64 overflow warning from valijson
#pragma GCC diagnostic ignored "-Woverflow"

#include "valijson/adapters/nlohmann_json_adapter.hpp"
#include "valijson/utils/nlohmann_json_utils.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validator.hpp"

#ifndef SRC_SHOOTERCALIBRATOR_H_
#define SRC_SHOOTERCALIBRATOR_H_

using namespace std;
using json=nlohmann::json;
using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::adapters::NlohmannJsonAdapter;

class ShooterCalibrator
{

public:

        ShooterCalibrator();

        // Calculate required flywheel power, given shooting distance
        // IMPORTANT: Upper/lower velocity limits must be controlled externally!
        double getTopFlywheelVelocity(double distance);
        double getLowFlywheelVelocity(double distance);

        void sortRefVals(vector<DistanceVelocityPair>& dvPairs);
        void initialize();

        ~ShooterCalibrator();


private:

        // Store distance/power pairs (read in from json)
        vector<DistanceVelocityPair> dvPairs;

        vector<DistanceVelocityPair> dvPairsLow;
        vector<DistanceVelocityPair> dvPairsTop;

        double interpolateVelocityLinear(double distance, vector<DistanceVelocityPair>& dvPairs);

};



#endif /* SRC_SHOOTERCALIBRATOR_H_ */

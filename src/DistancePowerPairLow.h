/*
 * DistancePowerPairLow.h
 *
 * Stores a measured distance/power pair for the low flywheel (used by ShooterCalibrator)
 *
 *  Created on: Feb 11, 2017
 *      Author: Brin Harper
 */

#include "WPILib.h"
#include <iostream>
#include "json.hpp"
#include <fstream>

#ifndef SRC_DISTANCEPOWERPAIRLOW_H_
#define SRC_DISTANCEPOWERPAIRLOW_H_

using namespace std;
using json=nlohmann::json;

class DistancePowerPairLow
{

    public:
        // Directly pass in distance and power values
        DistancePowerPairLow(double distance, double power);

        // Obtain distance and power from a json point object
        DistancePowerPairLow(json point);

        double getDistance();
        void setDistance(double distance);
        double getPower();
        void setPower(double power);
        virtual ~DistancePowerPairLow();

    private:
        double m_distance;
        double m_power;

};



#endif /* SRC_DISTANCEPOWERPAIRLow_H_ */

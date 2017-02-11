/*
 * DistancePowerPairTop.h
 *
 * Stores a measured distance/power pair for the top flywheel (used by ShooterCalibrator)
 *
 *  Created on: Feb 11, 2017
 *      Author: Brin Harper
 */

#include "WPILib.h"
#include <iostream>
#include "json.hpp"
#include <fstream>

#ifndef SRC_DISTANCEPOWERPAIRTOP_H_
#define SRC_DISTANCEPOWERPAIRTOP_H_

using namespace std;
using json=nlohmann::json;

class DistancePowerPairTop
{

    public:
        // Directly pass in distance and power values
        DistancePowerPairTop(double distance, double power);

        // Obtain distance and power from a json point object
        DistancePowerPairTop(json point);

        double getDistance();
        void setDistance(double distance);
        double getPower();
        void setPower(double power);
        virtual ~DistancePowerPairTop();

    private:
        double m_distance;
        double m_power;

};



#endif /* SRC_DISTANCEPOWERPAIRTOP_H_ */

/*
 * DistancePowerPair.h
 *
 * Stores a measured distance/power pair (used by ShooterCalibrator)
 *
 *  Created on: Jan 28, 2017
 *      Author: Brin Harper
 */

#include "WPILib.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
#ifndef SRC_DISTANCEPOWERPAIR_H_
#define SRC_DISTANCEPOWERPAIR_H_

using namespace std;
using json=nlohmann::json;

class DistancePowerPair
{

    public:
        // Directly pass in distance and power values
        DistancePowerPair(double distance, double power);

        // Obtain distance and power from a json point object
        DistancePowerPair(json point);

        double getDistance();
        void setDistance(double distance);
        double getPower();
        void setPower(double power);
        virtual ~DistancePowerPair();

    private:
        double m_distance;
        double m_power;

};



#endif /* SRC_DISTANCEPOWERPAIR_H_ */

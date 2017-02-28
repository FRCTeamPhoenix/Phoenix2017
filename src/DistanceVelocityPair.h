/*
 * DistancePowerPair.h
 *
 * Stores a measured distance/power pair (used by ShooterCalibrator)
 *
 *  Created on: Jan 28, 2017
 *      Author: Brin Harper
 */

#ifndef SRC_DISTANCEVELOCITYPAIR_H_
#define SRC_DISTANCEVELOCITYPAIR_H_


#include "WPILib.h"
#include <iostream>
#include "json.hpp"
#include <fstream>

using namespace std;
using json=nlohmann::json;

class DistanceVelocityPair
{

    public:
        // Directly pass in distance and power values
        DistanceVelocityPair(double distance, double velocity);

        // Obtain distance and power from a json point object
        DistanceVelocityPair(json point, bool isTop);

        double getDistance();
        void setDistance(double distance);
        double getVelocity();
        void setVelocity(double velocity);
        virtual ~DistanceVelocityPair();

    private:
        double m_distance;
        double m_velocity;

};



#endif /* SRC_DISTANCEVELOCITYPAIR_H_ */

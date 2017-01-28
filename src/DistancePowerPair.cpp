/*
 * DistancePowerPair.cpp
 *
 * Stores a distance/power pair in an organized manner.
 *
 *  Created on: Jan 28, 2017
 *      Author: Brin Harper
 */

#include <DistancePowerPair.h>

//        DistancePowerPair(double d, double p);
//        DistancePowerPair(json points);
//        double getDistance();
//        void setDistance(double d);
//        double getPower();
//        void setPower(double p);
//        virtual ~DistancePowerPair();


// Constructor that takes a distance value and a power value
//DistancePowerPair::DistancePowerPair(double distance, double power) {
//
//    m_distance = distance;
//    m_power = power;
//
//}

// Constructor that takes a json object (implement format checking)
//DistancePowerPair::DistancePowerPair(json point) {
//
//    m_distance = point["distance"];
//    m_power = point["power"];
//
//}

double DistancePowerPair::getDistance() {
    return m_distance;
}

void DistancePowerPair::setDistance(double distance) {
    m_distance = distance;
}

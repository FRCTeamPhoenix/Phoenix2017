/*
 * DistancePowerPair.cpp
 *
 * Stores a measured distance/power pair (used by ShooterCalibrator)
 *
 *  Created on: Jan 28, 2017
 *      Author: Brin Harper
 */

#include <DistancePowerPair.h>

// Directly pass in distance and power values
DistancePowerPair::DistancePowerPair(double distance, double power)
{

    m_distance = distance;
    m_power = power;

}

// Obtain distance and power from a json point object
DistancePowerPair::DistancePowerPair(json point)
{

    m_distance = point["distance"];
    m_power = point["power"];

}

double DistancePowerPair::getDistance()
{
    return m_distance;
}

void DistancePowerPair::setDistance(double distance)
{
    m_distance = distance;
}

double DistancePowerPair::getPower()
{
    return m_power;
}

void DistancePowerPair::setPower(double power)
{
    m_power = power;
}

DistancePowerPair::~DistancePowerPair()
{

}

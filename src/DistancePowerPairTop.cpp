/*
 * DistancePowerPairTop.cpp
 *
 * Stores a measured distance/power pair for the top flywheel (used by ShooterCalibrator)
 *
 *  Created on: Feb 11, 2017
 *      Author: Brin Harper
 */

#include <DistancePowerPairTop.h>

// Directly pass in distance and power values
DistancePowerPairTop::DistancePowerPairTop(double distance, double power)
{

    m_distance = distance;
    m_power = power;

}

// Obtain distance and power from a json point object
DistancePowerPairTop::DistancePowerPairTop(json point)
{

    m_distance = point["distance"];
    m_power = point["powerTop"];

}

double DistancePowerPairTop::getDistance()
{
    return m_distance;
}

void DistancePowerPairTop::setDistance(double distance)
{
    m_distance = distance;
}

double DistancePowerPairTop::getPower()
{
    return m_power;
}

void DistancePowerPairTop::setPower(double power)
{
    m_power = power;
}

DistancePowerPairTop::~DistancePowerPairTop()
{

}

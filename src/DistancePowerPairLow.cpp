/*
 * DistancePowerPairLow.cpp
 *
 * Stores a measured distance/power pair for the low flywheel (used by ShooterCalibrator)
 *
 *  Created on: Feb 11, 2017
 *      Author: Brin Harper
 */

#include <DistancePowerPairLow.h>

// Directly pass in distance and power values
DistancePowerPairLow::DistancePowerPairLow(double distance, double power)
{

    m_distance = distance;
    m_power = power;

}

// Obtain distance and power from a json point object
DistancePowerPairLow::DistancePowerPairLow(json point)
{

    m_distance = point["distance"];
    m_power = point["powerLow"];

}

double DistancePowerPairLow::getDistance()
{
    return m_distance;
}

void DistancePowerPairLow::setDistance(double distance)
{
    m_distance = distance;
}

double DistancePowerPairLow::getPower()
{
    return m_power;
}

void DistancePowerPairLow::setPower(double power)
{
    m_power = power;
}

DistancePowerPairLow::~DistancePowerPairLow()
{

}

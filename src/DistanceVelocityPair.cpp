/*
 * DistancePowerPair.cpp
 *
 * Stores a measured distance/power pair (used by ShooterCalibrator)
 *
 *  Created on: Jan 28, 2017
 *      Author: Brin Harper
 */

#include "DistanceVelocityPair.h"

// Directly pass in distance and power values
DistanceVelocityPair::DistanceVelocityPair(double distance, double velocity)
{

    m_distance = distance;
    m_velocity = velocity;

}

// Obtain distance and power from a json point object
DistanceVelocityPair::DistanceVelocityPair(json point, bool isTop)
{

    m_distance = point["distance"];

    if (isTop)
    {
        m_velocity = point["velocityTop"];
    }
    else
    {
        m_velocity = point["velocityLow"];
    }

}

double DistanceVelocityPair::getDistance()
{
    return m_distance;
}

void DistanceVelocityPair::setDistance(double distance)
{
    m_distance = distance;
}

double DistanceVelocityPair::getVelocity()
{
    return m_velocity;
}

void DistanceVelocityPair::setVelocity(double power)
{
    m_velocity = power;
}

DistanceVelocityPair::~DistanceVelocityPair()
{

}

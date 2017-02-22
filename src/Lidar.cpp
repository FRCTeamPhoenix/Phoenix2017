/*
 * Lidar.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#include "Lidar.h"

Lidar::Lidar(uint32_t triggerPin, uint32_t monitorPin, int mode):
        m_mode(mode),
        m_distance(0),
        m_fastAverage(0),
        m_slowAverage(0),
        m_status(0),
        m_monitorPin(monitorPin),
        m_triggerPin(triggerPin),
        m_counter(0)
{
    // TODO Auto-generated constructor stub
    m_I2C = new I2C(I2C::kOnboard, LIDARLite_ADDRESS);
    m_monitorPin.SetSemiPeriodMode(true);
    m_triggerPin.Set(0);
}

int Lidar::getStatus() {
    return (int)m_status;
}

double Lidar::getAverage() {
   double average = 0;
    for(int i=0; i<10; i++)
       average += (m_distances[i] / 10);
    return average;
}

double Lidar::getDistance() {
    return m_distance;
}

double Lidar::getFastAverage() {
    return m_fastAverage;
}

double Lidar::getSlowAverage() {
    return m_slowAverage;
}

void Lidar::run() {
    //I2C code
    double distance;
    byte distanceArray[2];
    m_I2C->Write(0x00, 0x04);
    Wait(0.05);
    byte distanceRegister_1st[1];
    distanceRegister_1st[0] = 0x8f;
    //Read and Write don't work, use WriteBulk and ReadOnly whenever you
    //use I2C
    m_I2C->WriteBulk(distanceRegister_1st, 0x01);
    m_I2C->ReadOnly(2, distanceArray);
    distance = ((distanceArray[0] << 8) + distanceArray[1]) / 2.54;

    if(distance > RobotConstants::lidarMaxReading) return;

    m_distance = distance;

    double average = 0;
    for(int i=0; i<10; i++)
       average += (m_distances[i] / 10);

    if(abs(average - distance) < RobotConstants::lidarValueTolerance)
    {
       m_counter = (1 + m_counter) % 10;
       m_distances[m_counter] = distance;
    }

    double fast = 5.0;
    m_fastAverage = (fast * m_fastAverage + m_distance) / (fast + 1.0);
    double slow = 25.0;
    m_slowAverage = (slow * m_slowAverage + m_distance) / (slow + 1.0);
}

Lidar::~Lidar()
{
    delete m_I2C;
}


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
m_triggerPin(triggerPin)
{
    // TODO Auto-generated constructor stub
    m_I2C = new I2C(I2C::kOnboard, LIDARLite_ADDRESS);
    m_monitorPin.SetSemiPeriodMode(true);
    m_triggerPin.Set(0);
}

int Lidar::getStatus() {
    return (int)m_status;
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
byte distanceArray[2];
//   byte otherArray[1];
//   otherArray[0] = 0x04;
//   while(m_I2C->WriteBulk(otherArray, 1));
   m_I2C->Write(0x00, 0x04);
   Wait(0.05);
   byte distanceRegister_1st[1];
   distanceRegister_1st[0] = 0x8f;
   //Read and Write don't work, use WriteBulk and ReadOnly whenever you
   //use I2C
   m_I2C->WriteBulk(distanceRegister_1st, 0x01);
   m_I2C->ReadOnly(2, distanceArray);
   m_distance = (distanceArray[0] << 8) + distanceArray[1];
   m_distance /= 2.54;

//   byte distanceArray[2];
//   m_I2C->Write(0x00, 0x04);
//   Wait(0.04);
//   m_I2C->Read(0x8f, 2, distanceArray);
//   Wait(0.05);
//   m_distance = ((distanceArray[0] << 8) + distanceArray[1]) / 2.54;

   double fast = 5.0;
   m_fastAverage = (fast * m_fastAverage + m_distance) / (fast + 1.0);
   double slow = 25.0;
   m_slowAverage = (slow * m_slowAverage + m_distance) / (slow + 1.0);
}

Lidar::~Lidar()
{
    delete m_I2C;
}

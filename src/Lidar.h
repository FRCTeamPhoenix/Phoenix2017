/*
 * Lidar.h
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

#define MODE_I2C 0
#define MODE_PWM 1
#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x03          // Value to initiate ranging.
#define    HighByte            0x18          // Distance measurement high byte
#define    LowByte             0x19          // Distance measurement low byte


typedef unsigned char byte;

#include <cstdint>
#include "WPILib.h"
#include <sstream>

class Lidar
{
    int m_mode;

    double m_distance;

    double m_fastAverage;
    double m_slowAverage;

    byte m_status;

    I2C *m_I2C;

    Counter m_monitorPin;

    DigitalOutput m_triggerPin;

    public:
        // Make sure to pass in 0 to mode
        Lidar(uint32_t triggerPin, uint32_t monitorPin, int mode);
        void run();
        double getDistance();
        double getFastAverage();
        double getSlowAverage();
        virtual ~Lidar();
        int getStatus();
};

#endif /* SRC_LIDAR_H_ */

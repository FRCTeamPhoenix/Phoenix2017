//
// Created by William Gebhardt on 1/21/17.
//

#ifndef PHOENIX2017_HEADINGCONTROL_H
#define PHOENIX2017_HEADINGCONTROL_H

#include "WPILib.h"
#include "ADIS16448_IMU.h"

class HeadingControl : public 
{
public:
    enum GyroAxes {
        x,
        y,
        z
    };

    HeadingControl(GyroAxes axis, bool invertDirection)


private:
    ADIS16448_IMU m_gyro;
    bool m_invertDirection;

};


#endif //PHOENIX2017_HEADINGCONTROL_H

//
// Created by William Gebhardt on 1/21/17.
//

#ifndef PHOENIX2017_HEADINGCONTROL_H
#define PHOENIX2017_HEADINGCONTROL_H

#include "WPILib.h"
#include "ADIS16448_IMU.h"

class HeadingControl : public PIDSource, public PIDOutput
{
public:
    enum GyroAxes {
        x,
        y,
        z
    };

    HeadingControl(ADIS16448_IMU& gyro, GyroAxes axis, bool invertDirection);

    double getOutput();
    void setGoal(double goal);
    void keepAt();
    void changeAngle(double change);

private:

    double PIDGet();
    void PIDWrite(double output);


    ADIS16448_IMU& m_gyro;
    GyroAxes m_axisOfInterest;
    bool m_invertDirection;
    double m_currentOutput;
    PIDController m_gyroController;


};


#endif //PHOENIX2017_HEADINGCONTROL_H

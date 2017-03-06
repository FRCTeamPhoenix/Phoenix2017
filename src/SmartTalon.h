//
// Created by William Gebhardt on 10/27/16.
//
#ifndef INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H
#define INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H

#include <fstream>
#include <iostream>
#include "WPILib.h"
#include "PIDGains.h"
#include "CANTalon.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json;
class SmartTalon : public CANTalon
{
public:
    SmartTalon(int deviceNumber, json config, FeedbackDevice device);

    void goTo(double position, double speed);
    void goAt(double speed);
    void goAtVelocity(int velocity);
    void goDistance(double distance, double speed);

    double getGoal();

    /*
     * DO NOT CALL IN ANY CASE WHERE YOU NEED ROBOT CONTROL
     * TAKES CONTROL OF SYSTEM AND DOES NOT RETURN IT TILL DONE
     */
    void tunePosition(double pInit, double tuneDistance, double F);

    void tuneRate(double pInit, double goalRate, int IZone, double F);
    string testStr(double power = 0.1, double timeout = 0.5);
    int test(double power = 0.1, double timeout = 0.5);


    double getMaxForwardSpeed();
    double getMaxReverseSpeed();

private:

    void switchToGain(PIDGains gains);
    double m_goal;

    double m_maxForwardSpeed;
    double m_maxReverseSpeed;

    Timer m_tuneTimer;

    bool m_inverted;

    CANSpeedController::ControlMode m_mode;

    PIDGains m_distanceGains;
    PIDGains m_speedGains;


};


#endif //INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H


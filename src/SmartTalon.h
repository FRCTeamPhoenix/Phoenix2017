//
// Created by William Gebhardt on 10/27/16.
//
#ifndef INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H
#define INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H

#include <fstream>
#include "WPILib.h"
#include "PIDGains.h"
#include "CANTalon.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json;
class SmartTalon : public CANTalon
{
public:
    SmartTalon(int deviceNumber);

    void goTo(double position, double speed);
    void goAt(double speed);
    void goDistance(double distance, double speed);

    double getGoal();

    /*
     * DO NOT CALL IN ANY CASE WHERE YOU NEED ROBOT CONTROL
     * TAKES CONTROL OF SYSTEM AND DOES NOT RETURN IT TILL DONE
     */
    void tunePosition(double pInit, double tuneDistance, double F);

    void tuneRate(double pInit, double goalRate, int IZone, double F);

private:

    void switchToGain(PIDGains gains);
    double m_goal;

    double m_maxForwardSpeed;
    double m_maxReverseSpeed;

    Timer m_tuneTimer;

    PIDGains m_distanceGains;
    PIDGains m_speedGains;


};


#endif //INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H

//
// Created by William Gebhardt on 1/10/17.
//

#ifndef PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H
#define PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

#include "SmartTalon.h"
#include "WPILib.h"

class relativeMecanumDrivetrain
{

/*
 * Front Right  : FR
 * Front Left   : FL
 * Back Right   : BR
 * Back Left    : BL
 */

/*
 * X-axis:
 *  Front Left
 *  Back Right
 *
 * Y-axis:
 *  Front Right
 *  Back Left
 */

/*
 * All angles are passed in in degrees
 */

public:
    relativeMecanumDrivetrain(SmartTalon& FRTalon, SmartTalon& FLTalon, SmartTalon& BRTalon, SmartTalon& BLTalon);

    void moveDistance(double distance, double angle, double speed);
    void moveAt(double speed, double angle);
    void rotate(double angle, double speed);
    void moveRelative(double FB, double LR, double rotation);
    void stop();



private:

    double getXComponent(double magnitude, double angle);
    double getYComponent(double magnitude, double angle);

    RobotDrive m_driveTrain;

    SmartTalon& m_FRTalon;
    SmartTalon& m_FLTalon;
    SmartTalon& m_BRTalon;
    SmartTalon& m_BLTalon;

};


#endif //PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

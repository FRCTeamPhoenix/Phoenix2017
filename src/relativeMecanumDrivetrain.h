//
// Created by William Gebhardt on 1/10/17.
//

#ifndef PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H
#define PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

#include "SmartTalon.h"
#include "WPILib.h"

class relativeMecanumDrivetrain : public PIDOutput, public PIDSource
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
    relativeMecanumDrivetrain(SmartTalon& FRTalon, SmartTalon& FLTalon, SmartTalon& BRTalon, SmartTalon& BLTalon, json taloncfg);

    void moveDistance(double distance, double angle, double speed);
    void moveAt(double speed, double angle);
    void rotate(double angle, double speed);
    void moveRelative(double FB, double LR, double rotation);
    void stop();

    void PIDWrite(double output);
    double PIDGet();

    void SetPIDSourceType(PIDSourceType pidSource);

    double getAvgError();

    CANSpeedController::ControlMode m_mode;

    PIDController* m_distanceController;

private:


    double m_goalX;
    double m_goalY;
    double m_goalGyro;
    double m_maxSpeed;

    double getXComponent(double magnitude, double angle);
    double getYComponent(double magnitude, double angle);



    SmartTalon& m_FRTalon;
    SmartTalon& m_FLTalon;
    SmartTalon& m_BRTalon;
    SmartTalon& m_BLTalon;

    RobotDrive m_driveTrain;

};


#endif //PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

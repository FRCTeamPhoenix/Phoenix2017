//
// Created by William Gebhardt on 1/10/17.
//

#ifndef PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H
#define PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

#include "SmartTalon.h"
#include "HeadingControl.h"
#include "ADIS16448_IMU.h"
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
    relativeMecanumDrivetrain(SmartTalon& FRTalon, SmartTalon& FLTalon, SmartTalon& BRTalon, SmartTalon& BLTalon, ADIS16448_IMU& gyro, HeadingControl::GyroAxes axis);

    void moveDistance(double distance, double angle, double speed, double rotation = 0);
    void moveAt(double speed, double angle);
    void rotate(double angle, double speed);
    void moveRelative(double FB, double LR, double rotation, double front);
    void moveRelativeVoltage(double FB, double LR, double rotation);
    void moveTankStyle(double left, double right, double strafe_power);

    void stop();

    void PIDWrite(double output);
    double PIDGet();

    bool doneMove(double tolerancePercentage);
    bool doneMoveAbsolute(double distanceInches);

    void SetPIDSourceType(PIDSourceType pidSource);

    bool doneMove();


    CANSpeedController::ControlMode m_mode;


private:

    HeadingControl m_headingControl;
    SmartTalon& m_FRTalon;
    SmartTalon& m_FLTalon;
    SmartTalon& m_BRTalon;
    SmartTalon& m_BLTalon;
    PIDController m_distanceController;


    double m_distanceOutput;

    double m_gyroSensitivity;

    double m_goalX;
    double m_goalY;
    double m_goalGyro;
    double m_maxSpeed;

    double m_distance;
    double m_goalDistance;

    bool m_isDistanceMove;


    int m_FRenc;
    int m_FLenc;
    int m_BRenc;
    int m_BLenc;

    double getXComponent(double magnitude, double angle);
    double getYComponent(double magnitude, double angle);

    double getDistance();





//    RobotDrive m_driveTrain;

};


#endif //PHOENIX2017_RELATIVEMECANUMDRIVETRAIN_H

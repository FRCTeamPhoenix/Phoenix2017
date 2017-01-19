//
// Created by William Gebhardt on 1/10/17.
//

#include "relativeMecanumDrivetrain.h"
#include <math.h>


relativeMecanumDrivetrain::relativeMecanumDrivetrain (SmartTalon &FRTalon,
                                                      SmartTalon &FLTalon,
                                                      SmartTalon &BRTalon,
                                                      SmartTalon &BLTalon):

    m_FRTalon(FRTalon),
    m_FLTalon(FLTalon),
    m_BRTalon(BRTalon),
    m_BLTalon(BLTalon),
    m_driveTrain(FLTalon, BLTalon, FRTalon, BLTalon)
{
}


void relativeMecanumDrivetrain::stop ()
{
    m_FRTalon.StopMotor ();
    m_FLTalon.StopMotor ();
    m_BRTalon.StopMotor ();
    m_BLTalon.StopMotor ();
}

double relativeMecanumDrivetrain::getXComponent (double magnitude, double angle)
{
    angle += 45;
    angle *= (M_PI / 180);

    return magnitude / cos(angle);
}

double relativeMecanumDrivetrain::getYComponent (double magnitude, double angle)
{
    angle += 45;
    angle *= (M_PI / 180);

    return magnitude / sin(angle);
}

void relativeMecanumDrivetrain::rotate (double angle, double speed)
{
    double rotation = angle * 23;
    m_FLTalon.goDistance (rotation, speed);
    m_BRTalon.goDistance (-rotation, speed);

    m_FRTalon.goDistance (-rotation, speed);
    m_BLTalon.goDistance (rotation, speed);

}

void relativeMecanumDrivetrain::moveDistance (double distance, double angle, double speed)
{
    double distanceX = getXComponent(distance, angle);
    double distanceY = getYComponent(distance, angle);

    m_BLTalon.goDistance (distanceY, speed);

    m_FLTalon.goDistance (distanceX, speed);
    m_BRTalon.goDistance (distanceX, speed);

    m_FRTalon.goDistance (distanceY, speed);
}

void relativeMecanumDrivetrain::moveAt (double speed, double angle)
{
    double speedX = getXComponent(speed, angle);
    double speedY = getYComponent(speed, angle);

    m_FLTalon.goAt (speedX);
    m_BRTalon.goAt (speedX);

    m_FRTalon.goAt (speedY);
    m_BLTalon.goAt (speedY);
}

void relativeMecanumDrivetrain::moveRelative (double FB, double LR, double rotation)
{
    double x = cos(M_PI_4) * FB + cos(-M_PI_4) * LR;
    double y = sin(M_PI_4) * FB + sin(-M_PI_4) * LR;

    x = x > 1   ?   1   : x;
    x = x < -1  ?  -1   : x;

    y = y > 1   ?   1   : y;
    y = y < -1  ?  -1   : y;




    m_FLTalon.goAt (x + rotation);
    m_BRTalon.goAt (x - rotation);


    m_FRTalon.goAt (y - rotation);
    m_BLTalon.goAt (y + rotation);

}

double relativeMecanumDrivetrain::getAvgError ()
{
    int FL_error = m_FLTalon.GetClosedLoopError ();
    int BR_error = m_BRTalon.GetClosedLoopError ();
    int FR_error = m_FRTalon.GetClosedLoopError ();
    int BL_error = m_BLTalon.GetClosedLoopError ();

    return (FL_error + BR_error + FR_error + BL_error) / 4;

}


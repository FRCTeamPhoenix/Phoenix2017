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
    m_BLTalon(BLTalon)
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
    angle -= 45;
    angle *= (M_PI / 180);

    return magnitude * cos(angle);
}

double relativeMecanumDrivetrain::getYComponent (double magnitude, double angle)
{
    angle -= 45;
    angle *= (M_PI / 180);

    return magnitude * sin(angle);
}


void relativeMecanumDrivetrain::moveDistance (double distance, double angle)
{
    double distanceX = getXComponent(distance, angle);
    double distanceY = getYComponent(distance, angle);

    m_FLTalon.goDistance (distanceX);
    m_BRTalon.goDistance (distanceX);

    m_FRTalon.goDistance (distanceY);
    m_BLTalon.goDistance (distanceY);
}

void relativeMecanumDrivetrain::moveAt (double speed, double angle)
{
    double speedX = getXComponent(speed, angle);
    double speedY = getYComponent(speed, angle);

    m_FLTalon.goDistance (speedX);
    m_BRTalon.goDistance (speedX);

    m_FRTalon.goDistance (speedY);
    m_BLTalon.goDistance (speedY);
}

void relativeMecanumDrivetrain::moveRelative (double FB, double LR)
{
    double x = cos(M_PI_4) * FB + cos(-M_PI_4) * LR;
    double y = sin(M_PI_4) * FB + sin(-M_PI_4) * LR;

    x = x > 1   ?   1   : x;
    x = x < -1  ?  -1   : x;

    y = y > 1   ?   1   : y;
    y = y < -1  ?  -1   : y;

    m_FLTalon.goAt (x);
    m_BRTalon.goAt (x);


    m_FRTalon.goAt (y);
    m_BLTalon.goAt (y);

}


//
// Created by William Gebhardt on 1/10/17.
//

#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include <math.h>


relativeMecanumDrivetrain::relativeMecanumDrivetrain (SmartTalon &FRTalon,
                                                      SmartTalon &FLTalon,
                                                      SmartTalon &BRTalon,
                                                      SmartTalon &BLTalon,
                                                      ADIS16448_IMU &gyro,
                                                      HeadingControl::GyroAxes axis):

    m_headingControl(gyro, axis, true),
    m_FRTalon(FRTalon),
    m_FLTalon(FLTalon),
    m_BRTalon(BRTalon),
    m_BLTalon(BLTalon),
//    m_driveTrain(FLTalon, BLTalon, FRTalon, BLTalon),
    m_distanceController(0.0002, 0, 0.0008, this, this)
//    m_distanceController(SmartDashboard::GetNumber("DB/Slider 0", 0.0),
//                         SmartDashboard::GetNumber("DB/Slider 1", 0.0),
//                         SmartDashboard::GetNumber("DB/Slider 2", 0.0),
//                         SmartDashboard::GetNumber("DB/Slider 3", 0.0),
//                         this, this)
{
    m_gyroSensitivity = 1;
    m_goalX = 0;
    m_goalY = 0;
    m_goalGyro = 0;
    m_maxSpeed = 0;

    m_FRenc = 0;
    m_FLenc = 0;
    m_BRenc = 0;
    m_BLenc = 0;

    m_isDistanceMove = false;

    m_mode = CANSpeedController::ControlMode::kSpeed;

    m_distanceController.Enable();
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
    double new_angle = angle * (M_PI / 180);

    double xComponent = cos(M_PI_4 - new_angle);
    if(0.05 > fabs(xComponent))
    {
        return 0;
    }
    return magnitude * xComponent;
}

double relativeMecanumDrivetrain::getYComponent (double magnitude, double angle)
{
    double new_angle = angle * (M_PI / 180);

    double yComponent = sin(M_PI_4 - new_angle);
    if(0.05 > fabs(yComponent))
    {
        return 0;
    }
    return magnitude * yComponent;
}

void relativeMecanumDrivetrain::rotate (double angle, double speed)
{
//    double rotation = angle * 23;
//    m_FLTalon.goDistance (rotation, speed);
//    m_BRTalon.goDistance (-rotation, speed);
//
//    m_FRTalon.goDistance (-rotation, speed);
//    m_BLTalon.goDistance (rotation, speed);

}

void relativeMecanumDrivetrain::moveDistance (double distance, double angle, double speed, double rotation)
{
    m_mode = CANSpeedController::ControlMode::kPosition;

    if(fabs(distance) <= 0.05){
        m_isDistanceMove = false;
    }
    else{
        m_isDistanceMove = true;
    }

    double distanceX = getXComponent(distance, angle);
    double distanceY = getYComponent(distance, angle);


    std::stringstream gX;
    gX << "Goal X: " << distanceX;
    SmartDashboard::PutString("DB/String 0", gX.str());

    std::stringstream gY;
    gY << "Goal Y: " << distanceY;
    SmartDashboard::PutString("DB/String 1", gY.str());

    m_maxSpeed = fabs(speed);
    m_goalX = distanceX;
    m_goalY = distanceY;
    m_goalDistance = distance;

//    m_headingControl.keepAt ();
    m_headingControl.changeAngle (rotation);

    m_FRenc = m_FRTalon.GetEncPosition ();
    m_FLenc = m_FLTalon.GetEncPosition ();
    m_BRenc = m_BRTalon.GetEncPosition ();
    m_BLenc = m_BLTalon.GetEncPosition ();

    m_distanceController.SetSetpoint (distance);

//    m_distanceController.SetSetpoint (sqrt((distanceX * distanceX) + (distanceY * distanceY)));

//    std::stringstream sP;
//    sP << "SetPoint: " << m_distanceController.GetSetpoint ();
//    SmartDashboard::PutString("DB/String 5", sP.str());
}

void relativeMecanumDrivetrain::moveAt (double speed, double angle)
{
    m_mode = CANSpeedController::ControlMode::kSpeed;

    double speedX = getXComponent(speed, angle);
    double speedY = getYComponent(speed, angle);

    m_FLTalon.goAt (speedX);
    m_BRTalon.goAt (speedX);

    m_FRTalon.goAt (speedY);
    m_BLTalon.goAt (speedY);
}

void relativeMecanumDrivetrain::moveRelativeVoltage (double FB, double LR, double rotation)
{
    m_mode = CANSpeedController::ControlMode::kVoltage;

    double x = cos(M_PI_4) * FB + cos(-M_PI_4) * LR;
    double y = sin(M_PI_4) * FB + sin(-M_PI_4) * LR;

    x = x > 1   ?   1   : x;
    x = x < -1  ?  -1   : x;

    y = y > 1   ?   1   : y;
    y = y < -1  ?  -1   : y;

    stringstream ss;
    ss << y;
    SmartDashboard::PutString("DB/String 7", ss.str());

    stringstream ss2;
    ss2 << x;
    SmartDashboard::PutString("DB/String 8", ss.str());
    m_FLTalon.goVoltage (x + rotation);
    m_BRTalon.goVoltage (x - rotation);

    m_FRTalon.goVoltage (y - rotation);
    m_BLTalon.goVoltage (y + rotation);
}

void relativeMecanumDrivetrain::moveTankStyle(double left, double right, double strafe_power)
{
    m_mode = CANSpeedController::ControlMode::kSpeed;

    double FL_power = left + strafe_power;
    double BL_power = left - strafe_power;

    double FR_power = right - strafe_power;
    double BR_power = right + strafe_power;

    m_FLTalon.goAt (FL_power);
    m_BLTalon.goAt (BL_power);

    m_FRTalon.goAt (FR_power);
    m_BRTalon.goAt (BR_power);


}
void relativeMecanumDrivetrain::moveTankStyleVoltage(double left, double right, double strafe_power)
{
    m_mode = CANSpeedController::ControlMode::kVoltage;

    double FL_power = left + strafe_power;
    double BL_power = left - strafe_power;

    double FR_power = right - strafe_power;
    double BR_power = right + strafe_power;

    m_FLTalon.goVoltage (FL_power);
    m_BLTalon.goVoltage (BL_power);

    m_FRTalon.goVoltage (FR_power);
    m_BRTalon.goVoltage (BR_power);


}
void relativeMecanumDrivetrain::moveRelative (double FB, double LR, double rotation, double front)
{
    m_mode = CANSpeedController::ControlMode::kSpeed;

    front *= (M_PI / 180);

    double x = cos(M_PI_4 - front) * FB + sin(M_PI_4 - front) * LR;
    double y = cos(M_PI_4 + front) * FB + sin(-M_PI_4 - front) * LR;

    x *= sqrt(2);
    y *= sqrt(2);

    x = x > 1   ?   1   : x;
    x = x < -1  ?  -1   : x;

    y = y > 1   ?   1   : y;
    y = y < -1  ?  -1   : y;

    stringstream ss;
    ss << y;
    SmartDashboard::PutString("DB/String 7", ss.str());

    stringstream ss2;
    ss2 << x;
    SmartDashboard::PutString("DB/String 8", ss2.str());
    m_FLTalon.goVoltage (x + rotation);
    m_BRTalon.goVoltage (x - rotation);

    m_FRTalon.goVoltage (y - rotation);
    m_BLTalon.goVoltage (y + rotation);

}



bool relativeMecanumDrivetrain::doneMove (double tolerancePercentage)
{

    if(m_isDistanceMove)
    {
        double difference = m_distance - m_goalDistance;
        return (fabs(difference) < fabs((tolerancePercentage * m_goalDistance))) && m_headingControl.isDone();
    }
    return m_headingControl.isDone();
}

double relativeMecanumDrivetrain::PIDGet ()
{
    double distance = getDistance();
//    std::stringstream dist;
//    dist << "Distance: " << distance;
//    SmartDashboard::PutString("DB/String 4", dist.str());

//    LOGI << dist.str();

    m_distance = distance;

    return distance;
}

void relativeMecanumDrivetrain::PIDWrite (double output)
{
    if(CANSpeedController::ControlMode::kPosition == m_mode)
    {
        m_distanceOutput = output;
        double relativeMax = output * m_maxSpeed;
    	double speedX = 0;
    	double speedY = 0;



    	if(fabs(m_goalX) > fabs(m_goalY))
    	{
    		speedX = relativeMax;
    		speedY = fabs((m_goalY / m_goalX)) * relativeMax;
    	}
    	else
    	{
    		speedY = relativeMax;
    		speedX = fabs((m_goalX / m_goalY)) * relativeMax;
    	}


    	speedY *= fabs(m_goalY) / m_goalY;
    	speedX *= fabs(m_goalX) / m_goalX;

        if(fabs(m_goalY) < 0.05)
        {
            speedY = 0;
        }

        if(fabs(m_goalX) < 0.05)
        {
            speedX = 0;
        }


        m_FLTalon.goAt (speedX + (m_maxSpeed * m_headingControl.getOutput () * m_gyroSensitivity));
        m_BRTalon.goAt (speedX - (m_maxSpeed * m_headingControl.getOutput () * m_gyroSensitivity));

        m_FRTalon.goAt (speedY - (m_maxSpeed * m_headingControl.getOutput () * m_gyroSensitivity));
        m_BLTalon.goAt (speedY + (m_maxSpeed * m_headingControl.getOutput () * m_gyroSensitivity));

//        std::stringstream gX;
//        gX << "speed X: " << speedX;
//        SmartDashboard::PutString("DB/String 0", gX.str());
//
//        std::stringstream gY;
//        gY << "speed Y: " << speedY;
//        SmartDashboard::PutString("DB/String 1", gY.str());
//
//        std::stringstream speeds;
//        speeds << "Output Dist: " << output;
//        SmartDashboard::PutString("DB/String 3", speeds.str());
//
//        std::stringstream rot;
//        rot << "Rotation Spd: " << (m_maxSpeed * m_headingControl.getOutput () * m_gyroSensitivity);
//        SmartDashboard::PutString("DB/String 2", rot.str());
////        LOGI << speeds.str();
//
//        std::stringstream rotation;
//        rotation << "Rotation: " << m_headingControl.getOutput ();
//        SmartDashboard::PutString("DB/String 9", rotation.str());
//        LOGI << speeds.str();
    }
}

void relativeMecanumDrivetrain::SetPIDSourceType (PIDSourceType pidSource)
{
    m_pidSource = pidSource;
}

double relativeMecanumDrivetrain::getDistance ()
{

//    Wrong Code
//    double xPos = (-(m_FLTalon.GetEncPosition () - m_FLenc)  + (m_BRTalon.GetEncPosition () - m_BRenc)) / 2;
//    double yPos = ((m_FRTalon.GetEncPosition () - m_FRenc) + -(m_BLTalon.GetEncPosition () - m_BLenc)) / 2;
//
//    return sqrt((xPos * xPos) + (yPos * yPos));

//    Only works when going forawrd and back

//    return fabs((-(m_FLTalon.GetEncPosition () - m_FLenc) + (m_BRTalon.GetEncPosition () - m_BRenc) + (m_FRTalon.GetEncPosition () - m_FRenc) + -(m_BLTalon.GetEncPosition () - m_BLenc)) / 4);

    return (fabs((-(m_FLTalon.GetEncPosition () - m_FLenc) + (m_BRTalon.GetEncPosition () - m_BRenc)) / (2 * 0.7071)) + fabs(((m_FRTalon.GetEncPosition () - m_FRenc) + -(m_BLTalon.GetEncPosition () - m_BLenc)) / (2 * 0.7071))) / 2;
}

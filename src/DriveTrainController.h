#pragma once

#include "BaseController.h"
#include "WPILib.h"

/* TODO: Change order/numbering of
   enumeration to correct motor channels. */
enum MotorChannels
{
    REAR_LEFT_MOTOR,
    FRONT_LEFT_MOTOR,
    FRONT_RIGHT_MOTOR,
    REAR_RIGHT_MOTOR
};

class DriveTrainController : public BaseController
{
public:
    DriveTrainController(void);
    ~DriveTrainController(void);

    // void moveStraight(float distance, float motorSpeed);
    // void turn(float degrees, float motorSpeed);

private:
    RobotDrive m_driveTrain;
};

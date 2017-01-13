#include "DriveTrainController.h"
#include "WPILib.h"

DriveTrainController::DriveTrainController()
    : m_driveTrain(FRONT_LEFT_MOTOR, REAR_LEFT_MOTOR,
		   FRONT_RIGHT_MOTOR, REAR_RIGHT_MOTOR)
{
}

DriveTrainController::~DriveTrainController()
{
}

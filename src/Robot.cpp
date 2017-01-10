
#include "WPILib.h"
#include "constants.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "LoggerController.h"

using namespace std;

class Robot: public SampleRobot
{
    Talon m_FRDrive;
    Talon m_FLDrive;
    Talon m_BRDrive;
    Talon m_BLDrive;


public:
        Robot():
            m_FRDrive(PortAssign::frontRightWheelMotor),
            m_FLDrive(PortAssign::frontLeftWheelMotor),
            m_BRDrive(PortAssign::backRightWheelMotor),
            m_BLDrive(PortAssign::backLeftWheelMotor)
        {
        }
	void RobotInit() override {
              plog::init(plog::debug, "/home/lvuser/robot_logger.txt");

	}

	void Autonomous() {

	}

	void OperatorControl() {

	}

	void Test() {
	}

};

START_ROBOT_CLASS(Robot)

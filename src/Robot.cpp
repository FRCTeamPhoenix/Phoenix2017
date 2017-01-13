
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
    LoggerController m_loggerController;


public:
        Robot():
            m_FRDrive(PortAssign::frontRightWheelMotor),
            m_FLDrive(PortAssign::frontLeftWheelMotor),
            m_BRDrive(PortAssign::backRightWheelMotor),
            m_BLDrive(PortAssign::backLeftWheelMotor),
            m_loggerController()
        {
        }
	void RobotInit() override {
	    LOGI << "Start Robot Init";


	}

	void Autonomous() {
	    LOGI << "Start Auto";
            while(IsEnabled() && IsAutonomous())
            {

            }

	}

	void OperatorControl() {
	    LOGI << "Start Teleop";

	    while(IsEnabled() && IsOperatorControl())
	    {

	    }

	}

	void Test() {
	    LOGI << "Start Test Mode";
            while(IsEnabled() && IsTest())
            {

            }
	}

};

START_ROBOT_CLASS(Robot)

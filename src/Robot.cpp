
#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"
#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include "sys/stat.h"
//#include "LoggerController.h"

using namespace std;

class Robot: public SampleRobot
{
    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;

    relativeMecanumDrivetrain m_drivetrain;

    Joystick m_gamepad;


//    LoggerController m_loggerController;


public:
        Robot():
                m_FRDrive(1, 2000, 2000),
                m_FLDrive(2, 2000, 2000),
                m_BRDrive(3, 2000, 2000),
                m_BLDrive(4, 2000, 2000),
                m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),

                m_gamepad(0)
//            m_loggerController()
        {
        }
	void RobotInit() override {
//	    LOGI << "Start Robot Init";

	}

	void Autonomous() {
//	    LOGI << "Start Auto";

	}

	void OperatorControl() {
        double FrontBack = m_gamepad.GetY ();
        double LeftRight = m_gamepad.GetZ ();

        m_drivetrain.moveRelative (FrontBack, LeftRight);

	}

	void Test() {
        if(m_gamepad.GetRawButton (1))
        {
            m_FRDrive.tunePosition (2, 3200, 0.5);
        }
        if(m_gamepad.GetRawButton (2))
        {
            m_drivetrain.moveDistance (10000, 0);
        }
        if(m_gamepad.GetRawButton (3))
        {
            m_drivetrain.moveDistance (5000, 45);
        }
        if(m_gamepad.GetRawButton (4))
        {
            m_drivetrain.moveDistance (10000, -90);
        }
        if(m_gamepad.GetRawButton (5))
        {
            m_drivetrain.moveDistance (20000, -160);
        }
    }

};

START_ROBOT_CLASS(Robot)


#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"
#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "ADIS16448_IMU.h"
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
	ADIS16448_IMU weirdBoardThing;


//    LoggerController m_loggerController;


public:
        Robot():
                m_FRDrive(3, 2000, 2000),
                m_FLDrive(2, 2000, 2000),
                m_BRDrive(4, 2000, 2000),
                m_BLDrive(1, 2000, 2000),
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
		weirdBoardThing.Reset();

        while(IsEnabled() && IsOperatorControl())
        {
            std::ostringstream outputX;
			outputX << "Weird Gyro X: ";
			outputX << (weirdBoardThing.GetAngleX());
			SmartDashboard::PutString("DB/String 5", outputX.str());

            std::ostringstream outputY;
			outputY << "Weird Gyro Y: ";
			outputY << (weirdBoardThing.GetAngleY());
			SmartDashboard::PutString("DB/String 6", outputY.str());

            std::ostringstream outputZ;
			outputZ << "Weird Gyro Z: ";
			outputZ << (weirdBoardThing.GetAngleZ());
			SmartDashboard::PutString("DB/String 7", outputZ.str());

            double FrontBack = -m_gamepad.GetY ();
            double LeftRight = m_gamepad.GetX ();
            double rotation = m_gamepad.GetZ ();

            if(fabs(FrontBack) < 0.2){
            	FrontBack = 0;
            }
            if(fabs(LeftRight) < 0.2){
				LeftRight = 0;
			}
            if(fabs(rotation) < 0.2){
                rotation = 0;
            }

            FrontBack /= 4;
            LeftRight /= 4;
            rotation /= 4;

            m_drivetrain.moveRelative (FrontBack, LeftRight, rotation);
        }
	}

	void Test() {
        while(IsEnabled() && IsTest())
        {
            if (m_gamepad.GetRawButton (1))
            {
                m_FRDrive.tunePosition (2, 3200, 0.5);
            }
            if (m_gamepad.GetRawButton (2))
            {
                m_drivetrain.moveDistance (2000, 0, 0.2);
            }
            if (m_gamepad.GetRawButton (3))
            {
                m_drivetrain.moveDistance (8000, 90, 0.3);
            }
            if (m_gamepad.GetRawButton (4))
            {
                m_drivetrain.moveDistance (8000, -90, 0.3);
            }
            if (m_gamepad.GetRawButton (5))
            {
                m_drivetrain.moveDistance (20000, -160, 0.2);
            }
        }
    }

};

START_ROBOT_CLASS(Robot)

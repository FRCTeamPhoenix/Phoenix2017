#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"
#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "ADIS16448_IMU.h"
#include "ConfigEditor.h"
#include "LoggerController.h"
#include "FlyWheels.h"
#include "Turret.h"
#include "ShooterController.h"
#include "ConfigEditor.h"
#include "AutoController.h"
#include "Actions/Actions.h"
#include <fstream>
#include "json.hpp"
#include "Lidar.h"
#include "JSONFile.h"

using namespace std;
using json=nlohmann::json;

class Robot: public SampleRobot
{
    JSONFile m_talonsJSON;

    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;
    relativeMecanumDrivetrain m_drivetrain;
    SmartTalon m_rightFlyWheelMotor;
    SmartTalon m_leftFlyWheelMotor;
    SmartTalon m_turretRotateMotor;
    DigitalInput m_leftLimitSwitch;
    DigitalInput m_rightLimitSwitch;
    Joystick m_joystick;
    Joystick m_gamepad;
    ADIS16448_IMU m_gyro;
    FlyWheels m_flywheel;
    Turret m_turret;
    LoggerController m_loggerController;
    ShooterController m_shooterController;
    ConfigEditor m_configEditor;
    AutoController m_autoController;
    Lidar m_lidar;

public:
    Robot() :
            m_talonsJSON("talons.json"),
            m_FRDrive(3, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["3"]),
            m_FLDrive(2, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["2"]),
            m_BRDrive(4, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["4"]),
            m_BLDrive(1, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["1"]),
            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_gyro, HeadingControl::GyroAxes::x),
            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["6"]),
			m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["5"]),
			m_turretRotateMotor(PortAssign::turretRotationMotor, CANTalon::FeedbackDevice::QuadEncoder, m_talonsJSON.get()["7"]),
			m_leftLimitSwitch(PortAssign::leftLimitSwitch),
			m_rightLimitSwitch(PortAssign::rightLimitSwitch),
			m_joystick(PortAssign::joystick),
			m_gamepad(PortAssign::gamepad),
			m_gyro(),
			m_flywheel(m_rightFlyWheelMotor,m_leftFlyWheelMotor, m_gamepad),
			m_turret(m_turretRotateMotor, m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
            m_loggerController(),
			m_shooterController(m_flywheel, m_turret),
            m_configEditor(),
            m_autoController(),
            m_lidar(PortAssign::lidarTriggerPin, PortAssign::lidarMonitorPin, 0)
		{
    	}


        void Autonomous()
        {
//            m_autoController.clearQueue ();
////            m_autoController.pushAction (new ActionRotate(m_drivetrain, 90, 0.4));
//            m_autoController.pushAction (new ActionGoDistance(m_drivetrain, 8200, 0, 0.1));
//			m_autoController.pushAction (new ActionMotorDoneDistance(m_drivetrain));
//            m_autoController.pushAction (new ActionGoDistance(m_drivetrain, 8200, 0, 0.1));
//			m_autoController.pushAction (new ActionMotorDoneDistance(m_drivetrain));
//////			m_autoController.pushAction (new ActionRotate(m_drivetrain, 30, 0.05));
//			m_autoController.pushAction (new ActionGoDistance(m_drivetrain, 1500, -90, 0.1));
//			m_autoController.pushAction (new ActionMotorDoneDistance(m_drivetrain));
//            m_autoController.pushAction (new ActionGoDistance(m_drivetrain, 3000, 90, 0.1));
//			m_autoController.pushAction (new ActionMotorDoneDistance(m_drivetrain));
//            m_autoController.pushAction (new ActionGoDistance(m_drivetrain, 8000, 0, 0.1));
        	bool init = false;

            LOGI << "Start Auto";
            while (IsEnabled() && IsAutonomous())
            {
//                m_autoController.run ();
            }

        }

        void OperatorControl()
        {

            LOGI << "Start Teleop";
        	int count = 0;

            while (IsEnabled() && IsOperatorControl())
            {
//				m_FLDrive.SetControlMode(CANSpeedController::kPosition);
//				m_BRDrive.SetControlMode(CANSpeedController::kPosition);
//				m_BLDrive.SetControlMode(CANSpeedController::kPosition);
				if(count < 10){
					m_drivetrain.moveDistance(20000, 0, 0.4);


    //            		m_FRDrive.SetControlMode(CANSpeedController::kPosition);
    //                	m_FRDrive.Set(2000);
					count ++;
				}
    //            	m_FRDrive.Get();
    //				m_FLDrive.Get();
    //				m_BRDrive.Get();
    //				m_BLDrive.Get();

    //                m_autoController.run ();




//                double FrontBack = -m_gamepad.GetY();
//                double LeftRight = m_gamepad.GetX();
//                double rotation = m_gamepad.GetZ();
//                std::ostringstream outputX;
//                outputX << "Weird Gyro X: ";
//                outputX << (weirdBoardThing.GetAngleX());
//                SmartDashboard::PutString("DB/String 5", outputX.str());
//
//                std::ostringstream outputY;
//                outputY << "Weird Gyro Y: ";
//                outputY << (weirdBoardThing.GetAngleY());
//                SmartDashboard::PutString("DB/String 6", outputY.str());
//
//                std::ostringstream outputZ;
//                outputZ << "Weird Gyro Z: ";
//                outputZ << (weirdBoardThing.GetAngleZ());
//                SmartDashboard::PutString("DB/String 7", outputZ.str());
//
//                if (fabs(FrontBack) < 0.2)
//                {
//                    FrontBack = 0;
//                }
//                if (fabs(LeftRight) < 0.2)
//                {
//                    LeftRight = 0;
//                }
//                if (fabs(rotation) < 0.2)
//                {
//                    rotation = 0;
//                }
//
//                FrontBack /= 4;
//                LeftRight /= 4;
//                rotation /= 4;
//
//                m_drivetrain.moveRelative(FrontBack, LeftRight, rotation);
            }    
        
    }

    void Test()
    {
    //bool init = false;

            //LOGI << "Start Test Mode";
            while (IsEnabled() && IsTest())
            {
//                m_configEditor.update();
//            	if(!init){
//                    m_drivetrain.G(2000, 0, 0.4);
//                    init = true;

            	std::stringstream mode;
            	mode << "Current Mode: " << m_drivetrain.m_mode;
            	SmartDashboard::PutString("DB/String 2", mode.str());

                if (m_gamepad.GetRawButton(1))
                {
                    m_FRDrive.tunePosition(2, 3200, 0.5);
                }
                else if (m_gamepad.GetRawButton(2))
                {
                    m_drivetrain.moveDistance(0, 0, 0.03, -120);
                }
                else if (m_gamepad.GetRawButton(5))
                {
                    m_drivetrain.moveDistance(16000, 0, 0.03, 90);
                }
                else if (m_gamepad.GetRawButton(4))
                {
                    m_drivetrain.moveDistance(0, 0, 0.03, 90);
                }
                else if (m_gamepad.GetRawButton(6))
                {
                    m_drivetrain.moveDistance(8000, -90, 0.03);
                }
                else if (m_gamepad.GetRawButton(3))
				{
					m_drivetrain.moveDistance(8000, -180, 0.03);
				}
                else if (m_gamepad.GetRawButton(11))
                {
					double FrontBack = -m_gamepad.GetY();
					double LeftRight = m_gamepad.GetX();
					double rotation = m_gamepad.GetZ();
					if (fabs(FrontBack) < 0.2)
					{
						FrontBack = 0;
					}
					if (fabs(LeftRight) < 0.2)
					{
						LeftRight = 0;
					}
					if (fabs(rotation) < 0.2)
					{
						rotation = 0;
					}

					FrontBack /= 4;
					LeftRight /= 4;
					rotation /= 4;

					m_drivetrain.moveRelative(FrontBack, LeftRight, rotation);
                }
            }
    
    }

};

START_ROBOT_CLASS(Robot)

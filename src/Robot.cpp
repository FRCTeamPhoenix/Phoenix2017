#include "WPILib.h"
#include "constants.h"
#include "SmartTalon.h"
#include "relativeMecanumDrivetrain.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "ADIS16448_IMU.h"
#include "ConfigEditor.h"
#include "LoggerController.h"
#include "AutoController.h"
#include "Actions/Actions.h"
#include <fstream>
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class Robot: public SampleRobot
{
        SmartTalon m_FRDrive;
        SmartTalon m_FLDrive;
        SmartTalon m_BRDrive;
        SmartTalon m_BLDrive;
        ADIS16448_IMU m_gyro;

        relativeMecanumDrivetrain m_drivetrain;

        Joystick m_gamepad;

        LoggerController m_loggerController;
        ConfigEditor m_configEditor;
        AutoController m_autoController;


    public:
        Robot() :
                m_FRDrive(3, CANTalon::FeedbackDevice::QuadEncoder),
                m_FLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
                m_BRDrive(4, CANTalon::FeedbackDevice::QuadEncoder),
                m_BLDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
                m_gyro(),
                m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_gyro, HeadingControl::GyroAxes::x),
                m_gamepad(0),
                m_loggerController(),
                m_configEditor(),
                m_autoController()

        {
        }
        void RobotInit() override
        {
            LOGI << "Start Robot Init";
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
            m_gyro.Reset();
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
        	bool init = false;

            //LOGI << "Start Test Mode";
            while (IsEnabled() && IsTest())
            {
//                m_configEditor.update();
//            	if(!init){
//                    m_drivetrain.G(2000, 0, 0.4);
//                    init = true;

				std::ostringstream outputX;
				outputX << "Weird Gyro X: ";
				outputX << (m_gyro.GetAngleX());
				SmartDashboard::PutString("DB/String 6", outputX.str());

				std::ostringstream outputY;
				outputY << "Weird Gyro Y: ";
				outputY << (m_gyro.GetAngleY());
				SmartDashboard::PutString("DB/String 7", outputY.str());

				std::ostringstream outputZ;
				outputZ << "Weird Gyro Z: ";
				outputZ << (m_gyro.GetAngleZ());
				SmartDashboard::PutString("DB/String 8", outputZ.str());

//				std::stringstream mode;
//            	mode << "Current Mode: " << m_drivetrain.m_mode;
//            	SmartDashboard::PutString("DB/String 2", mode.str());

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

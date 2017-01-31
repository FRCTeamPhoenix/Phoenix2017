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

using namespace std;
using json=nlohmann::json;

class Robot: public SampleRobot
{
    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;
    relativeMecanumDrivetrain m_drivetrain;
//    SmartTalon m_rightFlyWheelMotor;
//    SmartTalon m_leftFlyWheelMotor;
//    SmartTalon m_turretRotateMotor;
//    DigitalInput m_leftLimitSwitch;
//    DigitalInput m_rightLimitSwitch;
    Joystick m_joystick;
    Joystick m_gamepad;
    ADIS16448_IMU m_gyro;
//    FlyWheels m_flywheel;
//    Turret m_turret;
    LoggerController m_loggerController;
//    ShooterController m_shooterController;
//    ConfigEditor m_configEditor;
//    AutoController m_autoController;
//    Lidar m_lidar;

public:
    Robot() :
            m_FRDrive(7, CANTalon::FeedbackDevice::QuadEncoder),
            m_FLDrive(8, CANTalon::FeedbackDevice::QuadEncoder),

            m_BRDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
            m_BLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),

            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive, m_gyro, HeadingControl::GyroAxes::x),
//            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
//			m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
//			m_turretRotateMotor(PortAssign::turretRotationMotor, CANTalon::FeedbackDevice::QuadEncoder),
//			m_leftLimitSwitch(PortAssign::leftLimitSwitch),
//			m_rightLimitSwitch(PortAssign::rightLimitSwitch),
			m_joystick(PortAssign::joystick),
			m_gamepad(PortAssign::gamepad),
//			m_gyro(),
//			m_flywheel(m_rightFlyWheelMotor,m_leftFlyWheelMotor, m_gamepad),
//			m_turret(m_turretRotateMotor, m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
            m_loggerController()
//			m_shooterController(m_flywheel, m_turret),
//            m_configEditor(),
//            m_autoController(),
//            m_lidar(PortAssign::lidarTriggerPin, PortAssign::lidarMonitorPin, 0)
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

        	int maxSpeed = 0;

            while (IsEnabled() && IsOperatorControl())
            {

//            	m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
//            	m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
//            	m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
//            	m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);

				double FrontBack = -m_joystick.GetY();
				double LeftRight = m_joystick.GetX();
				double rotation = m_joystick.GetZ();
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



				std::stringstream FR;
				FR << "FR Speed: " << m_FRDrive.GetSpeed();
				SmartDashboard::PutString("DB/String 5", FR.str());

				std::stringstream FL;
				FL << "FL Speed: " << m_FLDrive.GetSpeed();
				SmartDashboard::PutString("DB/String 6", FL.str());

				std::stringstream BR;
				BR << "BR Speed: " << m_BRDrive.GetSpeed();
				SmartDashboard::PutString("DB/String 7", BR.str());

				std::stringstream BL;
				BL << "BL Speed: " << m_BLDrive.GetSpeed();
				SmartDashboard::PutString("DB/String 8", BL.str());
//				}


            }    
        
    }

    void Test()
    {
    //bool init = false;

            //LOGI << "Start Test Mode";
            while (IsEnabled() && IsTest())
            {
            	std::stringstream FR;
            	FR << "X: " << m_gyro.GetAngleX();
            	SmartDashboard::PutString("DB/String 5", FR.str());

            	std::stringstream FL;
            	FL << "Y: " << m_gyro.GetAngleY();
            	SmartDashboard::PutString("DB/String 6", FL.str());

            	std::stringstream BR;
            	BR << "Z: " << m_gyro.GetAngleZ();
            	SmartDashboard::PutString("DB/String 7", BR.str());

//            	std::stringstream BL;
//            	BL << "Accel Y: " << m_gyro.GetAngleZ();
//            	SmartDashboard::PutString("DB/String 8", BL.str());

//                m_configEditor.update();
//            	if(!init){
//                    m_drivetrain.G(2000, 0, 0.4);
//                    init = true;

            	std::stringstream mode;
            	mode << "Current Mode: " << m_drivetrain.m_mode;
            	SmartDashboard::PutString("DB/String 2", mode.str());

                if (m_joystick.GetRawButton(1))
                {
//                    m_FRDrive.tunePosition(2, 3200, 0.5);
                }
                else if (m_joystick.GetRawButton(2))
                {
//                    m_drivetrain.moveDistance(0, 0, 0.03, -120);
                }
                else if (m_joystick.GetRawButton(5))
                {
                    m_drivetrain.moveDistance(30000, 0, 0.5, 0);
                }
                else if (m_joystick.GetRawButton(4))
                {
                    m_drivetrain.moveDistance(30000, 180, 0.5, 0);
                }
                else if (m_joystick.GetRawButton(6))
                {
//                    m_drivetrain.moveDistance(8000, -90, 0.03);
                }
                else if (m_joystick.GetRawButton(3))
				{
//					m_drivetrain.moveDistance(8000, -180, 0.03);
				}
                else if (m_joystick.GetRawButton(11))
                {
					double FrontBack = -m_joystick.GetY();
					double LeftRight = m_joystick.GetX();
					double rotation = m_joystick.GetZ();
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

					FrontBack /= 3;
					LeftRight /= 3;
					rotation /= 3;

					m_drivetrain.moveRelative(FrontBack, LeftRight, rotation);
                }
            }

    
    }

};

START_ROBOT_CLASS(Robot)

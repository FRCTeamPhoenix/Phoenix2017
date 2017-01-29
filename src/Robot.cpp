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
#include "Actions/ActionFactory.h"
#include <fstream>
#include "json.hpp"
#include "Lidar.h"
#include "Climber.h"

using namespace std;
using json=nlohmann::json;


class Robot: public SampleRobot
{

    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;
    ActionGroup m_mainAutoGroup;
//    relativeMecanumDrivetrain m_drivetrain;
//    SmartTalon m_rightFlyWheelMotor;
//    SmartTalon m_leftFlyWheelMotor;
//    SmartTalon m_turretRotateMotor;
//    DigitalInput m_leftLimitSwitch;
//    DigitalInput m_rightLimitSwitch;
    Joystick m_joystick;
//    Joystick m_gamepad;
//    ADIS16448_IMU m_expansionBoard;
//    FlyWheels m_flywheel;
//    Turret m_turret;
    LoggerController m_loggerController;
//    ShooterController m_shooterController;
//    ConfigEditor m_configEditor;
//    Lidar m_lidar;
//    SmartTalon m_climberMotor;
//    Climber m_climber;

public:
    Robot() :
            m_FRDrive(7, CANTalon::FeedbackDevice::QuadEncoder),
            m_FLDrive(8, CANTalon::FeedbackDevice::QuadEncoder),
            m_BRDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
            m_BLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
            m_mainAutoGroup(),
//            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
//            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
//            m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
//            m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
//            m_leftLimitSwitch(PortAssign::leftLimitSwitch),
//            m_rightLimitSwitch( PortAssign::rightLimitSwitch),
            m_joystick(PortAssign::joystick),
//            m_gamepad(PortAssign::gamepad),
//            m_expansionBoard(),
//            m_flywheel(m_rightFlyWheelMotor, m_leftFlyWheelMotor, m_gamepad),
//            m_turret(m_turretRotateMotor,m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
            m_loggerController()
//            m_shooterController(m_flywheel, m_turret),
//            m_configEditor(),
//            m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
//			m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
//			m_climber(m_climberMotor, m_joystick)
    {

    }
    void RobotInit() override
    {
        LOGI << "Start Robot Init";

    }

    void Autonomous()
    {

        bool init = false;

        LOGI << "Start Auto";
        while (IsEnabled() && IsAutonomous())
        {
            m_mainAutoGroup.execute (m_mainAutoGroup.getContainedActions ());
        }

    }
    void OperatorControl()
    {

        LOGI << "Start Teleop";
        //int count = 0;

        while (IsEnabled() && IsOperatorControl())
        {

        }

    }

    void Test()
    {
    	m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
    	m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
    	m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
    	m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);

        LOGI << "Start Test Mode";
        while (IsEnabled() && IsTest())
        {
            if(m_joystick.GetRawButton (6))
                m_FRDrive.Set (0.2);
            else
                m_FRDrive.Set (0);

            if(m_joystick.GetRawButton (5))
                m_FLDrive.Set (0.2);
            else
                m_FLDrive.Set (0);

            if(m_joystick.GetRawButton (4))
                m_BRDrive.Set (0.2);
            else
                m_BRDrive.Set (0);

            if(m_joystick.GetRawButton (3))
                m_BLDrive.Set (0.2);
            else
                m_BLDrive.Set (0);



        }

    }

};

START_ROBOT_CLASS(Robot)

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
    SmartTalon m_rightFlyWheelMotor;
    SmartTalon m_leftFlyWheelMotor;
    SmartTalon m_turretRotateMotor;
    DigitalInput m_leftLimitSwitch;
    DigitalInput m_rightLimitSwitch;
    Joystick m_joystick;
    Joystick m_gamepad;
    ADIS16448_IMU m_expansionBoard;
    FlyWheels m_flywheel;
    Turret m_turret;
    LoggerController m_loggerController;
    ShooterController m_shooterController;
    ConfigEditor m_configEditor;
    AutoController m_autoController;
    Lidar m_lidar;
    SmartTalon m_feederMotor;
    SmartTalon m_indexerMotor;

public:
    Robot() :
            m_FRDrive(3, CANTalon::FeedbackDevice::QuadEncoder),
            m_FLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
            m_BRDrive(4, CANTalon::FeedbackDevice::QuadEncoder),
            m_BLDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
            m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
            m_leftLimitSwitch(PortAssign::leftLimitSwitch),
            m_rightLimitSwitch( PortAssign::rightLimitSwitch),
            m_joystick(PortAssign::joystick),
            m_gamepad(PortAssign::gamepad),
            m_expansionBoard(),
            m_flywheel(m_rightFlyWheelMotor, m_leftFlyWheelMotor, m_gamepad),
            m_turret(m_turretRotateMotor,m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
            m_loggerController(),
            m_shooterController(m_flywheel, m_turret),
            m_configEditor(),
            m_autoController(),
            m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
            m_feederMotor(PortAssign::feeder, CANTalon::FeedbackDevice::QuadEncoder),
            m_indexerMotor(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder)

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
            if (!init)
            {
                init = true;
            }

            m_autoController.run();
        }

    }
    void OperatorControl()
    {

        m_expansionBoard.Reset();
        LOGI << "Start Teleop";

        while (IsEnabled() && IsOperatorControl())
        {

        }

    }

    void Test()
    {

        LOGI << "Start Test Mode";
        while (IsEnabled() && IsTest())
        {


           //feeder test

           if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
              m_feederMotor.goAt(SmartDashboard::GetNumber("DB/Slider 0",0.0));

           }
           else
           {
               m_feederMotor.goAt((m_joystick.GetThrottle()-1) / 2);
           }
            std::ostringstream throttleValue;
            throttleValue << "Throttle: ";
            throttleValue << ((m_joystick.GetThrottle()-1) / 2);
            SmartDashboard::PutString("DB/String 7", throttleValue.str());

            std::ostringstream feederEncoderValue;
            feederEncoderValue << "EncoderF: ";
            feederEncoderValue << m_feederMotor.GetEncPosition();
            SmartDashboard::PutString("DB/String 6", feederEncoderValue.str());



            //indexer test
            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)){
                m_indexerMotor.goDistance(250,0.5);

           }

           std::ostringstream indexerEncoderValue;
           indexerEncoderValue << "EncoderI: ";
           indexerEncoderValue << m_feederMotor.GetEncPosition();
           SmartDashboard::PutString("DB/String 8", indexerEncoderValue.str());



           if (m_gamepad.GetRawButton(DriveStationConstants::buttonX)){
               m_rightFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1",0.0));
               m_leftFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2",0.0));
           }
           else
           {
               m_rightFlyWheelMotor.goAt(m_joystick.GetY());
               m_leftFlyWheelMotor.goAt(m_joystick.GetY());
           }
            m_configEditor.update();

        }

    }

};

START_ROBOT_CLASS(Robot)

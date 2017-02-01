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
#include "Climber.h"

//Test mode includes
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>




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
    SmartTalon m_climberMotor;
    Climber m_climber;

private:
    frc::SendableChooser<int*> m_testModeChooser;

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
        m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
        m_climber(m_climberMotor, m_joystick)

{
}
    void RobotInit() override
            {
        LOGI << "Start Robot Init";
        m_testModeChooser.AddObject("All Talons", new int (1)); //Test all Talons on robot
        m_testModeChooser.AddObject("Shooter Head", new int (2)); //Test Shooter Head
        m_testModeChooser.AddObject("Feeder", new int (3)); //Test Feeder
        m_testModeChooser.AddObject("Indexer", new int (4)); //Test Indexer
        m_testModeChooser.AddObject("Gatherer", new int (5)); //Test Gather
        m_testModeChooser.AddObject("Turret", new int (6)); //Test Turret
        m_testModeChooser.AddObject("Climber", new int (7)); //Test Climber
        m_testModeChooser.AddObject("All of Shooter", new int (8)); //Test all Shooter Components
        m_testModeChooser.AddObject("Drive Train", new int (9)); //Test all 4 Drive Train Motors
        frc::SmartDashboard::PutData("Test Modes", &m_testModeChooser);
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
        //int count = 0;

        while (IsEnabled() && IsOperatorControl())
        {

        }

    }

    void Test()
    {
        LOGI << "Start Test Mode";
        while (IsEnabled() && IsTest())
        {

            float power = m_joystick.GetY();
            if (fabs(power) < 0.05f){
                power = 0;
            }
            else{
                power = m_joystick.GetY() / 3;
            }

            switch(*m_testModeChooser.GetSelected())
            {
            case 1: //Test all Talons on robot
            {
                std::ostringstream mode;
                mode << "All Talons";
                SmartDashboard::PutString("DB/String 0", mode.str());

                std::ostringstream encoderFRDrive;
                encoderFRDrive << m_FRDrive.GetEncPosition();
                SmartDashboard::PutString("DB/String 1", "FRD ENC: " + encoderFRDrive.str());

                std::ostringstream encoderFLDrive;
                encoderFRDrive << m_FLDrive.GetEncPosition();
                SmartDashboard::PutString("DB/String 2", "FLD ENC: " + encoderFRDrive.str());

                std::ostringstream encoderBRDrive;
                encoderFRDrive << m_BRDrive.GetEncPosition();
                SmartDashboard::PutString("DB/String 3", "BRD ENC: " + encoderFRDrive.str());

                std::ostringstream encoderBLDrive;
                encoderFRDrive << m_BLDrive.GetEncPosition();
                SmartDashboard::PutString("DB/String 4", "BLD ENC: " + encoderFRDrive.str());

                std::ostringstream encoderRFW;
                encoderFRDrive << m_rightFlyWheelMotor.GetEncPosition();
                SmartDashboard::PutString("DB/String 5", "RFW ENC: " + encoderFRDrive.str());

                std::ostringstream encoderLFW;
                encoderFRDrive << m_leftFlyWheelMotor.GetEncPosition();
                SmartDashboard::PutString("DB/String 6", "LFW ENC: " + encoderFRDrive.str());

                std::ostringstream encoderTRM;
                encoderFRDrive << m_turretRotateMotor.GetEncPosition();
                SmartDashboard::PutString("DB/String 7", "TRM ENC: " + encoderFRDrive.str());

                m_FRDrive.goAt(power);
                m_FLDrive.goAt(power);
                m_BRDrive.goAt(power);
                m_BLDrive.goAt(power);
                m_rightFlyWheelMotor.goAt(power);
                m_leftFlyWheelMotor.goAt(power);
                m_turretRotateMotor.goAt(power);
                break;
            }

            case 2: //Test Shooter Head
            {

                break;
            }

            case 3: //Test Feeder
            {

                break;
            }

            case 4: //Test Indexer
            {

                break;
            }

            case 5: //Test Gather
            {

                break;
            }

            case 6: //Test Turret
            {

                break;
            }

            case 7: //Test Climber
            {

                break;
            }

            case 8: //Test all Shooter Components
            {

                break;
            }

            case 9: //Test all 4 Drive Train Motors
            {

                break;
            }

            }

        }
    }
};

START_ROBOT_CLASS(Robot);

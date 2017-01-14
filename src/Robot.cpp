#include "WPILib.h"
#include "constants.h"
#include "plog/Log.h"
#include "sys/stat.h"
#include "LoggerController.h"
#include "FlyWheels.h"
#include "Turret.h"
#include "ShooterController.h"
#include "ConfigEditor.h"

using namespace std;

class Robot: public SampleRobot
{
    Talon m_FRDrive;
    Talon m_FLDrive;
    Talon m_BRDrive;
    Talon m_BLDrive;
    SmartTalon m_rightFlyWheelMotor;
    SmartTalon m_leftFlyWheelMotor;
    SmartTalon m_turretRotateMotor;
    Joystick m_joystick;
    Joystick m_gamepad;
    FlyWheels m_flywheel;
    Turret m_turret;
    LoggerController m_loggerController;
    ShooterController m_shooterController;
    ConfigEditor m_configEditor;

public:
    Robot() :
            m_FRDrive(PortAssign::frontRightWheelMotor),
            m_FLDrive(PortAssign::frontLeftWheelMotor),
            m_BRDrive(PortAssign::backRightWheelMotor),
            m_BLDrive(PortAssign::backLeftWheelMotor),
			m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor,2000,2000),
			m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor,2000,2000),
			m_turretRotateMotor(PortAssign::turretRotationMotor,2000,200),
			m_joystick(PortAssign::joystick),
			m_gamepad(PortAssign::gamepad),
			m_flywheel(m_rightFlyWheelMotor,m_leftFlyWheelMotor, m_gamepad),
			m_turret(m_turretRotateMotor, m_gamepad),
            m_loggerController(),
			m_shooterController(m_flywheel, m_turret),
            m_configEditor()

    {
    }
    void RobotInit() override
    {
        LOGI << "Start Robot Init";

    }

    void Autonomous()
    {
        LOGI << "Start Auto";
        m_shooterController.setState(ShooterController::AUTO);
        while (IsEnabled() && IsAutonomous())
        {
        	m_shooterController.run();
        }

    }
    void OperatorControl()
    {
        LOGI << "Start Teleop";
        m_shooterController.setState(ShooterController::TELEOP);
        while (IsEnabled() && IsOperatorControl())
        {
        	m_shooterController.run();
        }
    }

    void Test()
    {
        LOGI << "Start Test Mode";
        while (IsTest() && IsEnabled())
        {
            m_configEditor.update();
        }
    }

};

START_ROBOT_CLASS(Robot)

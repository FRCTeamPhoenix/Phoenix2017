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
	// TODO NEED ALL OF THE ACTUAL PIN NUMBERS CHECKED AND NEEDS FIX.
	// CHECK CONSTANTS.H
	// TODO NEEDS TO BE TESTED
	SmartTalon m_FRDrive;
	SmartTalon m_FLDrive;
	SmartTalon m_BRDrive;
	SmartTalon m_BLDrive;
	relativeMecanumDrivetrain m_drivetrain;
	SmartTalon m_rightFlyWheelMotor;
	SmartTalon m_leftFlyWheelMotor;
	SmartTalon m_turretRotateMotor;
	Joystick m_joystick;
	Joystick m_gamepad;
	ADIS16448_IMU m_expansionBoard;
	FlyWheels m_flywheel;
//	Turret m_turret;
	LoggerController m_loggerController;
//	ShooterController m_shooterController;
	ConfigEditor m_configEditor;
	AutoController m_autoController;
	Lidar m_lidar;
	SmartTalon m_climberMotor;
	Climber m_climber;
	SmartTalon m_feederMotor;
	SmartTalon m_indexerMotor;
	Talon m_gathererMotor;
	DigitalInput m_climberLimit;

private:
	frc::SendableChooser<int*> m_testModeChooser;

public:
	Robot() :
		m_FRDrive(PortAssign::frontRightWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_FLDrive(PortAssign::frontLeftWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_BRDrive(PortAssign::backRightWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_BLDrive(PortAssign::backLeftWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
		m_rightFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_leftFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
		m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
		m_joystick(PortAssign::joystick),
		m_gamepad(PortAssign::gamepad),
		m_expansionBoard(),
		m_flywheel(m_rightFlyWheelMotor, m_leftFlyWheelMotor, m_gamepad),
//		m_turret(m_turretRotateMotor,m_leftLimitSwitch, m_rightLimitSwitch, m_gamepad),
		m_loggerController(),
//		m_shooterController(m_flywheel, m_turret),
		m_configEditor(),
		m_autoController(),
		m_lidar(PortAssign::lidarTriggerPin,PortAssign::lidarMonitorPin, 0),
		m_climberMotor(PortAssign::climber, CANTalon::FeedbackDevice::QuadEncoder),
		m_climber(m_climberMotor, m_joystick),
		m_feederMotor(PortAssign::feeder, CANTalon::FeedbackDevice::QuadEncoder),
		m_indexerMotor(PortAssign::indexer, CANTalon::FeedbackDevice::QuadEncoder),
		m_gathererMotor(PortAssign::gatherer),
		m_climberLimit(1)
{
}
    void RobotInit() override
    {
        LOGI << "Start Robot Init";
        m_testModeChooser.AddObject("All Talons", new int(1)); //Test all Talons on robot
        LOGI << "add object 1";
        m_testModeChooser.AddObject("Shooter Head", new int(2)); //Test Shooter Head
        m_testModeChooser.AddObject("Feeder", new int(3)); //Test Feeder
        m_testModeChooser.AddObject("Indexer", new int(4)); //Test Indexer
        m_testModeChooser.AddObject("Gatherer", new int(5)); //Test Gather
        m_testModeChooser.AddObject("Turret", new int(6)); //Test Turret
        m_testModeChooser.AddObject("Climber", new int(7)); //Test Climber
        m_testModeChooser.AddObject("All of Shooter", new int(8)); //Test all Shooter Components
        m_testModeChooser.AddObject("Drive Train", new int(9)); //Test all 4 Drive Train Motors
        frc::SmartDashboard::PutData("Test Modes", &m_testModeChooser);
        LOGI << "Finish init";

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
    void printMessage(string place, string message)
    {
        std::ostringstream stream;
        stream << message;
        SmartDashboard::PutString("DB/String " + place, stream.str());
    }

    void Test()
    {
        // TODO ADD LIMITS
        LOGI << "Start Test Mode";
        bool isPID = false;
        float joystickPower = 0.0;
        float gamepadPower = 0.0;

        while (IsEnabled() && IsTest())
        {

            joystickPower = -m_joystick.GetY();
            if (fabs(joystickPower) < 0.05f)
            {
                joystickPower = 0.0f;
            }

            gamepadPower = -m_gamepad.GetY();
            if (fabs(gamepadPower) < 0.05f)
            {
                gamepadPower = 0.0f;
            }

            if (m_gamepad.GetRawButton(DriveStationConstants::buttonA))
            {
                isPID = true;
            }
            else if (m_gamepad.GetRawButton(DriveStationConstants::buttonB))
            {
                isPID = false;
            }

            printMessage("8", "Gyro: " + std::to_string(m_expansionBoard.GetAngleX()));
            printMessage("9", "Lidar: " + std::to_string(m_lidar.getFastAverage()));

            switch (/**m_testModeChooser.GetSelected()*/ 1) //null ptr causes code crash
            {
            case 1: //Test all Talons on robot
            {
                printMessage("0", "All Talons"); //mode
                printMessage("1", "FRD ENC " + std::to_string(m_FRDrive.GetEncPosition()));
                printMessage("2", "FLD ENC " + std::to_string(m_FLDrive.GetEncPosition()));
                printMessage("3", "BRD ENC " + std::to_string(m_BRDrive.GetEncPosition()));
                printMessage("4", "BLD ENC " + std::to_string(m_BLDrive.GetEncPosition()));
                printMessage("5", "TFW ENC " + std::to_string(m_rightFlyWheelMotor.GetEncPosition()));
                printMessage("6", "BFW ENC " + std::to_string(m_leftFlyWheelMotor.GetEncPosition()));
                printMessage("7", "TRM ENC " + std::to_string(m_turretRotateMotor.GetEncPosition()));


                if(isPID)
                {
                    m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_FRDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_FLDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_BRDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_BLDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_climberMotor.SetControlMode(CANSpeedController::kSpeed);

                    m_FRDrive.goAt(joystickPower);
                    m_FLDrive.goAt(joystickPower);
                    m_BRDrive.goAt(joystickPower);
                    m_BLDrive.goAt(joystickPower);
                    m_rightFlyWheelMotor.goAt(joystickPower);
                    m_leftFlyWheelMotor.goAt(joystickPower);
                    m_turretRotateMotor.goAt(joystickPower);
                    m_climberMotor.goAt(joystickPower);
                }
                else
                {
                    m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_turretRotateMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_climberMotor.SetControlMode(CANSpeedController::kPercentVbus);

                    m_FRDrive.Set(joystickPower);
                    m_FLDrive.Set(joystickPower);
                    m_BRDrive.Set(joystickPower);
                    m_BLDrive.Set(joystickPower);
                    m_rightFlyWheelMotor.Set(joystickPower);
                    m_leftFlyWheelMotor.Set(joystickPower);
                    m_turretRotateMotor.Set(joystickPower);
                    m_climberMotor.Set(joystickPower);
                }

                break;
            }

            case 2: //Test Shooter Head
            {
                printMessage("0", "Shooter Head");
                printMessage("1", "TFW ENC " + std::to_string(m_rightFlyWheelMotor.GetEncPosition()));
                printMessage("2", "BFW ENC " + std::to_string(m_leftFlyWheelMotor.GetEncPosition()));
                switch (isPID)
                {
                case true:
                    m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_rightFlyWheelMotor.goAt(joystickPower);
                    m_leftFlyWheelMotor.goAt(joystickPower);
                    break;
                case false:
                    m_rightFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_leftFlyWheelMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_rightFlyWheelMotor.Set(joystickPower);
                    m_leftFlyWheelMotor.Set(joystickPower);
                    break;
                }
                break;
            }

            case 3: //Test Feeder
            {
                printMessage("0", "Feeder");
                printMessage("1", "Feed ENC " + std::to_string(m_feederMotor.GetEncPosition()));
                switch (isPID)
                {
                case true:
                    m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_feederMotor.goAt(joystickPower);
                    break;
                case false:
                    m_feederMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_feederMotor.Set(joystickPower);
                    break;
                }
                break;
            }

            case 4: //Test Indexer
            {
                printMessage("0", "Indexer");
                printMessage("1", "Index ENC " + std::to_string(m_indexerMotor.GetEncPosition()));
                switch (isPID)
                {
                case true:
                    m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_indexerMotor.goAt(joystickPower);
                    break;
                case false:
                    m_indexerMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_indexerMotor.Set(joystickPower);
                    break;
                }
                break;
            }

            case 5: //Test Gather
            {
                printMessage("0", "Gatherer");
                m_gathererMotor.Set(joystickPower);
                break;
            }

            case 6: //Test Turret
            {
                printMessage("0", "Turret");
                printMessage("1", "TUR ENC " + std::to_string(m_turretRotateMotor.GetEncPosition()));
                printMessage("2", "TUR LIM1 " + std::to_string(m_turretRotateMotor.IsFwdLimitSwitchClosed()));
                printMessage("3", "TUR LIM2 " + std::to_string(m_turretRotateMotor.IsRevLimitSwitchClosed()));
                switch (isPID)
                {
                case true:
                    m_turretRotateMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_turretRotateMotor.goAt(joystickPower);
                    break;
                case false:
                    m_turretRotateMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_turretRotateMotor.Set(joystickPower);
                    break;
                }
                break;
            }

            case 7: //Test Climber
            {
                printMessage("0", "Climber");
                printMessage("1", "CLimb ENC " + std::to_string(m_climberMotor.GetEncPosition()));
                printMessage("2", "Limit " + std::to_string(m_climberLimit.Get()));

                switch (isPID)
                {
                case true:
                    m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_indexerMotor.goAt(joystickPower);
                    break;
                case false:
                    m_indexerMotor.SetControlMode(CANTalon::CANSpeedController::kPercentVbus);
                    m_indexerMotor.Set(joystickPower);
                    break;
                }
                break;
            }

            case 8: //Test all Shooter Components
            {

                printMessage("0", "Full Shooter");
                printMessage("1", "TFly ENC " + std::to_string(m_rightFlyWheelMotor.GetEncPosition()));
                printMessage("2", "BFly ENC " + std::to_string(m_leftFlyWheelMotor.GetEncPosition()));
                printMessage("3", "Feed ENC " + std::to_string(m_feederMotor.GetEncPosition()));
                printMessage("4", "Index ENC " + std::to_string(m_indexerMotor.GetEncPosition()));

                switch (isPID)
                {
                case true:
                    m_indexerMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_feederMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);
                    m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kSpeed);

                    if (m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                    {
                        m_rightFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                        m_leftFlyWheelMotor.goAt(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
                    }
                    else
                    {
                        m_rightFlyWheelMotor.goAt(joystickPower);
                        m_leftFlyWheelMotor.goAt(joystickPower);
                    }

                    if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                    {
                        m_feederMotor.goAt(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
                    }
                    else
                    {
                        m_feederMotor.goAt((m_joystick.GetThrottle() - 1) / 2);

                    }
                    m_indexerMotor.goAt(gamepadPower);
                    break;
                case false:

                    m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_leftFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                    m_rightFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);

                    if (m_gamepad.GetRawButton(DriveStationConstants::buttonX))
                    {
                        m_rightFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1", 0.0));
                        m_leftFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2", 0.0));
                    }
                    else
                    {
                        m_rightFlyWheelMotor.Set(joystickPower);
                        m_leftFlyWheelMotor.Set(joystickPower);
                    }

                    if (m_gamepad.GetRawButton(DriveStationConstants::buttonY))
                    {
                        m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0", 0.0));
                    }
                    else
                    {
                        m_feederMotor.Set((m_joystick.GetThrottle() - 1) / 2);
                    }


                m_indexerMotor.goAt(gamepadPower);
                break;
                }
                break;
            }

            case 9: //Test all 4 Drive Train Motors
            {
                printMessage("0", "DriveTrain");
                printMessage("1", "FRD ENC " + std::to_string(m_FRDrive.GetEncPosition()));
                printMessage("2", "FLD ENC " + std::to_string(m_FLDrive.GetEncPosition()));
                printMessage("3", "BRD ENC " + std::to_string(m_BRDrive.GetEncPosition()));
                printMessage("4", "BLD ENC " + std::to_string(m_BLDrive.GetEncPosition()));

                switch (isPID)
                {
                case true:
                    m_FRDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_FLDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_BRDrive.SetControlMode(CANSpeedController::kSpeed);
                    m_BLDrive.SetControlMode(CANSpeedController::kSpeed);

                    m_FRDrive.goAt(joystickPower);
                    m_FLDrive.goAt(joystickPower);
                    m_BRDrive.goAt(joystickPower);
                    m_BLDrive.goAt(joystickPower);
                    break;
                case false:
                    m_FRDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_FLDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_BRDrive.SetControlMode(CANSpeedController::kPercentVbus);
                    m_BLDrive.SetControlMode(CANSpeedController::kPercentVbus);

                    m_FRDrive.Set(joystickPower);
                    m_FLDrive.Set(joystickPower);
                    m_BRDrive.Set(joystickPower);
                    m_BLDrive.Set(joystickPower);
                    break;
                }
                break;

            }
            default:
            {

                LOGD << "In case default";
                break;
            }
            }
        }
    }
};

START_ROBOT_CLASS(Robot);

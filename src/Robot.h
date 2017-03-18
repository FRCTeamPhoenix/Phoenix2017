#ifndef _ROBOT_H
#define _ROBOT_H
#include "WPILib.h"
#include "RobotController.h"
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
#include "ConfigEditor.h"
#include <fstream>
#include "json.hpp"
#include "Lidar.h"
#include "Climber.h"
#include "Gatherer.h"
#include "Feeder.h"
#include "Indexer.h"
#include "GearTargeting.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <ntcore.h>
#include <cscore.h>
#include <networktables/NetworkTable.h>

//Suppresses uint_64 overflow warning from valijson
#pragma GCC diagnostic ignored "-Woverflow"
#include "Talons.h"
#include "valijson/adapters/nlohmann_json_adapter.hpp"
#include "valijson/utils/nlohmann_json_utils.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validator.hpp"


using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::adapters::NlohmannJsonAdapter;

using namespace std;
using json=nlohmann::json;

class ActionGroup;

class Robot: public SampleRobot

{
    Talons m_talons;
    SmartTalon m_FRDrive;
    SmartTalon m_FLDrive;
    SmartTalon m_BRDrive;
    SmartTalon m_BLDrive;
    ActionGroup* m_mainAutoGroup;
    relativeMecanumDrivetrain m_drivetrain;
    SmartTalon m_topFlyWheelMotor;
    SmartTalon m_lowerFlyWheelMotor;
    SmartTalon m_turretRotateMotor;
    DigitalInput m_leftLimitSwitch;
    DigitalInput m_rightLimitSwitch;
    Joystick m_joystickLeft;
    Joystick m_joystickRight;
    Joystick m_gamepad;
    Joystick m_customBox;
    Lidar m_lidar;
    ADIS16448_IMU m_expansionBoard;
    Communications m_visionComs;
    ShooterCalibrator m_shooterCalibrator;
    FlyWheels m_flywheel;
    Turret m_turret;
    GearTargeting m_gearTargeting;
    LoggerController m_loggerController;
    ConfigEditor m_configEditor;
    SmartTalon m_climberMotor;
    Climber m_climber;
    Talon m_gathererMotor;
    SmartTalon m_feederMotor;
    SmartTalon m_indexerMotor;
    Indexer m_indexer;
    Feeder m_feeder;
    Gatherer m_gatherer;
    RobotController m_robotController;

public:
	Robot();

	void RobotInit() override;

	void Autonomous();

	void OperatorControl();

	void Test();

	void initMainActionGroup();

	void initAutoMode();

	static void VisionThread();
	void switchToTeleoperated();

	//Functions For Robot Actions
	void driveAt(double speed, double angle);

	void driveDistance(double distance, double angle, double speed);

	void rotateAngle(double angle, double speed);

	bool doneDriveMove(double tolerance);

	void driveJoystick();

    void setIndexerSpeed(double speed);

	//End of Functions for Actions

	// Beginning of Test Mode
	enum TestMode{
		t_Talons,
		t_ShooterHead,
		t_Feeder,
		t_Indexer,
		t_Climber,
		t_Turret,
		t_Gatherer,
		t_Shooter,
		t_DriveTrain
	};

	vector<string> testModes = {
			"Talons",
			"ShooterHead",
			"Feeder",
			"Indexer",
			"Climber",
			"Turret",
			"Gatherer",
			"Shooter",
			"DriveTrain"};

	enum pidState {
		PID,
		VOLTAGE
	};
	pidState m_pidState;
	TestMode testModeSelector;
	// End of Test Mode

};
#endif

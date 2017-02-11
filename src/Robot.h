#ifndef ACTIONGRAPHS_ROBOT_H
#define ACTIONGRAPHS_ROBOT_H
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
#include <fstream>
#include "json.hpp"
#include "Lidar.h"
#include "Climber.h"
#include "Gatherer.h"
#include "Feeder.h"
#include "Indexer.h"
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

class ActionGroup;

class Robot: public SampleRobot

{

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
    Joystick m_joystick;
    Joystick m_gamepad;
    Lidar m_lidar;
    ADIS16448_IMU m_expansionBoard;
    Communications m_visionComs;
    ShooterCalibrator m_shooterCalibrator;
    FlyWheels m_flywheel;
    Turret m_turret;
    LoggerController m_loggerController;
    ShooterController m_shooterController;
    ConfigEditor m_configEditor;
    SmartTalon m_climberMotor;
    Climber m_climber;
    Talon m_gathererMotor;
    SmartTalon m_feederMotor;
    SmartTalon m_indexerMotor;
    Indexer m_indexer;
    Feeder m_feeder;
    Gatherer m_gatherer;

public:
    Robot();

    void RobotInit() override;

    void Autonomous();

    void OperatorControl();

    void Test();
    
    void initMainActionGroup();

    void initAutoMode();

    //Functions For Robot Actions
    void driveAt(double speed, double angle);

    void driveDistance(double distance, double angle, double speed);

    void rotateAngle(double angle, double speed);

    bool doneDriveMove(double tolerance);



    //End of Functions for Actions

};
#endif
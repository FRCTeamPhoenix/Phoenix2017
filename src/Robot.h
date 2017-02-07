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

    using namespace std;
    using json=nlohmann::json;

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

    public:
        Robot();

        void RobotInit() override;

        void Autonomous();

        void OperatorControl();

        void Test();

        //Functions For Robot Actions
        void driveAt(double speed, double angle);

        //End of Functions for Actions

    };
#endif

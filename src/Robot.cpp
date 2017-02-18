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

class Robot;

void lidarThread(Robot * robot, Lidar * lidar);

class Robot: public SampleRobot
{
//    SmartTalon m_FRDrive;
//    SmartTalon m_FLDrive;
//    SmartTalon m_BRDrive;
//    SmartTalon m_BLDrive;
//    relativeMecanumDrivetrain m_drivetrain;
    SmartTalon m_topFlyWheelMotor;
    SmartTalon m_lowerFlyWheelMotor;
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
//            m_FRDrive(3, CANTalon::FeedbackDevice::QuadEncoder),
//            m_FLDrive(2, CANTalon::FeedbackDevice::QuadEncoder),
//            m_BRDrive(4, CANTalon::FeedbackDevice::QuadEncoder),
//            m_BLDrive(1, CANTalon::FeedbackDevice::QuadEncoder),
//            m_drivetrain(m_FRDrive, m_FLDrive, m_BRDrive, m_BLDrive),
            m_topFlyWheelMotor(PortAssign::rightFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_lowerFlyWheelMotor(PortAssign::leftFlyWheelMotor, CANTalon::FeedbackDevice::QuadEncoder),
            m_turretRotateMotor(PortAssign::turret, CANTalon::FeedbackDevice::QuadEncoder),
            m_leftLimitSwitch(PortAssign::leftLimitSwitch),
            m_rightLimitSwitch( PortAssign::rightLimitSwitch),
            m_joystick(PortAssign::joystick),
            m_gamepad(PortAssign::gamepad),
            m_expansionBoard(),
            m_flywheel(m_topFlyWheelMotor, m_lowerFlyWheelMotor, m_gamepad),
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

                m_feederMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_indexerMotor.ConfigMaxOutputVoltage(3);
                m_topFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);
                m_lowerFlyWheelMotor.SetControlMode(CANSpeedController::kPercentVbus);

                std::thread runLidar(lidarThread, this, &m_lidar);
                runLidar.detach();

                while (IsEnabled() && IsTest())
                {
                    //A = indexer quarter rotation
                    //B = feeder run of dashboard from slider 0 input
                    //joystick throttle = run feeder
                    //joystick Y = run flywheels
                    //gamepad Y -= run indexer
                    // X = run flywheels off driverstation from slider 1 and 2 input


                   // FEEDER
                   // B: Run feeder off dashboard from slider 0 input
                   // Joystick throttle: Run feeder
                   if (m_gamepad.GetRawButton(DriveStationConstants::buttonB)){
                      m_feederMotor.Set(SmartDashboard::GetNumber("DB/Slider 0",0.0));

                   }
                   else
                   {
                       m_feederMotor.Set((m_joystick.GetThrottle()-1) / 2);
                   }

                    std::ostringstream throttleValue;
                    throttleValue << "Throttle: ";
                    throttleValue << ((m_joystick.GetThrottle()-1) / 2);
                    SmartDashboard::PutString("DB/String 7", throttleValue.str());

                    std::ostringstream feederEncoderValue;
                    feederEncoderValue << "EncoderF: ";
                    feederEncoderValue << m_feederMotor.GetEncPosition();
                    SmartDashboard::PutString("DB/String 6", feederEncoderValue.str());



                    // INDEXER
                    // A: Indexer quarter rotation
                    // Gamepad Y: Run indexer
                    if (m_gamepad.GetRawButton(DriveStationConstants::buttonA)){
                        //m_indexerMotor.goDistance(250,0.5);
                        m_indexerMotor.goAt(0.75);

                   }
                    else{
                        m_indexerMotor.Set(m_gamepad.GetY());
                    }

                   std::ostringstream indexerEncoderValue;
                   indexerEncoderValue << "EncoderI: ";
                   indexerEncoderValue << m_feederMotor.GetEncPosition();
                   SmartDashboard::PutString("DB/String 8", indexerEncoderValue.str());

                   // FLYWHEELS
                   // X: Run flywheels off driverstation from slider 1 and 2 input
                   // Joystick Y: Run flywheels
                   if (m_gamepad.GetRawButton(DriveStationConstants::buttonX)){

                       // Power-based
//                       m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1",0.0));
//                       m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2",0.0));

                       // Velocity-based (implement only after PID tuning of flywheel motors)

                       m_topFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 1",0.0));
                       m_lowerFlyWheelMotor.Set(SmartDashboard::GetNumber("DB/Slider 2",0.0));


                   }

                   else
                   {
//                       m_topFlyWheelMotor.goAt(0);
//                       m_lowerFlyWheelMotor.goAt(0);
//                       m_topFlyWheelMotor.goAt(m_joystick.GetY());
//                       m_lowerFlyWheelMotor.goAt(m_joystick.GetY());
                      m_topFlyWheelMotor.Set(m_joystick.GetY());
                      m_lowerFlyWheelMotor.Set(m_joystick.GetY());
                   }



                   std::ostringstream shooterRightEncoderString;
                   shooterRightEncoderString << "EncoderTop: ";
                   shooterRightEncoderString << m_topFlyWheelMotor.GetEncPosition();
                   SmartDashboard::PutString("DB/String 4", shooterRightEncoderString.str());

                   std::ostringstream shooterLeftEncoderString;
                   shooterLeftEncoderString << "EncoderLow: ";
                   shooterLeftEncoderString << m_lowerFlyWheelMotor.GetEncPosition();
                   SmartDashboard::PutString("DB/String 5", shooterLeftEncoderString.str());

                   std::ostringstream lidarString;
                   lidarString << "Distance: ";
                   lidarString << m_lidar.getFastAverage();
                   SmartDashboard::PutString("DB/String 9", lidarString.str());

                   std::ostringstream shooterTopVel;
                   shooterTopVel << "VelTop: ";
                   shooterTopVel << m_topFlyWheelMotor.GetEncVel();
                   //shooterTopVel << SmartDashboard::GetNumber("DB/Slider 1", 0.0);
                   SmartDashboard::PutString("DB/String 2", shooterTopVel.str());

                   std::ostringstream shooterLowVel;
                   shooterLowVel << "VelLow: ";
                   shooterLowVel << m_lowerFlyWheelMotor.GetEncVel();
                   //shooterLowVel << SmartDashboard::GetNumber("DB/Slider 2", 0.0);
                   SmartDashboard::PutString("DB/String 3", shooterLowVel.str());


                   m_configEditor.update();



                }

                runLidar.join();
    }

};

void lidarThread(Robot * robot, Lidar * lidar) {
   while(true) {
      lidar->run();
      stringstream ss;
      ss << lidar->getDistance();
      SmartDashboard::PutString("DB/String 3", ss.str());
   }
}

START_ROBOT_CLASS(Robot)
